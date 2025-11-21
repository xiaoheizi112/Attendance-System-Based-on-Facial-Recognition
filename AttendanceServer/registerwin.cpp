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

//获取摄像头数据并且显示在界面上
void RegisterWin::timerEvent(QTimerEvent *e)
{
    if(cap.isOpened()){
        cap>>image;
        if(image.data == nullptr) return;
    }
    //Mat-->QImage
    cv::Mat rgbImage;
    cv::cvtColor(image,rgbImage,cv::COLOR_BGR2RGB);
    QImage qimage(rgbImage.data,rgbImage.cols,rgbImage.rows,rgbImage.step1(),QImage::Format_RGB888);
    //在Qt界面上显示
    QPixmap mmp = QPixmap::fromImage(qimage);
    mmp = mmp.scaledToWidth(ui->headpicLb->width());
    ui->headpicLb->setPixmap(mmp);
}

//重置按钮
void RegisterWin::on_resetBtn_clicked()
{
    //清空数据
    ui->nameEdit->clear();
    ui->birthdayEdit->setDate(QDate::currentDate());
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->picfileEdit->clear();
}

//添加头像
void RegisterWin::on_addpicBtn_clicked()
{
    //通过文件对话框 选中图片路径
    QString filepath = QFileDialog::getOpenFileName(this);
    ui->picfileEdit->setText(filepath);

    //显示图片
    QPixmap mmp(filepath);
    mmp = mmp.scaledToWidth(ui->headpicLb->width());
    ui->headpicLb->setPixmap(mmp);
}

//注册
void RegisterWin::on_registerBtn_clicked()
{
    // 通过照片，结合QFaceObject模块得到faceID
    // 这是人脸注册的核心流程，将用户上传的照片转换为唯一的faceID
    QFaceObject faceobj;                                         // 创建人脸识别对象，用于调用SeetaFace引擎功能
    cv::Mat image = cv::imread(ui->picfileEdit->text().toUtf8().data());  // 从界面获取的图片路径，转换为OpenCV的Mat格式
    int64_t faceID = faceobj.face_register(image);
    qDebug()<<faceID;    // 调用人脸注册接口，返回唯一的faceID用于后续考勤识别

    // 生成头像文件保存路径
    // 使用员工姓名的Base64编码作为文件名，避免中文路径问题，同时保证文件名唯一性
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
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
    //3.提示注册成功
    if(ret){
        QMessageBox::information(this,"注册提示","注册成功");
        //提交
        model.submitAll();
    }else{
        QMessageBox::information(this,"注册提示","注册失败");
    }
}

//打开关闭摄像头
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


void RegisterWin::on_cameraBtn_clicked()
{
    //保存数据
    // 生成头像文件保存路径
    // 使用员工姓名的Base64编码作为文件名，避免中文路径问题，同时保证文件名唯一性
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    ui->picfileEdit->setText(headfile);
    cv::imwrite(headfile.toUtf8().data(),image);
    killTimer(timeid);
    ui->videoswitchBtn->setText("打开摄像头");
    //关闭摄像头
    cap.release();
}

