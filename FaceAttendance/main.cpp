#include "faceattendannce.h"

#include <QApplication>

/**
 * @brief 应用程序入口函数
 * @param argc 命令行参数数量
 * @param argv 命令行参数字符串数组
 * @return 程序退出状态码
 * 功能：
 * - 创建Qt应用程序实例
 * - 初始化人脸考勤窗口
 * - 显示考勤窗口
 * - 启动Qt事件循环，处理用户交互和系统事件
 * 执行流程：
 * 1. 创建QApplication对象，初始化Qt应用程序环境
 * 2. 实例化FaceAttendannce窗口类
 * 3. 调用show()方法显示主窗口
 * 4. 调用exec()方法启动事件循环，处理所有事件直到应用程序退出
 * 5. 返回应用程序的退出状态码
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FaceAttendannce w;
    w.show();
    return a.exec();
}
