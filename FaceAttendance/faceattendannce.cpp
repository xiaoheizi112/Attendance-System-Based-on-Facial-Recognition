#include "faceattendannce.h"
#include "ui_faceattendannce.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

/**
 * @brief 构造函数
 * @param parent 父窗口指针
 * 功能：
 * - 初始化考勤窗口，设置固定大小和UI界面
 * - 配置摄像头设备
 * - 启动定时器进行视频采集和人脸检测
 * - 加载Haar级联分类器进行人脸检测
 * - 设置网络连接信号槽，实现自动重连机制
 */
FaceAttendannce::FaceAttendannce(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FaceAttendannce)
{
    this->setFixedSize(800, 480);
    ui->setupUi(this);
    //打开摄像头
    //参数0表示使用系统默认的第一个摄像头设备
    //也可以使用路径或摄像头索引号来指定特定设备
    cap.open(0);
    
    //启动定时器事件
    //参数100表示定时器间隔为100毫秒(0.1秒)
    //定时器到期后将自动调用timerEvent()函数进行视频帧处理和人脸检测
    startTimer(100);

    //导入分类器文件
    //加载OpenCV预训练的人脸检测Haar特征分类器
    //haarcascade_frontalface_alt2.xml是优化后的人脸检测模型
    //该文件包含 milliers个Haar特征，用于识别人脸的正面轮廓
    //文件路径指向OpenCV安装目录下的分类器库
    cascade.load("C:/opencv452/etc/haarcascades/haarcascade_frontalface_alt2.xml");

    //QTcpsocket网络连接信号槽机制详解：
    //1. disconnected信号：网络断开时自动触发，重新启动连接定时器
    //2. connected信号：网络连接成功时触发，停止自动重连
    //3. 自动重连机制：确保网络异常时能自动恢复连接
    //&符号作用：获取对象的地址(引用)，是C++地址操作符
    //&msocket: 获取msocket对象的内存地址，指向QTcpSocket实例
    //&QTcpSocket::disconnected: 获取disconnected信号的函数指针地址
    //函数指针 = 函数的地址，指向函数的入口点
    //函数调用需要括号(如Start_connect())，函数指针不需要括号
    //语法格式：connect(发送者地址,&发送者类::信号名,接收者地址,&接收者类::槽名)
    connect(&msocket,&QTcpSocket::disconnected,this,&FaceAttendannce::Start_connect);
    connect(&msocket,&QTcpSocket::connected,this,&FaceAttendannce::Stop_connect);
    //关联接收数据的槽函数
    connect(&msocket,&QTcpSocket::readyRead,this,&FaceAttendannce::recv_data);

    //QTimer定时器信号槽详解：
    //1. timeout信号：定时器超时(5000ms)时触发，尝试连接服务器
    //2. 连接触发：调用Timer_connect()函数执行网络连接
    //3. 自动重连控制：连接成功后停止定时器，断开后重新启动
    //作用：实现网络连接的重试机制，确保可靠连接
    connect(&mtimer,&QTimer::timeout,this,&FaceAttendannce::Timer_connect);
    //启动定时器
    mtimer.start(5000);//每5s连接一次，直到连接成功后就不再连接
    flag = 0;
    ui->widgetLb->hide();
}

FaceAttendannce::~FaceAttendannce()
{
    delete ui;
}

/**
 * @brief 定时器事件处理函数
 * @param e 定时器事件对象
 * 功能：
 * - 定时从摄像头捕获视频帧
 * - 对图像进行人脸检测
 * - 处理检测到的人脸，当连续检测到同一人脸多次时，将图像发送到服务器
 * - 将捕获的图像转换格式并显示在UI界面上
 * 触发时机：
 * - 当定时器启动后，每隔100毫秒自动调用
 */
