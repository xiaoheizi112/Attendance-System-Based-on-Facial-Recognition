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

/**
 * @brief 考勤主窗口类
 * 功能：
 * - 作为考勤系统的服务器端主界面
 * - 管理TCP服务器，处理客户端连接
 * - 接收并处理客户端发送的人脸图像数据
 * - 执行人脸识别并记录考勤信息
 * - 展示考勤数据和系统状态
 */
class AttendanceWin : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     * 功能：
     * - 初始化考勤窗口UI
     * - 配置TCP服务器
     * - 设置人脸识别对象和数据库连接
     * - 建立信号槽连接
     */
    AttendanceWin(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     * 功能：
     * - 释放UI资源
     * - 清理网络连接
     * - 释放动态分配的内存
     */
    ~AttendanceWin();

signals:
    /**
     * @brief 人脸查询信号
     * @param image 待识别的人脸图像
     * 功能：
     * - 向人脸识别对象发送人脸查询请求
     * - 触发人脸ID提取过程
     */
    void query(cv::Mat& image);

protected slots:
    /**
     * @brief 接受客户端连接槽函数
     * 功能：
     * - 处理新的客户端连接请求
     * - 建立与客户端的TCP通信
     * - 设置数据接收连接
     * 触发时机：
     * - 当有新客户端连接到服务器时自动调用
     */
    void accept_client();
    
    /**
     * @brief 读取数据槽函数
     * 功能：
     * - 接收客户端发送的图像数据
     * - 处理数据完整性
     * - 解析图像数据并准备人脸识别
     * 触发时机：
     * - 当收到客户端数据时自动调用
     */
    void read_data();
    
    /**
     * @brief 接收人脸ID槽函数
     * @param faceid 识别到的人脸ID
     * 功能：
     * - 根据人脸ID查询员工信息
     * - 记录考勤数据
     * - 更新UI显示考勤结果
     * 触发时机：
     * - 当人脸识别完成并返回人脸ID时调用
     */
    void recv_faceid(int64_t faceid);

private:
    Ui::AttendanceWin *ui; ///< UI对象指针，用于访问界面元素
    QTcpServer mserver; ///< TCP服务器对象，用于监听和接受客户端连接
    QTcpSocket *msocket; ///< TCP套接字指针，用于与客户端通信
    quint64 bsize; ///< 缓冲区大小，用于跟踪接收数据的字节数
    QFaceObject fobj; ///< 人脸识别核心对象，在独立线程中执行人脸识别
    QSqlTableModel model; ///< 数据库表模型，用于访问和操作员工数据表
};
#endif // ATTENDANCEWIN_H
