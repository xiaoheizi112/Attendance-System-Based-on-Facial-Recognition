/********************************************************************************
** Form generated from reading UI file 'registerwin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIN_H
#define UI_REGISTERWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWin
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QRadioButton *mrb;
    QRadioButton *wrb;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDateEdit *birthdayEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *addressEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *phoneEdit;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *registerBtn;
    QPushButton *resetBtn;
    QVBoxLayout *verticalLayout_2;
    QLabel *headpicLb;
    QLineEdit *picfileEdit;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *addpicBtn;
    QPushButton *videoswitchBtn;
    QPushButton *cameraBtn;

    void setupUi(QWidget *RegisterWin)
    {
        if (RegisterWin->objectName().isEmpty())
            RegisterWin->setObjectName(QString::fromUtf8("RegisterWin"));
        RegisterWin->resize(1000, 800);
        RegisterWin->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(RegisterWin);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(RegisterWin);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        nameEdit = new QLineEdit(RegisterWin);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nameEdit->sizePolicy().hasHeightForWidth());
        nameEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(nameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(RegisterWin);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        mrb = new QRadioButton(RegisterWin);
        mrb->setObjectName(QString::fromUtf8("mrb"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mrb->sizePolicy().hasHeightForWidth());
        mrb->setSizePolicy(sizePolicy1);
        mrb->setFont(font);

        horizontalLayout_2->addWidget(mrb);

        wrb = new QRadioButton(RegisterWin);
        wrb->setObjectName(QString::fromUtf8("wrb"));
        wrb->setFont(font);

        horizontalLayout_2->addWidget(wrb);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(RegisterWin);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        birthdayEdit = new QDateEdit(RegisterWin);
        birthdayEdit->setObjectName(QString::fromUtf8("birthdayEdit"));
        sizePolicy2.setHeightForWidth(birthdayEdit->sizePolicy().hasHeightForWidth());
        birthdayEdit->setSizePolicy(sizePolicy2);
        birthdayEdit->setFont(font);

        horizontalLayout_5->addWidget(birthdayEdit);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 10);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(RegisterWin);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        addressEdit = new QLineEdit(RegisterWin);
        addressEdit->setObjectName(QString::fromUtf8("addressEdit"));
        sizePolicy.setHeightForWidth(addressEdit->sizePolicy().hasHeightForWidth());
        addressEdit->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(addressEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(RegisterWin);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        phoneEdit = new QLineEdit(RegisterWin);
        phoneEdit->setObjectName(QString::fromUtf8("phoneEdit"));
        sizePolicy.setHeightForWidth(phoneEdit->sizePolicy().hasHeightForWidth());
        phoneEdit->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(phoneEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        registerBtn = new QPushButton(RegisterWin);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(registerBtn->sizePolicy().hasHeightForWidth());
        registerBtn->setSizePolicy(sizePolicy3);
        registerBtn->setFont(font);

        horizontalLayout_6->addWidget(registerBtn);

        resetBtn = new QPushButton(RegisterWin);
        resetBtn->setObjectName(QString::fromUtf8("resetBtn"));
        sizePolicy3.setHeightForWidth(resetBtn->sizePolicy().hasHeightForWidth());
        resetBtn->setSizePolicy(sizePolicy3);
        resetBtn->setFont(font);

        horizontalLayout_6->addWidget(resetBtn);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_8->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        headpicLb = new QLabel(RegisterWin);
        headpicLb->setObjectName(QString::fromUtf8("headpicLb"));
        headpicLb->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(headpicLb);

        picfileEdit = new QLineEdit(RegisterWin);
        picfileEdit->setObjectName(QString::fromUtf8("picfileEdit"));

        verticalLayout_2->addWidget(picfileEdit);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        addpicBtn = new QPushButton(RegisterWin);
        addpicBtn->setObjectName(QString::fromUtf8("addpicBtn"));
        sizePolicy3.setHeightForWidth(addpicBtn->sizePolicy().hasHeightForWidth());
        addpicBtn->setSizePolicy(sizePolicy3);
        addpicBtn->setFont(font);

        horizontalLayout_7->addWidget(addpicBtn);

        videoswitchBtn = new QPushButton(RegisterWin);
        videoswitchBtn->setObjectName(QString::fromUtf8("videoswitchBtn"));
        sizePolicy3.setHeightForWidth(videoswitchBtn->sizePolicy().hasHeightForWidth());
        videoswitchBtn->setSizePolicy(sizePolicy3);
        videoswitchBtn->setFont(font);

        horizontalLayout_7->addWidget(videoswitchBtn);

        cameraBtn = new QPushButton(RegisterWin);
        cameraBtn->setObjectName(QString::fromUtf8("cameraBtn"));
        sizePolicy3.setHeightForWidth(cameraBtn->sizePolicy().hasHeightForWidth());
        cameraBtn->setSizePolicy(sizePolicy3);
        cameraBtn->setFont(font);

        horizontalLayout_7->addWidget(cameraBtn);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);

        horizontalLayout_8->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        retranslateUi(RegisterWin);

        QMetaObject::connectSlotsByName(RegisterWin);
    } // setupUi

    void retranslateUi(QWidget *RegisterWin)
    {
        RegisterWin->setWindowTitle(QCoreApplication::translate("RegisterWin", "Form", nullptr));
        label->setText(QCoreApplication::translate("RegisterWin", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterWin", "\346\200\247\345\210\253\357\274\232", nullptr));
        mrb->setText(QCoreApplication::translate("RegisterWin", "\347\224\267", nullptr));
        wrb->setText(QCoreApplication::translate("RegisterWin", "\345\245\263", nullptr));
        label_5->setText(QCoreApplication::translate("RegisterWin", "\347\224\237\346\227\245\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterWin", "\345\234\260\345\235\200\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterWin", "\347\224\265\350\257\235\357\274\232", nullptr));
        registerBtn->setText(QCoreApplication::translate("RegisterWin", "\346\263\250\345\206\214", nullptr));
        resetBtn->setText(QCoreApplication::translate("RegisterWin", "\351\207\215\347\275\256", nullptr));
        headpicLb->setText(QString());
        addpicBtn->setText(QCoreApplication::translate("RegisterWin", "\346\267\273\345\212\240\345\233\276\345\203\217", nullptr));
        videoswitchBtn->setText(QCoreApplication::translate("RegisterWin", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        cameraBtn->setText(QCoreApplication::translate("RegisterWin", "\346\213\215\347\205\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWin: public Ui_RegisterWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIN_H
