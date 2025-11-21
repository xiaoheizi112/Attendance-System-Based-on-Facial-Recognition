QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#window平台opencv，seetaface环境
win32{
LIBS +=C:\opencv452\x64\mingw\lib\libopencv*
LIBS +=C:\SeetaFace\lib\libSeeta*
INCLUDEPATH +=C:\opencv452\include
INCLUDEPATH += C:\opencv452\include\opencv2
INCLUDEPATH += C:\SeetaFace\include
INCLUDEPATH += C:\SeetaFace\include\seeta
}

#linux平台opencv seetaface环境
unix{
LIBS += -L/opt/opencv4-pc/lib -lopencv_world \
-lSeetaFaceDetector \
-lSeetaFaceLandmarker \
-lSeetaFaceRecognizer \
-lSeetaFaceTracker \
-lSeetaNet \
-lSeetaQualityAssessor \

INCLUDEPATH += /opt/opencv4-pc/include/opencv4
INCLUDEPATH += /opt/opencv4-pc/include/opencv4/opencv2
INCLUDEPATH += /opt/opencv4-pc/include
INCLUDEPATH += /opt/opencv4-pc/include/seeta
}

SOURCES += \
    main.cpp \
    faceattendannce.cpp

HEADERS += \
    faceattendannce.h

FORMS += \
    faceattendannce.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
