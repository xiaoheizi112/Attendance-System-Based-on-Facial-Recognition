#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>
#include <opencv.hpp>

namespace Ui {
class RegisterWin;
}

/**
 * @brief RegisterWin 类
 * 功能：员工注册窗口类，负责处理员工信息录入和人脸注册
 * 主要功能包括：
 * - 员工基本信息输入
 * - 头像上传或摄像头拍照
 * - 人脸特征提取和注册
 * - 员工信息保存
 */
class RegisterWin : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     * 功能：初始化注册窗口，创建UI界面
     */
    explicit RegisterWin(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     * 功能：释放UI资源和其他动态分配的资源
     */
    ~RegisterWin();
    
    /**
     * @brief 定时器事件处理函数
     * @param e 定时器事件对象
     * 功能：定时捕获摄像头画面并显示在界面上
     * 触发时机：当定时器启动后，每隔指定时间自动调用
     */
    virtual void timerEvent(QTimerEvent *e);

private slots:
    /**
     * @brief 重置按钮点击事件
     * 功能：清空所有表单输入内容
     * 触发时机：当用户点击重置按钮时调用
     */
    void on_resetBtn_clicked();

    /**
     * @brief 添加头像按钮点击事件
     * 功能：打开文件选择对话框，让用户选择头像图片
     * 触发时机：当用户点击添加头像按钮时调用
     */
    void on_addpicBtn_clicked();

    /**
     * @brief 注册按钮点击事件
     * 功能：执行员工注册流程，包括人脸特征提取和个人信息保存
     * 触发时机：当用户点击注册按钮时调用
     */
    void on_registerBtn_clicked();

    /**
     * @brief 摄像头开关按钮点击事件
     * 功能：切换摄像头的开启/关闭状态
     * 触发时机：当用户点击摄像头开关按钮时调用
     */
    void on_videoswitchBtn_clicked();

    /**
     * @brief 拍照按钮点击事件
     * 功能：捕获当前摄像头画面并保存为员工头像
     * 触发时机：当用户点击拍照按钮时调用
     */
    void on_cameraBtn_clicked();

private:
    Ui::RegisterWin *ui;         // UI界面指针
    int timeid;                  // 定时器ID
    cv::VideoCapture cap;        // 摄像头对象
    cv::Mat image;               // 摄像头采集图像
};

#endif // REGISTERWIN_H
