#include "attendancewin.h"
#include "ui_attendancewin.h"

#include <QDateTime>
#include <QThread>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief AttendanceWin类构造函数
 * @param parent 父窗口指针
 * @details 初始化考勤系统主窗口，设置UI组件、TCP服务器、数据库模型和多线程环境
 *          1. 初始化UI界面组件
 *          2. 配置并启动TCP服务器，监听8888端口所有网络接口
 *          3. 设置数据库模型与employee表绑定
 *          4. 创建工作线程并将人脸识别对象移至该线程
 *          5. 建立信号槽连接处理客户端连接和人脸识别结果
 */
AttendanceWin::AttendanceWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceWin)
{
    ui->setupUi(this);
    //qtcpServer当有客户端连接会发送newconnection
    connect(&mserver,&QTcpServer::newConnection,this,&AttendanceWin::accept_client);
    mserver.listen(QHostAddress::Any,8888);//监听所有网络接口，启动服务器
    bsize = 0;

    //给sql模型绑定表格
    model.setTable("employee");

    //创建一个线程
    QThread *thread = new QThread();
    // 将人脸识别核心对象fobj移动到新创建的工作线程中执行
    // 作用：将耗时的人脸识别计算从UI主线程中分离出来，避免界面卡顿
    fobj.moveToThread(thread);
    //启动线程
    thread->start();
    // 当系统接收到客户端发送的人脸图像数据后， AttendanceWin 会发射 query 信号
    // 该信号会被连接到 QFaceObject 中的 face_query 槽函数
    // 槽函数会在工作线程中执行，进行人脸识别计算
    connect(this,&AttendanceWin::query,&fobj,&QFaceObject::face_query);
    //关联QFaceObject里面的send——faceid信号
    connect(&fobj,&QFaceObject::send_faceid,this,&AttendanceWin::recv_faceid);
}

/**
 * @brief AttendanceWin类析构函数
 * @details 清理UI资源，避免内存泄漏
 *          注意：由于Qt的父子对象机制，其他子对象(如socket、thread等)会被自动清理
 */
AttendanceWin::~AttendanceWin()
{
    delete ui;
}

/**
 * @brief 客户端连接处理函数
 * @details 接收并处理新的客户端连接请求，获取通信套接字并建立数据接收连接
 * @note 触发时机：当QTcpServer检测到有新的客户端连接时，通过newConnection信号调用此函数
 */
void AttendanceWin::accept_client()
{
    //获取与客户端通信的套接字
    msocket = mserver.nextPendingConnection();
    //当客户端有数据到达时会发送readyRead信号
    connect(msocket,&QTcpSocket::readyRead,this,&AttendanceWin::read_data);
}

/**
 * @brief 数据接收处理函数
 * @details 从TCP套接字中读取并解析客户端发送的人脸图像数据，实现自定义网络协议解析
 *          1. 使用QDataStream读取和解析数据包
 *          2. 确保数据完整接收，处理分块传输的情况
 *          3. 显示接收到的图像
 *          4. 将图像数据转换为OpenCV格式并触发人脸识别
 * @note 触发时机：当客户端通过TCP套接字发送数据时，通过readyRead信号调用此函数
 */
