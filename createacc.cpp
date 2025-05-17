#include "createacc.h"
#include "ui_createacc.h"
#include "signin.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

createAcc::createAcc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createAcc)
{

    ui->setupUi(this);
    setWindowTitle("Parking Management System");

    ui->CusernameLabel->setFixedHeight(20);
    ui->CusernameLabel->setFixedWidth(95);

    ui->CpasswordLabel->setFixedHeight(20);
    ui->CpasswordLabel->setFixedWidth(97);

    ui->CconfirmLabel->setFixedHeight(20);
    ui->CconfirmLabel->setFixedWidth(180);

    ui->CempIDLabel->setFixedHeight(20);
    ui->CempIDLabel->setFixedWidth(110);

    ui->CusernameLabel->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                      "border-radius: 5px;"
                                      "border: none;");
    ui->CpasswordLabel->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                      "border-radius: 5px;"
                                      "border: none;");
    ui->CconfirmLabel->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                     "border-radius: 5px;"
                                     "border: none;");
    ui->CempIDLabel->setStyleSheet("background-color: rgba(255,255,255,70%);"
                                   "border-radius: 5px;"
                                   "border: none;");

    ui->CreateUsernameEdit->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                          "border: none;"
                                          "border-radius: 5px;");
    ui->CreateUsernameEdit->setPlaceholderText("Enter Username...");

    ui->CreatePasswordEdit->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                          "border: none;"
                                          "border-radius: 5px;");
    ui->CreatePasswordEdit->setPlaceholderText("Enter Password...");

    ui->CreateConfirmPasswordEdit->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                                 "border: none;"
                                                 "border-radius: 5px;");
    ui->CreateConfirmPasswordEdit->setPlaceholderText("Confirm Password...");

    ui->CreateEmpIdEdit->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                       "border: none;"
                                       "border-radius: 5px;");
    ui->CreateEmpIdEdit->setPlaceholderText("Enter Employee ID...");


    ui->AdminRadio->setFixedWidth(60);
    ui->AdminRadio->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                  "border: none;"
                                  "border-radius: 5px;");
    ui->EmployeeRadio->setFixedWidth(75);
    ui->EmployeeRadio->setStyleSheet("background-color: rgba(255,255,255,65%);"
                                  "border: none;"
                                  "border-radius: 5px;");


    ui->CreateAccountLabel->setFixedWidth(170);
    ui->CreateAccountLabel->setFixedHeight(20);
    ui->CreateAccountLabel->setStyleSheet("background-color: rgba(0,0,0,30%);"
                                          "color: rgb(255,255,255);"
                                          "border-radius: 5px;"
                                          "border: none;");

}

createAcc::~createAcc()
{
    delete ui;
}

void createAcc::saveUser(const QString& username, const QString& password, const QString& empId, const QString& role, const QString& filePath) {
    QFile file(filePath);
    if (!file.exists()) {
        QFile newFile(filePath);
        if (newFile.open(QIODevice::WriteOnly)) {
            QJsonArray emptyArray;
            QJsonDocument emptyDoc(emptyArray);
            newFile.write(emptyDoc.toJson());
            newFile.close();
        } else {
            QMessageBox::critical(nullptr, "File Error", "Could not create users file.");
            return;
        }
    }
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "File Error", "Could not open users file.");
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::critical(nullptr, "Data Error", "Invalid data format in users file.");
        return;
    }
    QJsonArray usersArray = doc.array();
    QJsonObject newUser;
    newUser["username"] = Encoder(username);
    newUser["password"] = Encoder(password);
    newUser["employeeId"] = Encoder(empId);
    newUser["role"] = Encoder(role);

    usersArray.append(newUser);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "File Error", "Could not open users file for writing.");
        return;
    }

    QJsonDocument updatedDoc(usersArray);
    file.write(updatedDoc.toJson());
    file.close();

    QMessageBox::information(nullptr, "Success", "User added successfully!");
}

// Hides data
QString createAcc::Encoder(const QString& input) {
    QString encoded;
    for (int i = 0; i < input.length(); ++i) {
        QChar c = input[i];
        int shift = (i % 5 + 1) * 2; // Ascii value manipulation
        encoded += QChar(c.unicode() + shift);
    }
    return encoded;
}
void createAcc::on_Register_clicked()
{

    QString username = ui->CreateUsernameEdit->text();
    QString password = ui->CreatePasswordEdit->text();
    QString confirmpassword = ui->CreateConfirmPasswordEdit->text();
    QString empId = ui->CreateEmpIdEdit->text();
    QString role;

    if(ui->AdminRadio->isChecked()){
        role = "admin";
    } else if(ui->EmployeeRadio->isChecked()){
        role = "employee";
    }

    if(username.isEmpty() || password.isEmpty() || confirmpassword.isEmpty() || empId.isEmpty() || (ui->AdminRadio->isChecked() && ui->EmployeeRadio->isChecked())){

        QMessageBox::warning(nullptr,"Incomplete Data","Input fields cannot be empty!");

    } else if (password != confirmpassword){

        QMessageBox::warning(nullptr,"Password Error","Passwords do not match!");

    } else if (password.size()<8){

        QMessageBox::warning(nullptr,"Short Password","Passwords must be greater than 8 characters!");

    } else if (username.size()<5){

        QMessageBox::warning(nullptr,"Short Username","Username must be greater than 5 characters!");

    } else if((ui->AdminRadio->isChecked() && ui->EmployeeRadio->isChecked())){

        QMessageBox::warning(nullptr,"No Role","Please enter a role for the user");

    } else if(!username.isEmpty() && !password.isEmpty() &&
               !confirmpassword.isEmpty() && !empId.isEmpty() &&
               (ui->AdminRadio->isChecked() || ui->EmployeeRadio->isChecked()) &&
               isUniqueId(empId)){

        saveUser(username,password,empId,role,"accounts.json");

        emit registerClicked();
    }
}

bool createAcc::isUniqueId(const QString& empId){

    QFile file("accounts.json");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(doc.isArray()){
            QJsonArray userArray = doc.array();
            for(const QJsonValue &val : userArray){
                QJsonObject obj = val.toObject();
                if(obj.contains("employeeId") && SignIn::Decoder(obj["employeeId"].toString()) == empId){
                    qDebug() << "Comparing:" << obj["employeeId"].toString() << "with" << empId;

                    QMessageBox::warning(nullptr, "Duplicate Employee ID", "This employee ID already exists!");
                    return false;
                }
            }
        }
    }
    return true;
}


void createAcc::on_BackButton_clicked()
{
    this->reject();
}

