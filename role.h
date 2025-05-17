#ifndef ROLE_H
#define ROLE_H

#include <QObject>

class role : public QObject
{
    Q_OBJECT
public:
    explicit role(QObject *parent = nullptr);
    QString getSelectedRole() const;
    QString getAdminUsername() const;
    QString getAdminPassword() const;

signals:


private:
    QRadioButton *adminRadio;
    QRadioButton *employeeRadio;
    QLineEdit *adminUsernameEdit;
    QLineEdit *adminPasswordEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ROLE_H
