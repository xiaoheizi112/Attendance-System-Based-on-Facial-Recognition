#include "attendancewin.h"
#include "ui_attendancewin.h"

#include <QDateTime>
#include <QThread>
#include <QSqlQuery>
#include <QSqlError>

AttendanceWin::AttendanceWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceWin)
{
    ui->setupUi(this);
    //qtcpServer当有客户端连接会发送newconnection
    connect(&mserver,&QTcpServer::newConnection,this,&AttendanceWin::accept_client);
    mserver.listen(QHostAddress::Any,8888);//监听，启动服务器
    bsize = 0;

    //给sql模型绑定表格
    model.setTable("employee");

    //创建一个线程
    QThread *thread = new QThread();
    //把QFaceObject对象移动到线程执行
    fobj.moveToThread(thread);
    //启动线程
    thread->start();
    connect(this,&AttendanceWin::query,&fobj,&QFaceObject::face_query);
    //关联QFaceObject里面的send——faceid信号
    connect(&fobj,&QFaceObject::send_faceid,this,&AttendanceWin::recv_faceid);
}

AttendanceWin::~AttendanceWin()
{
    delete ui;
}

//接收客户端连接
void AttendanceWin::accept_client()
{
    //获取与客户端通信的套接字
    msocket = mserver.nextPendingConnection();
    //当客户端有数据到达时会发送readyRead信号
    connect(msocket,&QTcpSocket::readyRead,this,&AttendanceWin::read_data);
}

//读取客户端发送数据
void AttendanceWin::read_data()
{
    /*//读取所有数据
    //QString msg：将QByteArray转换为QString，将转换后的字符串存储在msg变量中
    QString msg = msocket->readAll();
    qDebug()<<msg;*/
    
    // 使用QDataStream进行二进制数据序列化处理
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
        // 这是一个典型的网络协议实现：首先传输数据长度，然后传输实际数据
        // stream>> 操作会从socket中读取8字节的quint64数据
        stream>>bsize;
    }

    if(msocket->bytesAvailable()<bsize)//说明数据还没有发送完成，返回继续等待
    {
        return;
    }
    QByteArray data;
    stream>>data;
    bsize = 0;
    if(data.size() == 0){
        return;
    }
    //显示图片
    QPixmap mmp;
    mmp.loadFromData(data,"jpg");
    mmp = mmp.scaled(ui->picLb->size());
    ui->picLb->setPixmap(mmp);

    //识别人脸
    cv::Mat faceImage;
    std::vector<uchar> decode;
    decode.resize(data.size());
    memcpy(decode.data(),data.data(),data.size());
    faceImage = cv::imdecode(decode,cv::IMREAD_COLOR);


    //int faceid = fobj.face_query(faceImage);//消耗资源过多
    emit query(faceImage);
}

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
    //给模型设置过滤器
    model.setFilter(QString("faceID=%1").arg(faceid));
    //查询
    model.select();
    //判断是否查询到数据
    if(model.rowCount() == 1){
        //工号、姓名、部门、时间
        //{employeeID:%1,name:%2,department:软件,time:%3}
        QSqlRecord record = model.record(0);
        QString sdmsg = QString("{\"employeeID\":\"%1\",\"name\":\"%2\",\"department\":\"软件\",\"time\":\"%3\"}")
                            .arg(record.value("employeeID").toString()).arg(record.value("name").toString())
                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        //把数据写入到数据库考勤表当中
        QString insertSql = QString("insert into attendance(employeeID) values('%1')").arg(record.value("employeeID").toString());
        QSqlQuery query;
        if(!query.exec(insertSql)){
            QString sdmsg = QString("{\"employeeID\":\" \",\"name\":\"\",\"department\":\"\",\"time\":\"\"}");
            msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端
            qDebug()<<query.lastError().text();
            return;
        }else{
            msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端
        }
    }
}



























