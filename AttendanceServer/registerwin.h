#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>
#include <opencv.hpp>

namespace Ui {
class RegisterWin;
}

class RegisterWin : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWin(QWidget *parent = nullptr);
    ~RegisterWin();
    virtual void timerEvent(QTimerEvent *e);

private slots:
    void on_resetBtn_clicked();

    void on_addpicBtn_clicked();

    void on_registerBtn_clicked();

    void on_videoswitchBtn_clicked();


    void on_cameraBtn_clicked();

private:
    Ui::RegisterWin *ui;
    int timeid;

    cv::VideoCapture cap;
    cv::Mat image;
};

#endif // REGISTERWIN_H
