#include "qfaceobject.h"

QFaceObject::QFaceObject(QObject *parent)
    : QObject{parent}
{
    // 初始化SeetaFace人脸识别引擎
    // SeetaFace是一个完整的人脸识别系统，包含检测、对齐和识别三个模块
    // FDmode: 人脸检测模块 - 检测图像中的人脸位置
    seeta::ModelSetting FDmode("C:/SeetaFace/bin/model/fd_2_00.dat",seeta::ModelSetting::CPU,0);
    
    // PDmode: 人脸关键点定位模块 - 检测5个关键点（左眼、右眼、鼻子、左嘴角、右嘴角）
    seeta::ModelSetting PDmode("C:/SeetaFace/bin/model/pd_2_00_pts5.dat",seeta::ModelSetting::CPU,0);
    
    // FRmode: 人脸识别模块 - 提取人脸特征向量用于身份识别
    seeta::ModelSetting FRmode("C:/SeetaFace/bin/model/fr_2_10.dat",seeta::ModelSetting::CPU,0);
    
    // 使用三个模型设置创建完整的人脸识别引擎实例
    // FaceEngine整合了人脸检测、对齐和识别的完整流程
    this->fengineptr = new seeta::FaceEngine(FDmode,PDmode,FRmode);

    // 导入已有的人脸数据库 - 实现数据持久化和系统恢复能力
    // 程序重启后加载之前保存的人脸特征数据，避免重新注册所有员工人脸
    // 确保考勤系统能够识别之前已经注册过的员工，实现连续性服务
    this->fengineptr->Load("./face.db");

}

QFaceObject::~QFaceObject()
{
    delete fengineptr;
}

int64_t QFaceObject::face_register(cv::Mat &faceImage)
{
    //把OpenCV的Mat数据转为seetaface的数据
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();
    int64_t faceid = this->fengineptr->Register(simage);//注册返回一个人脸id
    if(faceid >= 0){
        fengineptr->Save("./face.db");
    }
    return faceid;
}

int QFaceObject::face_query(cv::Mat &faceImage)
{
    //把OpenCV的Mat数据转为seetaface的数据
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();
    float similarity = 0;
    int64_t faceid = fengineptr->Query(simage,&similarity);//运算时间比较长
    qDebug()<<"查询"<<faceid<<similarity;
    if(similarity > 0.7){//相似度大于0.7
        emit send_faceid(faceid);
    }else{
        emit send_faceid(-1);
    }
    return faceid;
}


















