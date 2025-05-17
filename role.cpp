#include "role.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

RoleDialog::RoleDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Select Role and Authenticate");

    adminRadio = new QRadioButton("Admin");
    employeeRadio = new QRadioButton("Employee");
    employeeRadio->setChecked(true);  // Default

    adminUsernameEdit = new QLineEdit;
    adminPasswordEdit = new QLineEdit;
    adminPasswordEdit->setEchoMode(QLineEdit::Password);

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Select role for the new account:"));
    layout->addWidget(adminRadio);
    layout->addWidget(employeeRadio);

    layout->addWidget(new QLabel("Enter Admin Username:"));
    layout->addWidget(adminUsernameEdit);
    layout->addWidget(new QLabel("Enter Admin Password:"));
    layout->addWidget(adminPasswordEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

QString RoleDialog::getSelectedRole() const {
    return adminRadio->isChecked() ? "admin" : "employee";
}

QString RoleDialog::getAdminUsername() const {
    return adminUsernameEdit->text();
}

QString RoleDialog::getAdminPassword() const {
    return adminPasswordEdit->text();
}