void FaceAttendannce::timerEvent(QTimerEvent *e)
{
    //采集数据
    //Mat是OpenCV中的核心矩阵类，用于存储图像数据
    //创建Mat对象用于存储摄像头捕获的图像帧
    Mat srcImage;
    if(cap.grab()){
        //grab()尝试获取下一帧，返回true表示成功获取
        cap.read(srcImage);//读取捕获的视频帧数据到srcImage矩阵中
    }

    //把图片大小设与显示窗口一样大
    cv::resize(srcImage,srcImage,Size(480,480));
    //检测人脸数据
    //创建矩形向量用于存储检测到的人脸区域坐标
    std::vector<Rect> faceRects;
    //使用级联分类器进行多尺度人脸检测
    //detectMultiScale会自动在不同尺度下搜索人脸
    cascade.detectMultiScale(srcImage,faceRects);
    //如果检测到人脸（返回的人脸矩形框数量>0）
    if(faceRects.size()>0 && flag >= 0){
        //从检测到的人脸矩形框向量中获取第一个检测到的人脸
        //Rect是OpenCV中的矩形类，包含x,y坐标和width,height尺寸信息
        Rect rect = faceRects.at(0);//获取第一个检测到的人脸矩形框
        //rectangle函数绘制矩形框详解：
        //参数1 srcImage: 在此图像上绘制矩形
        //参数2 rect: 要绘制的矩形区域，包含人脸的位置和尺寸
        //参数3 Scalar(0,0,255): 矩形边框颜色，BGR格式 (蓝=0, 绿=0, 红=255) = 纯红色
        //作用：在人脸检测结果上绘制红色矩形框，提供视觉反馈
        //应用：用户可以直观看到检测到的人脸位置，便于确认系统运行状态
        //rectangle(srcImage,rect,Scalar(0,0,255));

        //移动人脸框（图片--QLabel）
        ui->headpicLb->move(rect.x,rect.y);

        if(flag >2){
            // 将OpenCV的Mat格式图像数据编码为JPEG压缩格式
            // 创建向量缓冲区用于存储编码后的JPEG图像数据
            vector<uchar> buf;  // uchar类型：无符号字符，适合存储字节数据

            // 使用OpenCV的imencode函数将Mat图像压缩为JPEG格式
            // 参数说明：
            //  - ".jpg": 输出图像格式为JPEG
            //  - srcImage: 输入的原始图像数据（检测人脸后的完整图像帧）
            //  - buf: 输出参数，存储编码后的JPEG字节数据
            // 作用：大幅减少图像数据大小，提高网络传输效率
            cv::imencode(".jpg",srcImage,buf);

            // 将OpenCV的字节数据转换为Qt可处理的字节数组
            // QByteArray是Qt框架中的字节数组类，提供了丰富的操作方法
            // 构造函数参数详解：
            //  - (const char*)buf.data(): 将OpenCV向量的数据指针转换为C字符串指针
            //  - buf.size(): 数据大小（字节数），确保完整传输所有图像数据
            QByteArray byte((const char*)buf.data(),buf.size());

            // 准备网络传输数据格式
            // quint64：64位无符号整数，确保在各种平台上图像大小数据一致性
            // 记录编码后JPEG图像的实际字节数，用于接收端验证数据完整性
            quint64 backsize = byte.size();

            // 创建用于网络传输的字节数组容器
            QByteArray sendData;

            // 使用Qt数据流序列化图像数据
            // QDataStream提供跨平台的数据序列化功能，确保不同系统间的数据兼容性
            // 构造函数参数：
            //  - &sendData: 关联输出数据流到sendData字节数组
            //  - QIODevice::WriteOnly: 以只写模式打开数据流
            QDataStream stream(&sendData,QIODevice::WriteOnly);

            // 设置数据流版本以确保兼容性
            // Qt_5_15版本提供了稳定的序列化格式，避免版本间的数据格式差异
            stream.setVersion(QDataStream::Qt_5_15);

            // 序列化图像大小和图像数据
            // 按照固定顺序写入数据：
            //  1. 先写入backsize（图像大小信息）
            //  2. 再写入byte（实际的JPEG图像数据）
            // 这样的顺序便于接收端先验证数据大小，再读取对应大小的数据
            stream<<backsize<<byte;

            // 通过网络套接字发送序列化后的图像数据
            // QTcpSocket::write()函数将sendData中的所有字节写入网络缓冲区
            msocket.write(sendData);
            flag = -2;

            faceMat = srcImage(rect);
            //保存
            imwrite("./face.jpg",faceMat);
        }
        flag ++;
    }
    if(faceRects.size() == 0){//把人脸框移到中心位置
        ui->headpicLb->move(100,60);
        flag = 0;
    }

    if(srcImage.data == nullptr)return;
    //把opencv里面的mat格式数据（BGR）转Qt里面的QImage（RGB）
    //OpenCV使用BGR颜色格式，Qt使用RGB格式，需要颜色空间转换
    //颜色空间转换说明：
    //1. OpenCV标准：使用BGR格式 (B-蓝, G-绿, R-红)，这是历史原因形成的
    //2. Qt标准：使用RGB格式 (R-红, G-绿, B-蓝)，这是常见的颜色表示方法
    //3. 转换原因：如果不转换，颜色会显示异常（红色变蓝色等）
    //4. 转换过程：cvtColor函数会重新排列像素中的颜色通道顺序
    //cvtColor函数调用详解：
    //参数1 srcImage: 输入图像(BGR格式)，同时也是输出图像
    //参数2 srcImage: 原地转换，不创建新图像对象，节省内存
    //参数3 COLOR_BGR2RGB: 转换码，指定从BGR到RGB的颜色空间转换
    cvtColor(srcImage,srcImage,COLOR_BGR2RGB);
    //创建QImage对象，使用RGB888格式（每像素3字节）
    //QImage构造函数详解 - 将OpenCV Mat转换为Qt QImage格式：
    //参数1 srcImage.data: OpenCV图像数据的指针，指向像素数据起始地址
    //参数2 srcImage.cols: 图像宽度(列数)，单位像素
    //参数3 srcImage.rows: 图像高度(行数)，单位像素
    //参数4 srcImage.step1(): 每行字节数(步幅)，用于跳过填充字节
    //参数5 QImage::Format::Format_RGB888: 像素格式，RGB三通道每通道8位
    //注意：不复制数据，只创建视图，原Mat数据变更会影响QImage
    QImage image(srcImage.data,srcImage.cols,srcImage.rows,srcImage.step1(),QImage::Format::Format_RGB888);
    //将QImage转换为QPixmap，QPixmap专为在GUI中显示优化
    //QPixmap转换详解 - 从QImage创建QPixmap用于GUI显示：
    //深拷贝 vs 浅拷贝说明：
    //浅拷贝(Shallow Copy)：只复制指针，不复制数据，多个对象共享同一内存
    //深拷贝(Deep Copy)：复制指针和数据，每个对象拥有独立的数据副本
    //QPixmap::fromImage()默认执行深拷贝，确保GUI显示的独立性和线程安全
    //参数image：前一步创建的QImage对象(RGB格式)
    //返回mmp：QPixmap对象，专为GUI显示优化，支持硬件加速
    //QPixmap特点：线程安全、硬件加速、适合频繁重绘
    QPixmap mmp = QPixmap::fromImage(image);
    //setPixmap(): QLabel的方法，用于设置显示的图像内容
    //参数mmp: 前面创建的QPixmap对象，包含完整的图像数据和人脸检测标记
    ui->videoLb->setPixmap(mmp);
}

