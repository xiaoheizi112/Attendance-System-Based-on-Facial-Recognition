/********************************************************************************
** Form generated from reading UI file 'faceattendannce.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEATTENDANNCE_H
#define UI_FACEATTENDANNCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceAttendannce
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *widgetLb;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *headpicLb;
    QLabel *videoLb;
    QWidget *widget_3;
    QLabel *titleLb;
    QLabel *headLb;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *numberEdit;
    QWidget *widget_5;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *nameEdit;
    QWidget *widget_6;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_18;
    QLineEdit *departmentEdit;
    QWidget *widget_7;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_19;
    QLineEdit *timeEdit;

    void setupUi(QMainWindow *FaceAttendannce)
    {
        if (FaceAttendannce->objectName().isEmpty())
            FaceAttendannce->setObjectName(QString::fromUtf8("FaceAttendannce"));
        FaceAttendannce->resize(800, 480);
        FaceAttendannce->setStyleSheet(QString::fromUtf8(""));
        FaceAttendannce->setAnimated(true);
        centralwidget = new QWidget(FaceAttendannce);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 480, 480));
        widget->setMinimumSize(QSize(480, 480));
        widget->setMaximumSize(QSize(480, 480));
        widget->setStyleSheet(QString::fromUtf8(""));
        widgetLb = new QWidget(widget);
        widgetLb->setObjectName(QString::fromUtf8("widgetLb"));
        widgetLb->setGeometry(QRect(90, 400, 281, 61));
        widgetLb->setStyleSheet(QString::fromUtf8("background-color: rgba(49, 50, 54,63);\n"
"border-radius :10px;"));
        gridLayout = new QGridLayout(widgetLb);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widgetLb);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(31, 31));
        label->setMaximumSize(QSize(31, 31));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/yes.png);"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(widgetLb);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setKerning(false);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: rgba(49, 50, 54,63);\n"
"color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);

        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        headpicLb = new QLabel(widget);
        headpicLb->setObjectName(QString::fromUtf8("headpicLb"));
        headpicLb->setGeometry(QRect(100, 50, 266, 266));
        headpicLb->setMinimumSize(QSize(266, 266));
        headpicLb->setMaximumSize(QSize(266, 266));
        headpicLb->setStyleSheet(QString::fromUtf8("border-image: url(:/crc.png);"));
        videoLb = new QLabel(widget);
        videoLb->setObjectName(QString::fromUtf8("videoLb"));
        videoLb->setGeometry(QRect(0, 0, 480, 480));
        videoLb->raise();
        widgetLb->raise();
        headpicLb->raise();
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(480, 0, 320, 480));
        widget_3->setMinimumSize(QSize(320, 480));
        widget_3->setMaximumSize(QSize(320, 480));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border: 1px solid #313236;\n"
"	border-radius:4px;\n"
"	\n"
"	background-color: rgba(37, 40, 49,0.9);\n"
"}\n"
"\n"
"QWidget#titleLb{\n"
"	\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#headLb{\n"
"	border-radius:75px;\n"
"}"));
        titleLb = new QLabel(widget_3);
        titleLb->setObjectName(QString::fromUtf8("titleLb"));
        titleLb->setGeometry(QRect(0, 0, 320, 41));
        titleLb->setMinimumSize(QSize(320, 0));
        titleLb->setAlignment(Qt::AlignCenter);
        headLb = new QLabel(widget_3);
        headLb->setObjectName(QString::fromUtf8("headLb"));
        headLb->setGeometry(QRect(80, 50, 161, 151));
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(20, 210, 280, 60));
        widget_4->setMinimumSize(QSize(280, 60));
        widget_4->setMaximumSize(QSize(230, 50));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border: 1px solid #313236;\n"
"	border-radius:4px;\n"
"	\n"
"	background-color: rgba(37, 40, 49,0.9);\n"
"}\n"
""));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgba(255, 255, 255,0.8);"));

        horizontalLayout_2->addWidget(label_6);

        numberEdit = new QLineEdit(widget_4);
        numberEdit->setObjectName(QString::fromUtf8("numberEdit"));
        numberEdit->setEnabled(false);
        numberEdit->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(numberEdit);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 10);

        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(20, 280, 280, 60));
        widget_5->setMinimumSize(QSize(280, 60));
        widget_5->setMaximumSize(QSize(230, 50));
        widget_5->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border: 1px solid #313236;\n"
"	border-radius:4px;\n"
"	\n"
"	background-color: rgba(37, 40, 49,0.9);\n"
"}\n"
""));
        gridLayout_8 = new QGridLayout(widget_5);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(widget_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgba(255, 255, 255,0.8);"));

        horizontalLayout_3->addWidget(label_7);

        nameEdit = new QLineEdit(widget_5);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setEnabled(false);
        nameEdit->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(nameEdit);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 10);

        gridLayout_8->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(20, 350, 280, 60));
        widget_6->setMinimumSize(QSize(280, 60));
        widget_6->setMaximumSize(QSize(230, 50));
        widget_6->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border: 1px solid #313236;\n"
"	border-radius:4px;\n"
"	\n"
"	background-color: rgba(37, 40, 49,0.9);\n"
"}\n"
""));
        gridLayout_9 = new QGridLayout(widget_6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_18 = new QLabel(widget_6);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgba(255, 255, 255,0.8);"));

        horizontalLayout_9->addWidget(label_18);

        departmentEdit = new QLineEdit(widget_6);
        departmentEdit->setObjectName(QString::fromUtf8("departmentEdit"));
        departmentEdit->setEnabled(false);
        departmentEdit->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_9->addWidget(departmentEdit);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 10);

        gridLayout_9->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(20, 420, 280, 60));
        widget_7->setMinimumSize(QSize(280, 60));
        widget_7->setMaximumSize(QSize(230, 50));
        widget_7->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border: 1px solid #313236;\n"
"	border-radius:4px;\n"
"	\n"
"	background-color: rgba(37, 40, 49,0.9);\n"
"}\n"
""));
        gridLayout_10 = new QGridLayout(widget_7);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_19 = new QLabel(widget_7);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        label_19->setFont(font1);
        label_19->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgba(255, 255, 255,0.8);"));

        horizontalLayout_10->addWidget(label_19);

        timeEdit = new QLineEdit(widget_7);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setEnabled(false);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setItalic(false);
        timeEdit->setFont(font2);
        timeEdit->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_10->addWidget(timeEdit);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 10);

        gridLayout_10->addLayout(horizontalLayout_10, 0, 0, 1, 1);

        FaceAttendannce->setCentralWidget(centralwidget);

        retranslateUi(FaceAttendannce);

        QMetaObject::connectSlotsByName(FaceAttendannce);
    } // setupUi

    void retranslateUi(QMainWindow *FaceAttendannce)
    {
        FaceAttendannce->setWindowTitle(QCoreApplication::translate("FaceAttendannce", "FaceAttendannce", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("FaceAttendannce", "\350\256\244\350\257\201\346\210\220\345\212\237", nullptr));
        headpicLb->setText(QString());
        videoLb->setText(QString());
        titleLb->setText(QCoreApplication::translate("FaceAttendannce", "\344\272\272\350\204\270\350\257\206\345\210\253\350\200\203\345\213\244\347\263\273\347\273\237", nullptr));
        headLb->setText(QString());
        label_6->setText(QCoreApplication::translate("FaceAttendannce", "\345\267\245\345\217\267\357\274\232", nullptr));
        numberEdit->setText(QCoreApplication::translate("FaceAttendannce", "111", nullptr));
        label_7->setText(QCoreApplication::translate("FaceAttendannce", "\345\247\223\345\220\215\357\274\232", nullptr));
        nameEdit->setText(QCoreApplication::translate("FaceAttendannce", "111", nullptr));
        label_18->setText(QCoreApplication::translate("FaceAttendannce", "\351\203\250\351\227\250\357\274\232", nullptr));
        departmentEdit->setText(QCoreApplication::translate("FaceAttendannce", "111", nullptr));
        label_19->setText(QCoreApplication::translate("FaceAttendannce", "\346\227\266\351\227\264\357\274\232", nullptr));
        timeEdit->setText(QCoreApplication::translate("FaceAttendannce", "111", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FaceAttendannce: public Ui_FaceAttendannce {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEATTENDANNCE_H
