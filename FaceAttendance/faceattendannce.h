#ifndef FACEATTENDANNCE_H
#define FACEATTENDANNCE_H

#include <QMainWindow>
#include <opencv.hpp>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
#include <iostream>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class FaceAttendannce;
}
QT_END_NAMESPACE

class FaceAttendannce : public QMainWindow
{
    Q_OBJECT

public:
    FaceAttendannce(QWidget *parent = nullptr);
    ~FaceAttendannce();
    //定时器事件
    virtual void timerEvent(QTimerEvent *e);

private slots:
    void Timer_connect();
    void Stop_connect();
    void Start_connect();
    void recv_data();

private:
    Ui::FaceAttendannce *ui;

    //摄像头 - 用于捕获实时视频流
    //通过VideoCapture类从USB摄像头或IP摄像头获取视频帧
    //支持摄像头参数设置，如分辨率、帧率等
    VideoCapture cap;
    
    //Haar级联分类器 - 用于人脸检测
    //基于Haar特征的目标检测算法，能快速检测图像中的人脸区域
    //需要预训练的XML分类器文件来识别人脸模式
    cv::CascadeClassifier cascade;

    //创建网络套接字和定时器
    QTcpSocket msocket;
    QTimer mtimer;

    //标志是否是同一个人脸进入到识别区域
    int flag;
    //保存人脸的数据
    cv::Mat faceMat;
};
#endif // FACEATTENDANNCE_H


