/**
 * @brief 连接定时器超时处理函数
 * 功能：
 * - 尝试连接到考勤服务器
 * - 连接指定IP地址和端口的服务器
 * 触发时机：
 * - 当连接定时器超时时调用，默认每5秒尝试一次
 */
void FaceAttendannce::Timer_connect()
{
    //连接服务器
    msocket.connectToHost("192.168.31.158",8888);
}

/**
 * @brief 停止连接定时器处理函数
 * 功能：
 * - 停止连接定时器，表示已成功连接到服务器
 * - 输出调试信息指示连接状态
 * 触发时机：
 * - 当与服务器连接成功时自动调用
 */
void FaceAttendannce::Stop_connect()
{
    mtimer.stop();
    qDebug()<<"成功连接服务器!";
}

/**
 * @brief 启动连接定时器处理函数
 * 功能：
 * - 启动连接定时器，尝试重新连接服务器
 * - 设置定时器间隔为5秒
 * - 输出调试信息指示断开状态
 * 触发时机：
 * - 当与服务器连接断开时自动调用
 */
void FaceAttendannce::Start_connect()
{
    mtimer.start(5000);//启动定时器
    qDebug()<<"断开服务器连接!";
}

/**
 * @brief 接收数据处理函数
 * 功能：
 * - 接收服务器返回的JSON格式考勤结果数据
 * - 解析JSON数据，提取员工ID、姓名、部门和时间信息
 * - 更新UI界面显示考勤结果
 * - 设置员工头像显示
 * 触发时机：
 * - 当接收到服务器数据时自动调用
 */
