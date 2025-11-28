#include "qfaceobject.h"

/**
 * @brief QFaceObject构造函数
 * @param parent Qt对象树中的父对象指针
 * @details 初始化SeetaFace人脸识别引擎，加载所需的人脸检测、关键点定位和识别模型
 *          1. 设置模型在CPU上运行，确保系统兼容性
 *          2. 加载人脸检测模型(fd_2_00.dat)
 *          3. 加载人脸关键点定位模型(pd_2_00_pts5.dat)
 *          4. 加载人脸识别模型(fr_2_10.dat)
 *          5. 创建完整的人脸识别引擎实例
 *          6. 加载已有的人脸数据库，实现数据持久化
 * @note 确保模型文件路径正确，数据库文件face.db保存在应用程序当前目录
 */
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

/**
 * @brief 人脸注册函数
 * @param faceImage OpenCV格式的人脸图像
 * @return 成功返回分配的人脸ID（>=0），失败返回-1
 * @details 将新的人脸图像注册到人脸识别系统中
 *          1. 将OpenCV的Mat数据转换为SeetaFace引擎所需的SeetaImageData格式
 *          2. 调用Register方法执行人脸注册，返回分配的唯一人脸ID
 *          3. 注册成功后保存数据库，确保数据持久化
 * @note 注册过程包括人脸检测、关键点定位和特征提取三个步骤
 */
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

/**
 * @brief 人脸查询函数
 * @param faceImage 待查询的人脸图像（OpenCV Mat格式）
 * @return 匹配的人脸ID（成功）或-1（未匹配）
 * @details 在人脸数据库中查找最匹配的人脸
 *          1. 将OpenCV的Mat数据转换为SeetaFace引擎所需的SeetaImageData格式
 *          2. 调用Query方法在数据库中查找最匹配的人脸
 *          3. 计算相似度值
 *          4. 根据相似度阈值（0.7）判断识别结果
 *          5. 发送识别结果信号
 * @note 这是计算密集型操作，包含特征提取和特征比对过程
 */
int QFaceObject::face_query(cv::Mat &faceImage)
{
    // 步骤1: 格式转换 - 将OpenCV的Mat数据结构转换为SeetaFace引擎所需的SeetaImageData格式
    SeetaImageData simage;  // SeetaFace引擎使用的数据结构
    simage.data = faceImage.data;      // 图像数据指针
    simage.width = faceImage.cols;     // 图像宽度（列数）
    simage.height = faceImage.rows;    // 图像高度（行数）
    simage.channels = faceImage.channels();  // 图像通道数（通常为3，RGB格式）
    
    // 步骤2: 初始化相似度变量 - 用于存储查询结果的相似度值
    float similarity = 0;
    
    // 步骤3: 执行人脸查询 - 调用SeetaFace引擎的Query方法在数据库中查找最匹配的人脸
    // 这是计算密集型操作，包含特征提取和特征比对过程
    int64_t faceid = fengineptr->Query(simage, &similarity);
    
    // 步骤4: 调试输出 - 打印查询结果，包括人脸ID和相似度值
    qDebug() << "查询" << faceid << similarity;
    
    // 步骤5: 相似度判断与结果处理
    // 设置相似度阈值为0.7，这是一个经验值，平衡了识别准确率和召回率
    if (similarity > 0.7) {
        // 相似度高于阈值，认为识别成功，发送匹配的人脸ID
        // 信号发射语句的核心是 emit 关键字，用于触发一个已声明的信号，进而通知所有连接到该信号的槽函数执行
        // 这里的 send_faceid 信号用于将识别结果（人脸ID）发送给连接的槽函数（如UI界面）
        emit send_faceid(faceid);
    } else {
        // 相似度低于阈值，认为未识别到匹配人脸，发送-1表示识别失败
        emit send_faceid(-1);
    }
    
    // 步骤6: 返回查询结果ID，供调用者进一步处理
    return faceid;
}


















