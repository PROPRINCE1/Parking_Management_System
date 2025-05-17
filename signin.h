#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include "mainwindow.h"
#include "createacc.h"

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    static QString userRole;
    static QString userName;
    static QString empId;
    static QString password;
    ~SignIn();

public slots:
    static QString Decoder(const QString& msg);

private slots:
    void create_account_link();

    void on_continue_2_clicked();

    bool verifyUser(const QString& username, const QString& password, const QString& filePath);


private:
    Ui::SignIn *ui;

    createAcc *createAccWindow;

};

#endif // SIGNIN_H