void FaceAttendannce::recv_data()
{
    // 注释：JSON数据格式示例，包含考勤结果所需的字段
    //{employeeID:%1,name:%2,department:软件,time:%3}
    
    // 从TCP套接字读取服务器返回的所有数据
    // QByteArray是Qt中的字节数组类，适合存储二进制数据或文本数据
    // msocket.readAll()会一次性读取socket缓冲区中的所有可用数据
    QByteArray array = msocket.readAll();
    
    // 调试输出：打印接收到的原始数据，用于开发调试
    qDebug()<<array;
    
    // Json解析数据流程
    // 创建JSON解析错误对象，用于捕获解析过程中的错误信息
    QJsonParseError err;
    
    // 使用QJsonDocument::fromJson()静态方法解析JSON数据
    // 参数说明：
    // - array: 包含JSON格式文本的字节数组
    // - &err: 错误信息对象的引用，解析失败时会填充错误信息
    // 返回值: 成功时返回包含JSON数据结构的QJsonDocument对象
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    
    // 错误处理：检查JSON解析是否成功
    // QJsonParseError::NoError表示解析成功
    // 解析失败时输出错误信息并提前返回
    if(err.error!= QJsonParseError::NoError){
        qDebug()<<"Json解析错误！";
        return;
    }
    
    // 从QJsonDocument中获取根级别的JSON对象
    // QJsonObject表示JSON中的对象类型，由键值对组成
    QJsonObject obj = doc.object();
    
    // 从JSON对象中提取各个字段的值
    // 使用value()方法根据键名获取值，再使用toXXX()方法转换为所需类型
    // 提取员工ID信息
    QString employeeID = obj.value("employeeID").toString();
    // 提取员工姓名信息
    QString name = obj.value("name").toString();
    // 提取员工部门信息
    QString department = obj.value("department").toString();
    // 提取考勤时间信息
    QString timestr = obj.value("time").toString();

    ui->numberEdit->setText(employeeID);
    ui->nameEdit->setText(name);
    ui->departmentEdit->setText(department);
    ui->timeEdit->setText(timestr);

    // cvtColor(faceMat,faceMat,COLOR_BGR2RGB);
    // QImage image(faceMat.data,faceMat.cols,faceMat.rows,faceMat.step1(),QImage::Format::Format_RGB888);
    // QPixmap mmp = QPixmap::fromImage(image);
    // ui->headLb->setPixmap(mmp);

    //通过样式来显示图片
    ui->headLb->setStyleSheet("border-radius:75px;border-image: url(./face.jpg);");
    ui->widgetLb->show();
}














