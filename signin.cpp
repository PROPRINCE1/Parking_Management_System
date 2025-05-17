#include "signin.h"
#include "ui_signin.h"
#include "createacc.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString SignIn::userRole = "";
QString SignIn::userName = "";
QString SignIn::empId = "";
QString SignIn::password = "";

SignIn::SignIn(QWidget *parent)
    : QDialog(parent), ui(new Ui::SignIn) ,  createAccWindow(new createAcc(this))
{

    ui->setupUi(this);
    setWindowTitle("Parking Management System");


// Set QLabel hyperlink text
    ui->createlink->setText("Don't have an account? <a href='createAcc'>Click here</a> to create one.");
    ui->createlink->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->createlink->setOpenExternalLinks(false);
    ui->createlink->setAutoFillBackground(true);
    ui->createlink->setFixedHeight(20);
    ui->createlink->setFixedWidth(258);
    ui->createlink->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                  "border-radius: 5px;"
                                  "border: none;");
    ui->usernameLabel->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                     "border-radius: 5px;"
                                     "border: none;");
    ui->usernameLabel->setFixedHeight(20);
    ui->usernameLabel->setFixedWidth(72);

    ui->passwordLabel->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                     "border-radius: 5px;"
                                     "border: none;");
    ui->passwordLabel->setFixedHeight(20);
    ui->passwordLabel->setFixedWidth(67);

    ui->empIdEdit->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                    "border: none;"
                                    "border-radius: 5px;");
    ui->empIdEdit->setPlaceholderText("Enter Your Employee ID...");
    ui->PasswordEdit->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                    "border: none;"
                                    "border-radius: 5px;");
    ui->PasswordEdit->setPlaceholderText("Enter Your Password...");

    // Optimal QLabel setup for images
    QPixmap img(":/images/src/PMS.png");
    ui->iconLabel->setPixmap(img.scaled(
        ui->iconLabel->width()+30,
        ui->iconLabel->height(),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
        ));
    ui->iconLabel->setAlignment(Qt::AlignCenter);

// Manual Signal Slot Connection for create account link
    connect(ui->createlink, &QLabel::linkActivated, this, &SignIn::create_account_link);
}

// Create Account Link
void SignIn::create_account_link() {
        createAccWindow->exec();
}

SignIn::~SignIn()
{
    delete ui;
    delete createAccWindow;
}

void SignIn::on_continue_2_clicked()
{

    QString empId = ui->empIdEdit->text();
    QString password = ui->PasswordEdit->text();

    if (empId.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Employee ID and password cannot be empty.");
        return;
    }

    if (verifyUser(empId, password, "accounts.json")) {
        accept();
    }

    ui->empIdEdit->clear();
    ui->PasswordEdit->clear();
}

// Reveals Data
QString SignIn::Decoder(const QString& input) {
    QString decoded;
    for (int i = 0; i < input.length(); ++i) {
        QChar c = input[i];
        int shift = (i % 5 + 1) * 2;
        decoded += QChar(c.unicode() - shift);
    }
    return decoded;
}


bool SignIn::verifyUser(const QString& employeeID, const QString& pass, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "Login Error", "Could not open users file.");
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return false;

    QJsonArray usersArray = doc.array();
    for (const QJsonValue& value : usersArray) {
        QJsonObject user = value.toObject();
        QString decodedemp = Decoder(user["employeeId"].toString());
        QString decodedPass = Decoder(user["password"].toString());

        if (decodedemp == employeeID && decodedPass == pass) {
            userRole = Decoder(user["role"].toString());
            userName = Decoder(user["username"].toString());
            empId = Decoder(user["employeeId"].toString());
            password = Decoder(user["password"].toString());
            return true;
        }
    }

    QMessageBox::warning(nullptr, "Login Failed", "Wrong Employee ID or password.");
    return false;
}
