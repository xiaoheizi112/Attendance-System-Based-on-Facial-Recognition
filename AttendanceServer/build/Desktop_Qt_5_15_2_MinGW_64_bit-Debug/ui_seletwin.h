/********************************************************************************
** Form generated from reading UI file 'seletwin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELETWIN_H
#define UI_SELETWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeletWin
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *empRb;
    QRadioButton *attRb;
    QPushButton *selectBtn;
    QTableView *tableView;

    void setupUi(QWidget *SeletWin)
    {
        if (SeletWin->objectName().isEmpty())
            SeletWin->setObjectName(QString::fromUtf8("SeletWin"));
        SeletWin->resize(1000, 800);
        gridLayout = new QGridLayout(SeletWin);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        empRb = new QRadioButton(SeletWin);
        empRb->setObjectName(QString::fromUtf8("empRb"));

        horizontalLayout->addWidget(empRb);

        attRb = new QRadioButton(SeletWin);
        attRb->setObjectName(QString::fromUtf8("attRb"));

        horizontalLayout->addWidget(attRb);

        selectBtn = new QPushButton(SeletWin);
        selectBtn->setObjectName(QString::fromUtf8("selectBtn"));

        horizontalLayout->addWidget(selectBtn);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(SeletWin);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SeletWin);

        QMetaObject::connectSlotsByName(SeletWin);
    } // setupUi

    void retranslateUi(QWidget *SeletWin)
    {
        SeletWin->setWindowTitle(QCoreApplication::translate("SeletWin", "Form", nullptr));
        empRb->setText(QCoreApplication::translate("SeletWin", "\345\221\230\345\267\245", nullptr));
        attRb->setText(QCoreApplication::translate("SeletWin", "\350\200\203\345\213\244", nullptr));
        selectBtn->setText(QCoreApplication::translate("SeletWin", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SeletWin: public Ui_SeletWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELETWIN_H
