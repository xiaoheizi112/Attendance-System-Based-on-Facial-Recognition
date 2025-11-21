#ifndef ATTENDANCEWIN_H
#define ATTENDANCEWIN_H

#include "qfaceobject.h"
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <opencv.hpp>
#include <QSqlTableModel>
#include <QSqlRecord>

QT_BEGIN_NAMESPACE
namespace Ui {
class AttendanceWin;
}
QT_END_NAMESPACE

class AttendanceWin : public QMainWindow
{
    Q_OBJECT

public:
    AttendanceWin(QWidget *parent = nullptr);
    ~AttendanceWin();

signals:
    void query(cv::Mat& image);

protected slots:
    void accept_client();
    void read_data();
    void recv_faceid(int64_t faceid);

private:
    Ui::AttendanceWin *ui;
    //栈对象 ( QTcpServer mserver ) ：简单、安全、自动内存管理
    //指针 ( QTcpServer *mserver ) ：灵活、手动内存管理、适合复杂的内存分配需求
    QTcpServer mserver;

    //指针 ( QTcpSocket *msocket ) ：灵活、支持多客户端连接、可以动态创建和销毁
    //栈对象 ( QTcpSocket msocket ) ：简单、安全、但只能处理单一连接
    QTcpSocket *msocket;
    
    // bsize (缓冲区大小) ：用于跟踪和统计接收数据的字节数，支持大文件传输和网络数据处理
    // 使用quint64确保不会溢出，适合处理TB级别的大数据量统计
    quint64 bsize;

    QFaceObject fobj;
    QSqlTableModel model;
    

};
#endif // ATTENDANCEWIN_H
