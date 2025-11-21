/********************************************************************************
** Form generated from reading UI file 'attendancewin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTENDANCEWIN_H
#define UI_ATTENDANCEWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <registerwin.h>
#include "seletwin.h"

QT_BEGIN_NAMESPACE

class Ui_AttendanceWin
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *showWidget;
    QLabel *picLb;
    RegisterWin *registerWidget;
    SeletWin *selectWidget;

    void setupUi(QMainWindow *AttendanceWin)
    {
        if (AttendanceWin->objectName().isEmpty())
            AttendanceWin->setObjectName(QString::fromUtf8("AttendanceWin"));
        AttendanceWin->resize(800, 500);
        centralwidget = new QWidget(AttendanceWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        showWidget = new QWidget();
        showWidget->setObjectName(QString::fromUtf8("showWidget"));
        picLb = new QLabel(showWidget);
        picLb->setObjectName(QString::fromUtf8("picLb"));
        picLb->setGeometry(QRect(6, 6, 470, 470));
        picLb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 255);"));
        tabWidget->addTab(showWidget, QString());
        registerWidget = new RegisterWin();
        registerWidget->setObjectName(QString::fromUtf8("registerWidget"));
        tabWidget->addTab(registerWidget, QString());
        selectWidget = new SeletWin();
        selectWidget->setObjectName(QString::fromUtf8("selectWidget"));
        tabWidget->addTab(selectWidget, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        AttendanceWin->setCentralWidget(centralwidget);

        retranslateUi(AttendanceWin);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(AttendanceWin);
    } // setupUi

    void retranslateUi(QMainWindow *AttendanceWin)
    {
        AttendanceWin->setWindowTitle(QCoreApplication::translate("AttendanceWin", "AttendanceWin", nullptr));
        picLb->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(showWidget), QCoreApplication::translate("AttendanceWin", "\350\200\203\345\213\244\345\233\276\345\203\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(registerWidget), QCoreApplication::translate("AttendanceWin", "\346\263\250\345\206\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(selectWidget), QCoreApplication::translate("AttendanceWin", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttendanceWin: public Ui_AttendanceWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTENDANCEWIN_H
