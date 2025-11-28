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

/**
 * @brief FaceAttendannce 类
 * 功能：人脸识别考勤客户端主窗口类
 * 主要功能包括：
 * - 实时视频采集和人脸检测
 * - 将检测到的人脸图像发送到服务器进行识别
 * - 接收服务器返回的考勤结果并显示
 * - 自动重连服务器机制
 */
class FaceAttendannce : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     * 功能：初始化考勤窗口，创建UI界面，配置摄像头、分类器和网络连接
     */
    FaceAttendannce(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     * 功能：释放UI资源和其他动态分配的资源
     */
    ~FaceAttendannce();
    
    /**
     * @brief 定时器事件处理函数
     * @param e 定时器事件对象
     * 功能：定时捕获摄像头画面，进行人脸检测，处理检测到的人脸并发送到服务器
     * 触发时机：当定时器启动后，每隔指定时间自动调用
     */
    virtual void timerEvent(QTimerEvent *e);

private slots:
    /**
     * @brief 连接定时器超时处理函数
     * 功能：尝试连接到服务器
     * 触发时机：当连接定时器超时时调用
     */
    void Timer_connect();
    
    /**
     * @brief 停止连接定时器处理函数
     * 功能：停止连接定时器，表示已成功连接到服务器
     * 触发时机：当与服务器连接成功时调用
     */
    void Stop_connect();
    
    /**
     * @brief 启动连接定时器处理函数
     * 功能：启动连接定时器，尝试重新连接服务器
     * 触发时机：当与服务器连接断开时调用
     */
    void Start_connect();
    
    /**
     * @brief 接收数据处理函数
     * 功能：接收并解析服务器返回的考勤结果数据，更新UI显示
     * 触发时机：当接收到服务器数据时调用
     */
    void recv_data();

private:
    Ui::FaceAttendannce *ui;                 // UI界面指针

    //摄像头 - 用于捕获实时视频流
    //通过VideoCapture类从USB摄像头或IP摄像头获取视频帧
    //支持摄像头参数设置，如分辨率、帧率等
    VideoCapture cap;                        // 摄像头对象
    
    //Haar级联分类器 - 用于人脸检测
    //基于Haar特征的目标检测算法，能快速检测图像中的人脸区域
    //需要预训练的XML分类器文件来识别人脸模式
    cv::CascadeClassifier cascade;           // 人脸检测分类器

    //创建网络套接字和定时器
    QTcpSocket msocket;                      // TCP套接字，用于与服务器通信
    QTimer mtimer;                           // 定时器，用于自动重连服务器

    //标志是否是同一个人脸进入到识别区域
    int flag;                                // 人脸检测计数标志
    //保存人脸的数据
    cv::Mat faceMat;                         // 保存检测到的人脸图像
};

#endif // FACEATTENDANNCE_H


























