/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SignIn
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *iconLabel;
    QGridLayout *gridLayout_2;
    QLabel *passwordLabel;
    QLineEdit *empIdEdit;
    QLabel *usernameLabel;
    QLineEdit *PasswordEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *continue_2;
    QPushButton *exitbutton;
    QLabel *createlink;

    void setupUi(QDialog *SignIn)
    {
        if (SignIn->objectName().isEmpty())
            SignIn->setObjectName("SignIn");
        SignIn->setEnabled(true);
        SignIn->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SignIn->sizePolicy().hasHeightForWidth());
        SignIn->setSizePolicy(sizePolicy);
        SignIn->setMinimumSize(QSize(400, 300));
        SignIn->setMaximumSize(QSize(400, 300));
        SignIn->setStyleSheet(QString::fromUtf8("#SignIn{\n"
"	background-image: url(:/images/src/login.png);\n"
"	background-repeat: no-repeat;\n"
"	background-position: center;\n"
"	background-attachment: fixed;\n"
"	background-color: rgba(128,128,128,100);\n"
"}"));
        gridLayout = new QGridLayout(SignIn);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        iconLabel = new QLabel(SignIn);
        iconLabel->setObjectName("iconLabel");
        iconLabel->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(iconLabel, 0, Qt::AlignmentFlag::AlignVCenter);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        passwordLabel = new QLabel(SignIn);
        passwordLabel->setObjectName("passwordLabel");
        QFont font;
        font.setBold(true);
        passwordLabel->setFont(font);

        gridLayout_2->addWidget(passwordLabel, 2, 0, 1, 1);

        empIdEdit = new QLineEdit(SignIn);
        empIdEdit->setObjectName("empIdEdit");

        gridLayout_2->addWidget(empIdEdit, 1, 0, 1, 1);

        usernameLabel = new QLabel(SignIn);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setFont(font);

        gridLayout_2->addWidget(usernameLabel, 0, 0, 1, 1);

        PasswordEdit = new QLineEdit(SignIn);
        PasswordEdit->setObjectName("PasswordEdit");
        PasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout_2->addWidget(PasswordEdit, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        continue_2 = new QPushButton(SignIn);
        continue_2->setObjectName("continue_2");
        continue_2->setEnabled(true);

        horizontalLayout->addWidget(continue_2);

        exitbutton = new QPushButton(SignIn);
        exitbutton->setObjectName("exitbutton");

        horizontalLayout->addWidget(exitbutton);


        gridLayout_2->addLayout(horizontalLayout, 4, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        createlink = new QLabel(SignIn);
        createlink->setObjectName("createlink");
        createlink->setTextInteractionFlags(Qt::TextInteractionFlag::TextSelectableByMouse);

        verticalLayout->addWidget(createlink);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        passwordLabel->setBuddy(PasswordEdit);
        usernameLabel->setBuddy(empIdEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(SignIn);
        QObject::connect(exitbutton, &QPushButton::clicked, SignIn, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(SignIn);
    } // setupUi

    void retranslateUi(QDialog *SignIn)
    {
        SignIn->setWindowTitle(QCoreApplication::translate("SignIn", "Dialog", nullptr));
        iconLabel->setText(QString());
        passwordLabel->setText(QCoreApplication::translate("SignIn", "PASSWORD", nullptr));
        usernameLabel->setText(QCoreApplication::translate("SignIn", "Employee ID", nullptr));
        continue_2->setText(QCoreApplication::translate("SignIn", "Login", nullptr));
        exitbutton->setText(QCoreApplication::translate("SignIn", "Exit", nullptr));
        createlink->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignIn: public Ui_SignIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
