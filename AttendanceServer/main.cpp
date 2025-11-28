#include "attendancewin.h"
#include "seletwin.h"
#include "registerwin.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <opencv.hpp>


// 主函数：程序入口点
// 功能：
// - 初始化Qt应用程序
// - 注册自定义数据类型到Qt元对象系统，用于信号槽传递
// - 连接SQLite数据库
// - 创建系统所需的数据库表结构（员工表和考勤表）
// - 启动考勤系统主窗口
// 参数：
// - argc: 命令行参数数量
// - argv: 命令行参数数组
// 返回值：
// - 应用程序执行状态码（0表示正常退出，-1表示错误退出）
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册自定义数据类型到Qt元对象系统
    // 目的：使这些类型可以在Qt的信号槽机制中安全传递
    // cv::Mat&：OpenCV的矩阵引用类型，用于在不同线程间传递图像数据
    // cv::Mat：OpenCV的矩阵值类型，用于在不同线程间传递图像数据
    // int64_t：64位整数类型，用于在信号槽中传递大整数数据（如时间戳、ID等）
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<int64_t>("int64_t");

    // RegisterWin ww;
    // ww.show();

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名称
    db.setDatabaseName("server.db");
    //打开数据库
    if(!db.open()){
        qDebug()<<db.lastError().text();
        return -1;
    }
    // 创建员工信息表 - 用于存储员工基本信息和面部识别数据
    // 这个表是考勤系统的核心数据表，包含员工的个人信息和用于人脸识别的数据
    QString createsql = "create table if not exists employee("
                        "employeeID integer primary key autoincrement,"  // 员工ID - 主键，自动递增，唯一标识每个员工
                        "name varchar(256),"                           // 员工姓名 - 最多256字符，存储中文姓名
                        "sex varchar(32),"                             // 性别 - 32字符，可以存储"男"、"女"或其他描述
                        "birthday text,"                               // 生日 - text类型，存储日期格式(YYYY-MM-DD)
                        "address text,"                                // 地址 - 可以是任意长度的文本地址
                        "phone text,"                                  // 电话号码 - 存储手机号码或固定电话
                        "faceID integer unique,"                       // 人脸ID - 唯一标识，用于人脸识别系统，关联到SeetaFace的特征向量
                        "headfile text"                                // 头像文件路径 - 存储员工头像图片在服务器上的路径
                        ")";
    
    // 执行SQL创建表的语句
    // 创建SQL查询对象 - 用于执行SQL语句和操作SQLite数据库
    // QSqlQuery是Qt SQL模块的核心类，提供数据库查询、插入、更新、删除等功能
    QSqlQuery query;
    if(!query.exec(createsql)){
        // 如果创建失败，输出SQL错误信息并退出程序
        qDebug()<<query.lastError().text();
        return -1;
    }
    // 创建考勤表 - 用于存储员工考勤记录信息
    // 这个表记录员工的签到、签退等考勤数据，是考勤系统的核心业务表
    createsql = "create table if not exists attendance(attendanceID integer primary key autoincrement, employeeID integer,"
                "attendanceTime TimeStamp NOT NULL DEFAULT(datetime('now','localtime')))";
    
    // 执行SQL创建考勤表的语句
    if(!query.exec(createsql)){
        // 如果创建失败，输出SQL错误信息并退出程序
        qDebug()<<query.lastError().text();
        return -1;
    }

    AttendanceWin w;
    w.show();

    // SeletWin sw;
    // sw.show();
    return a.exec();
}