void AttendanceWin::read_data()
{
    /*//读取所有数据
    //QString msg：将QByteArray转换为QString，将转换后的字符串存储在msg变量中
    QString msg = msocket->readAll();
    qDebug()<<msg;*/
    
    // 通过QDataStream可以直接读写复杂数据类型（如int、QString、QByteArray等）
    // 自动处理数据类型的大小端字节序和数据格式转换
    QDataStream stream(msocket);//把套接字绑定到数据流
    
    // 设置数据流版本以确保客户端和服务器使用相同的序列化格式
    // 避免不同Qt版本之间的数据格式不兼容问题
    stream.setVersion(QDataStream::Qt_5_15);//设置Qt版本

    // 第一阶段：读取数据包长度信息（协议头）
    if(bsize == 0){
        // 检查socket中是否有足够的字节数据可以读取（至少8字节用于quint64长度信息）
        // sizeof(bsize) = 8字节，这是quint64类型的大小
        // 如果可用字节不足，说明数据包不完整，等待下次数据到达
        if(msocket->bytesAvailable()<(quint64)sizeof(bsize)) return;
        
        // 使用数据流从网络套接字中读取数据包的实际大小信息
        // stream>> 操作会从socket中读取8字节的quint64数据
        // >>:指向变量，输入  <<:指向目标，输出
        stream>>bsize;
    }

    if(msocket->bytesAvailable()<bsize)//说明数据还没有发送完成，返回继续等待
    {
        return;
    }
    QByteArray data;
    stream>>data;
    bsize = 0;
    // 数据完整性检查
    if(data.size() == 0){
        qDebug()<<"客户端接收的数据为空！";
        return;
    }
    //显示图片
    QPixmap mmp;
    mmp.loadFromData(data,"jpg");
    mmp = mmp.scaled(ui->picLb->size());//固定图片缩放比例
    ui->picLb->setPixmap(mmp);

    // 人脸图像处理与识别准备阶段
    // 这部分代码负责将网络接收的二进制图像数据转换为OpenCV可处理的格式
    
    // 创建OpenCV的Mat对象，用于存储解码后的人脸图像
    cv::Mat faceImage;
    
    // 创建unsigned char类型的向量，用于临时存储二进制图像数据
    std::vector<uchar> decode;
    
    // 调整vector大小以容纳整个图像数据
    decode.resize(data.size());
    
    // 使用内存复制函数，将QByteArray中的数据复制到vector中
    // 这是为了格式转换，使数据可以被OpenCV处理
    memcpy(decode.data(),data.data(),data.size());
    
    // 使用OpenCV的imdecode函数将二进制数据解码为彩色图像
    // cv::IMREAD_COLOR参数指定解码为3通道BGR彩色图像
    faceImage = cv::imdecode(decode,cv::IMREAD_COLOR);

    // 以下是关键的多线程设计：
    // 1. 注释掉的代码显示了直接调用方式的问题 - 在UI线程执行会消耗大量资源
    // 2. 采用信号槽机制，将图像处理任务转移到工作线程执行
    //int faceid = fobj.face_query(faceImage); // 消耗资源过多，会阻塞UI线程
    
    // 发射query信号，将人脸图像传递给工作线程中的QFaceObject对象处理
    // 这种异步方式确保UI线程保持响应，用户体验流畅
    emit query(faceImage);
}

/**
 * @brief 接收人脸识别结果并处理考勤逻辑的槽函数
 * @param faceid 人脸识别引擎返回的唯一身份标识，< 0表示识别失败，>= 0表示成功识别
 * @details 考勤系统的核心业务处理入口，处理流程包括：
 *          1. 验证人脸识别结果
 *          2. 查询员工数据库获取个人信息
 *          3. 写入考勤记录到数据库
 *          4. 向客户端发送响应数据
 * @note 触发时机：当QFaceObject完成人脸识别后，通过send_faceid信号调用此函数
 */
void AttendanceWin::recv_faceid(int64_t faceid)
{
    //qDebug()<<"0000"<<faceid;
    //从数据库中查询faceid对应的个人信息

    qDebug()<<"识别到的人脸ID为："<<faceid;
    if(faceid < 0){
        QString sdmsg = QString("{\"employeeID\":\" \",\"name\":\"\",\"department\":\"\",\"time\":\"\"}");
        msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端
        return;
    }
    // 数据库过滤查询设置：
    // 1. 为QSqlTableModel设置SQL WHERE条件，根据识别到的人脸ID过滤员工记录
    // 3. 通过setFilter方法构建"faceID=xxx"的过滤条件，确保只查询匹配的员工信息
    // 4. 此过滤器将在后续model.select()执行时应用，实现精确的数据检索
    model.setFilter(QString("faceID=%1").arg(faceid));
    //查询
    model.select();
    // 数据验证与考勤流程处理
    // 1. 验证查询结果：确保只返回一条匹配记录，保证身份识别的唯一性和准确性
    if(model.rowCount() == 1){
        // 2. 员工信息提取与JSON响应构建
        // 获取查询结果中的第一条记录
        QSqlRecord record = model.record(0);
        // 构建标准JSON格式响应，包含员工核心信息
        // employeeID: 工号, name: 姓名, department: 部门(固定为"软件"), time: 当前时间戳
        QString sdmsg = QString("{\"employeeID\":\"%1\",\"name\":\"%2\",\"department\":\"软件\",\"time\":\"%3\"}")
                            .arg(record.value("employeeID").toString()).arg(record.value("name").toString())
                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        // 3. 考勤记录持久化：将识别成功的员工ID写入考勤表
        QString insertSql = QString("insert into attendance(employeeID) values('%1')").arg(record.value("employeeID").toString());
        QSqlQuery query;
        
        // 4. 数据库操作异常处理
        if(!query.exec(insertSql)){
            // 考勤记录写入失败：发送空数据给客户端，记录错误日志
            QString sdmsg = QString("{\"employeeID\":\" \",\"name\":\"\",\"department\":\"\",\"time\":\"\"}");
            msocket->write(sdmsg.toUtf8());// 发送失败响应给客户端
            qDebug()<<query.lastError().text();// 记录数据库错误信息
            return; // 终止后续执行
        }else{
            // 5. 考勤成功处理：将完整员工信息和时间戳发送给客户端
            msocket->write(sdmsg.toUtf8());// 发送成功响应给客户端
        }
    }
}



























