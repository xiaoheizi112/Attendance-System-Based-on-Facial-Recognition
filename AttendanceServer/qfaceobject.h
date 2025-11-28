#ifndef QFACEOBJECT_H
#define QFACEOBJECT_H

#include <QObject>
#include <seeta/FaceEngine.h>
#include <opencv.hpp>
#include <QDebug>

/**
 * @brief 人脸识别核心类
 * @details 封装SeetaFace引擎，提供人脸检测、特征提取、人脸注册和识别功能
 *          支持在独立线程中运行，避免阻塞UI线程
 */
class QFaceObject : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，用于Qt对象树管理
     * @details 初始化人脸识别核心对象，创建并配置SeetaFace引擎
     * @note 使用explicit关键字防止隐式转换
     */
    explicit QFaceObject(QObject *parent = nullptr);
    /**
     * @brief 析构函数
     * @details 释放人脸识别引擎资源
     */
    ~QFaceObject();

public slots:
    /**
     * @brief 人脸注册槽函数
     * @param faceImage 包含人脸的OpenCV Mat格式图像
     * @return 成功注册的人脸ID（>=0），失败返回-1
     * @details 将新的人脸图像注册到系统中，提取人脸特征并分配唯一ID
     */
    int64_t face_register(cv::Mat& faceImage);
    
    /**
     * @brief 人脸查询槽函数
     * @param faceImage 待查询的人脸图像
     * @return 匹配的人脸ID（>=0），未匹配返回-1
     * @details 在注册数据库中查询匹配的人脸，提取当前人脸特征并与已注册特征比对
     */
    int face_query(cv::Mat& faceImage);

signals:
    /**
     * @brief 发送人脸ID信号
     * @param faceid 识别出的人脸ID
     * @details 当人脸识别完成后发送识别结果，供其他组件处理
     */
    void send_faceid(int64_t faceid);
private:
    /**
     * @brief SeetaFace引擎指针
     * @details 核心人脸识别引擎对象，负责执行人脸检测、关键点定位和特征提取等底层算法
     */
    seeta::FaceEngine *fengineptr;
};

#endif // QFACEOBJECT_H
