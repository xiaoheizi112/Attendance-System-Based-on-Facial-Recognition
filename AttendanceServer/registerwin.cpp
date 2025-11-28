#include "registerwin.h"
#include "qdebug.h"
#include "ui_registerwin.h"
#include <QFileDialog>
#include <qfaceobject.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>

RegisterWin::RegisterWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWin)
{
    ui->setupUi(this);
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

// 定时器事件处理函数
// 功能：
// - 定期从摄像头获取图像数据
// - 将OpenCV格式的图像转换为Qt可显示的格式
// - 在UI界面上实时显示摄像头画面
// 参数：
// - e: 定时器事件对象
// 触发时机：
// - 当定时器启动后，每隔指定时间间隔自动调用
void RegisterWin::timerEvent(QTimerEvent *e)
{
    // 步骤1：检查摄像头是否成功打开
    if(cap.isOpened()){
        // 使用流操作符>>从摄像头捕获一帧图像
        // 将捕获的图像数据存储到image(Mat类型)对象中
        cap>>image;
        if(image.data == nullptr) return;
    }
    
    // 步骤2：图像格式转换 - OpenCV Mat 转 Qt QImage
    // OpenCV默认使用BGR颜色空间，而Qt的QImage使用RGB颜色空间
    cv::Mat rgbImage; // 创建一个新的Mat对象用于存储RGB格式的图像
    cv::cvtColor(image,rgbImage,cv::COLOR_BGR2RGB); // 执行BGR到RGB的颜色空间转换
    
    // 从转换后的RGB图像数据创建QImage对象
    // 参数详解：
    // - rgbImage.data: 图像数据的指针
    // - rgbImage.cols: 图像宽度(列数)
    // - rgbImage.rows: 图像高度(行数)
    // - rgbImage.step1(): 每行字节数(步幅)，确保正确访问内存
    // - QImage::Format_RGB888: 像素格式，RGB三通道每通道8位
    QImage qimage(rgbImage.data,rgbImage.cols,rgbImage.rows,rgbImage.step1(),QImage::Format_RGB888);
    
    // 步骤3：在Qt界面上显示图像
    // 将QImage转换为QPixmap，QPixmap针对显示进行了优化
    QPixmap mmp = QPixmap::fromImage(qimage);
    
    // 调整图像尺寸以适应显示标签
    // scaledToWidth()方法保持图像宽高比进行缩放
    // ui->headpicLb->width()获取显示标签的宽度作为缩放目标
    mmp = mmp.scaledToWidth(ui->headpicLb->width());
    
    // 将调整后的图像设置到界面标签上显示
    // 这样摄像头捕获的实时画面就能显示在注册界面上
    ui->headpicLb->setPixmap(mmp);
}

// 重置按钮点击事件处理函数
// 功能：
// - 清空注册表单中的所有输入字段
// - 将生日日期重置为当前日期
// 触发时机：
// - 当用户点击重置按钮时调用
void RegisterWin::on_resetBtn_clicked()
{
    //清空数据
    ui->nameEdit->clear();
    ui->birthdayEdit->setDate(QDate::currentDate());
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->picfileEdit->clear();
}

// 添加头像按钮点击事件处理函数
// 功能：
// - 打开文件对话框，允许用户选择本地图片文件作为员工头像
// - 在UI上显示选中的头像图片
// - 将图片路径保存到表单中
// 触发时机：
// - 当用户点击添加头像按钮时调用
void RegisterWin::on_addpicBtn_clicked()
{
    //通过文件对话框 选中图片路径
    QString filepath = QFileDialog::getOpenFileName(this);
    ui->picfileEdit->setText(filepath);

    //显示图片：将用户选择的头像文件加载并显示在界面上
    //步骤1：创建QPixmap对象并从指定路径加载图片
    QPixmap mmp(filepath);
    
    //步骤2：调整图片尺寸以适应显示标签
    mmp = mmp.scaledToWidth(ui->headpicLb->width());
    
    //步骤3：将调整后的图片设置到头像标签上
    ui->headpicLb->setPixmap(mmp);
}

// 注册按钮点击事件处理函数
// 功能：
// - 执行员工注册流程，包括人脸特征提取和个人信息保存
// - 使用SeetaFace引擎提取人脸特征并生成唯一faceID
// - 将员工头像保存到本地文件系统
// - 将员工信息和faceID保存到数据库
// - 显示注册结果提示
// 触发时机：
// - 当用户点击注册按钮时调用
void RegisterWin::on_registerBtn_clicked()
{
    // 通过照片，结合QFaceObject模块得到faceID
    // 这是人脸注册的核心流程，将用户上传的照片转换为唯一的faceID
    QFaceObject faceobj;                                         // 创建人脸识别对象，用于调用SeetaFace引擎功能
    cv::Mat image = cv::imread(ui->picfileEdit->text().toUtf8().data());  // 从界面获取的图片路径，转换为OpenCV的Mat格式
    int64_t faceID = faceobj.face_register(image);
    qDebug()<<faceID;    // 调用人脸注册接口，返回唯一的faceID用于后续考勤识别

    // 生成头像文件保存路径 - 定义图像存储位置和命名规则
    // 使用员工姓名的Base64编码作为文件名，避免中文路径问题，同时保证文件名唯一性
    // 技术实现说明：toUtf8()将QString转换为UTF-8编码，toBase64()进行Base64编码，确保文件名在所有操作系统中有效
    // 保存路径为项目根目录下的data文件夹，文件格式为JPG
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    
    // 使用OpenCV的imwrite函数将捕获的人脸图像保存为文件
    // 参数说明：
    // 1. headfile.toUtf8().data() - 将QString转换为C风格字符串，确保正确处理中文路径
    // 2. image - OpenCV的Mat格式图像数据，包含捕获的人脸
    // 该操作将员工头像持久化存储，供后续人脸识别使用
    cv::imwrite(headfile.toUtf8().data(),image);

    //2.把个人信息存储到数据库employee
    QSqlTableModel model;
    model.setTable("employee");//设置表名
    QSqlRecord record = model.record();
    //设置数据
    record.setValue("name",ui->nameEdit->text());
    record.setValue("sex",ui->mrb->isChecked()?"男":"女");
    record.setValue("birthday",ui->birthdayEdit->text());
    record.setValue("address",ui->addressEdit->text());
    record.setValue("phone",ui->phoneEdit->text());
    record.setValue("faceID",faceID);
    //头像路径
    record.setValue("headfile",headfile);
    //把记录插入到数据库表格当中
    bool ret = model.insertRecord(0,record);
    //3.提示注册成功 - 员工注册流程的结果反馈阶段
    // 根据之前操作的返回值(ret)判断注册是否成功
    if(ret){
        // 注册成功：显示成功提示消息框
        // 参数说明：
        // this - 父窗口指针，使消息框显示在主窗口上方
        // "注册提示" - 消息框标题
        // "注册成功" - 消息框显示的文本内容
        QMessageBox::information(this,"注册提示","注册成功");
        
        // 提交
        // submitAll()方法将所有修改（包括新添加的记录）提交到数据库
        // 这是Qt SQL模型类的核心方法，确保内存中的数据变更被保存到物理数据库
        model.submitAll();
    }else{
        // 注册失败：显示失败提示消息框
        // 用户界面保持不变，允许用户修改信息后重新尝试注册
        QMessageBox::information(this,"注册提示","注册失败");
    }
}

// 摄像头开关按钮点击事件处理函数
// 功能：
// - 切换摄像头的开启/关闭状态
// - 当开启摄像头时，启动定时器以实时显示摄像头画面
// - 当关闭摄像头时，停止定时器并释放摄像头资源
// 触发时机：
// - 当用户点击摄像头开关按钮时调用
void RegisterWin::on_videoswitchBtn_clicked()
{
    if(ui->videoswitchBtn->text() == "打开摄像头")
    {
        //打开摄像头
        if(cap.open(0)){
            ui->videoswitchBtn->setText("关闭摄像头");
            //启动定时器事件
            timeid = startTimer(100);
        }
    }else{
        killTimer(timeid);
        ui->videoswitchBtn->setText("打开摄像头");
        //关闭摄像头
        cap.release();
    }
}


// 拍照按钮点击事件处理函数
// 功能：
// - 捕获当前摄像头画面并保存为员工头像
// - 生成唯一的头像文件名并保存到本地
// - 更新表单中的头像路径
// - 停止摄像头预览并关闭摄像头
// 触发时机：
// - 当用户点击拍照按钮时调用
void RegisterWin::on_cameraBtn_clicked()
{
    //保存数据 - 员工注册流程的最后阶段，将采集的人脸图像保存到系统中
    // 生成头像文件保存路径 - 定义数据存储位置为项目根目录下的data文件夹
    // 使用员工姓名的Base64编码作为文件名，避免中文路径问题，同时保证文件名唯一性
    // toUtf8().toBase64()将中文转换为UTF-8编码后再进行Base64编码，确保文件名兼容所有文件系统
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    
    // 将生成的文件路径显示在界面上的文件路径编辑框中，供用户查看和确认
    ui->picfileEdit->setText(headfile);
    
    // 使用OpenCV的imwrite函数将捕获的Mat格式图像保存为JPG文件
    // toUtf8().data()将QString转换为C风格字符串，确保正确写入包含中文的路径
    cv::imwrite(headfile.toUtf8().data(),image);
    
    // 停止定时器，关闭摄像头图像采集，释放系统资源
    killTimer(timeid);
    
    // 更新界面按钮文本状态，提示用户可以再次打开摄像头重新采集
    ui->videoswitchBtn->setText("打开摄像头");
    //关闭摄像头
    cap.release();
}

