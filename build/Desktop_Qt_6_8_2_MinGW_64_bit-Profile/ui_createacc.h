/********************************************************************************
** Form generated from reading UI file 'createacc.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACC_H
#define UI_CREATEACC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_createAcc
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *CreateAccountLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *CusernameLabel;
    QHBoxLayout *horizontalLayout;
    QLineEdit *CreateUsernameEdit;
    QLabel *CpasswordLabel;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *CreatePasswordEdit;
    QLabel *CconfirmLabel;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *CreateConfirmPasswordEdit;
    QLabel *CempIDLabel;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *CreateEmpIdEdit;
    QHBoxLayout *horizontalLayout_9;
    QRadioButton *AdminRadio;
    QRadioButton *EmployeeRadio;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Register;
    QPushButton *BackButton;

    void setupUi(QDialog *createAcc)
    {
        if (createAcc->objectName().isEmpty())
            createAcc->setObjectName("createAcc");
        createAcc->resize(450, 450);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createAcc->sizePolicy().hasHeightForWidth());
        createAcc->setSizePolicy(sizePolicy);
        createAcc->setMinimumSize(QSize(450, 450));
        createAcc->setMaximumSize(QSize(450, 450));
        createAcc->setStyleSheet(QString::fromUtf8("#createAcc{\n"
"	background-image: url(:/images/src/login.png);\n"
"	background-repeat: no-repeat;\n"
"	background-position: center;\n"
"	background-attachment: fixed;\n"
"	background-color: rgba(128,128,128,100);\n"
"}"));
        verticalLayout = new QVBoxLayout(createAcc);
        verticalLayout->setObjectName("verticalLayout");
        CreateAccountLabel = new QLabel(createAcc);
        CreateAccountLabel->setObjectName("CreateAccountLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        font.setStrikeOut(false);
        CreateAccountLabel->setFont(font);
        CreateAccountLabel->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";\n"
""));
        CreateAccountLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(CreateAccountLabel, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        CusernameLabel = new QLabel(createAcc);
        CusernameLabel->setObjectName("CusernameLabel");
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        CusernameLabel->setFont(font1);

        verticalLayout_2->addWidget(CusernameLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        CreateUsernameEdit = new QLineEdit(createAcc);
        CreateUsernameEdit->setObjectName("CreateUsernameEdit");
        CreateUsernameEdit->setMaximumSize(QSize(300, 16777215));

        horizontalLayout->addWidget(CreateUsernameEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        CpasswordLabel = new QLabel(createAcc);
        CpasswordLabel->setObjectName("CpasswordLabel");
        CpasswordLabel->setFont(font1);

        verticalLayout_2->addWidget(CpasswordLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        CreatePasswordEdit = new QLineEdit(createAcc);
        CreatePasswordEdit->setObjectName("CreatePasswordEdit");
        CreatePasswordEdit->setMaximumSize(QSize(300, 16777215));
        CreatePasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_5->addWidget(CreatePasswordEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        CconfirmLabel = new QLabel(createAcc);
        CconfirmLabel->setObjectName("CconfirmLabel");
        CconfirmLabel->setFont(font1);

        verticalLayout_2->addWidget(CconfirmLabel);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        CreateConfirmPasswordEdit = new QLineEdit(createAcc);
        CreateConfirmPasswordEdit->setObjectName("CreateConfirmPasswordEdit");
        CreateConfirmPasswordEdit->setMaximumSize(QSize(300, 16777215));
        CreateConfirmPasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_6->addWidget(CreateConfirmPasswordEdit);


        verticalLayout_2->addLayout(horizontalLayout_6);

        CempIDLabel = new QLabel(createAcc);
        CempIDLabel->setObjectName("CempIDLabel");
        CempIDLabel->setFont(font1);

        verticalLayout_2->addWidget(CempIDLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        CreateEmpIdEdit = new QLineEdit(createAcc);
        CreateEmpIdEdit->setObjectName("CreateEmpIdEdit");
        CreateEmpIdEdit->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_4->addWidget(CreateEmpIdEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        AdminRadio = new QRadioButton(createAcc);
        AdminRadio->setObjectName("AdminRadio");

        horizontalLayout_9->addWidget(AdminRadio);

        EmployeeRadio = new QRadioButton(createAcc);
        EmployeeRadio->setObjectName("EmployeeRadio");

        horizontalLayout_9->addWidget(EmployeeRadio);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Register = new QPushButton(createAcc);
        Register->setObjectName("Register");
        Register->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setBold(true);
        Register->setFont(font2);

        horizontalLayout_3->addWidget(Register);

        BackButton = new QPushButton(createAcc);
        BackButton->setObjectName("BackButton");
        BackButton->setFont(font2);

        horizontalLayout_3->addWidget(BackButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);
        verticalLayout_2->setStretch(4, 1);
        verticalLayout_2->setStretch(5, 1);
        verticalLayout_2->setStretch(6, 1);
        verticalLayout_2->setStretch(7, 1);
        verticalLayout_2->setStretch(8, 1);

        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(createAcc);

        QMetaObject::connectSlotsByName(createAcc);
    } // setupUi

    void retranslateUi(QDialog *createAcc)
    {
        createAcc->setWindowTitle(QCoreApplication::translate("createAcc", "Dialog", nullptr));
        CreateAccountLabel->setText(QCoreApplication::translate("createAcc", "Create Account", nullptr));
        CusernameLabel->setText(QCoreApplication::translate("createAcc", "USERNAME", nullptr));
        CpasswordLabel->setText(QCoreApplication::translate("createAcc", "PASSWORD", nullptr));
        CconfirmLabel->setText(QCoreApplication::translate("createAcc", "CONFIRM PASSWORD", nullptr));
        CempIDLabel->setText(QCoreApplication::translate("createAcc", "EMPLOYEE ID", nullptr));
        AdminRadio->setText(QCoreApplication::translate("createAcc", "Admin", nullptr));
        EmployeeRadio->setText(QCoreApplication::translate("createAcc", "Employee", nullptr));
        Register->setText(QCoreApplication::translate("createAcc", "REGISTER", nullptr));
        BackButton->setText(QCoreApplication::translate("createAcc", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createAcc: public Ui_createAcc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACC_H
