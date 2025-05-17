#include "logmanager.h"
#include "signin.h"
#include "createacc.h"
#include "mainwindow.h"
#include <QDateTime>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>

logmanager::logmanager(QTableWidget *tableWidget, QObject *parent)
    : QObject(parent), logTable(tableWidget)
{}
logmanager::logmanager(QObject *parent)
    : QObject(parent)
{}

// Display log table of Vehicles
void logmanager::addLogEntry(const QString &licensePlate,const QString &type,
                             const QString &slotID,const QString &status)
{
    int row = logTable->rowCount();
    logTable->insertRow(row);
    QString time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    logTable->setItem(row, 0, new QTableWidgetItem(licensePlate));
    logTable->setItem(row, 1, new QTableWidgetItem(type));
    logTable->setItem(row, 2, new QTableWidgetItem(slotID));
    logTable->setItem(row, 3, new QTableWidgetItem(time));
    logTable->setItem(row, 4, new QTableWidgetItem(status));
}

// Vehicle Log manager functions
void logmanager::saveLogToJSON(const QString &filename) {
    QJsonArray logArray;

    for (int row = 0; row < logTable->rowCount(); ++row) {
        QJsonObject logEntry;
        logEntry["licensePlate"] = logTable->item(row, 0)->text();
        logEntry["type"] = logTable->item(row, 1)->text();
        logEntry["slotID"] = logTable->item(row, 2)->text();
        logEntry["time"] = logTable->item(row, 3)->text();
        logEntry["status"] = logTable->item(row, 4)->text();

        logArray.append(logEntry);
    }

    QJsonDocument doc(logArray);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void logmanager::loadLogFromJSON(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
        return;

    QJsonArray logArray = doc.array();

    for(const QJsonValue &value : logArray) {
        QJsonObject obj = value.toObject();
        int row = logTable->rowCount();
        logTable->insertRow(row);
        logTable->setItem(row, 0, new QTableWidgetItem(obj["licensePlate"].toString()));
        logTable->setItem(row, 1, new QTableWidgetItem(obj["type"].toString()));
        logTable->setItem(row, 2, new QTableWidgetItem(obj["slotID"].toString()));
        logTable->setItem(row, 3, new QTableWidgetItem(obj["time"].toString()));
        logTable->setItem(row, 4, new QTableWidgetItem(obj["status"].toString()));
    }
}

void logmanager::loadLogFromJSON(int id,const QString &filename) {


    logTable->setRowCount(0);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
        return;

    QJsonArray logArray = doc.array();

    for(const QJsonValue &value : logArray) {
        QJsonObject obj = value.toObject();


        int row = logTable->rowCount();
        logTable->insertRow(row);
        logTable->setItem(row, 0, new QTableWidgetItem(SignIn::Decoder((obj["employeeId"].toString()))));
        logTable->setItem(row, 1, new QTableWidgetItem(SignIn::Decoder((obj["username"].toString()))));
        logTable->setItem(row, 2, new QTableWidgetItem(SignIn::Decoder((obj["role"].toString()))));
        logTable->setItem(row, 3, new QTableWidgetItem(SignIn::Decoder((obj["password"].toString()))));

        QTableWidgetItem* checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(Qt::Unchecked);
        logTable->setItem(row, 4, checkItem);
    }
}

QString logmanager::getEntryTimeIfParked(const QString& licensePlate, const QString& jsonFilePath) {
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return "Error opening file";
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (doc.isNull() || !doc.isArray()) {
        return "JSON parse error";
    }

    QJsonArray logs = doc.array();
    for (int i = logs.size() - 1; i >= 0; --i) {
        QJsonObject log = logs.at(i).toObject();
        if (log["license_plate"].toString() == licensePlate) {
            QString action = log["action"].toString();
            if (action == "enter") {
                return log["timestamp"].toString();
            } else {
                return "No such vehicle exists";
            }
        }
    }

    return "No such vehicle exists";
}

bool logmanager::isVehicleCurrentlyParked(const QString& licensePlate, const QString& vehicleType, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "File Error", "Failed to open JSON file:\n" + file.errorString());
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        QMessageBox::critical(nullptr, "Parse Error", "JSON parse error:\n" + parseError.errorString());
        return false;
    }

    if (!doc.isArray()) {
        QMessageBox::critical(nullptr, "Data Error", "Expected a JSON array at root.");
        return false;
    }

    QJsonArray entries = doc.array();
    QString lastStatus;
    bool foundPlate = false;

    for (const QJsonValue& value : entries) {
        QJsonObject obj = value.toObject();
        QString plate = obj["licensePlate"].toString();
        QString type = obj["type"].toString(); // Add type check here
        QString status = obj["status"].toString(); // "entry" or "exit"

        if (plate == licensePlate && type.toLower() == vehicleType.toLower()) {
            lastStatus = status;
            foundPlate = true;
        }
    }

    if (!foundPlate) {
        QMessageBox::warning(nullptr, "Vehicle Not Found", "No such vehicle exists in the parking lot.");
        return false;
    }

    if (lastStatus.toLower() != "entry") {
        QMessageBox::information(nullptr, "Vehicle Already Exited", "The vehicle has already exited the parking lot.");
        return false;
    }

    return true;
}

void logmanager::saveSlotstoJSON(int car,int bike, int truck,int ec,int eb,const QString& filepath){
    QJsonObject slotsEntry;

    slotsEntry["Car"] = car;
    slotsEntry["Bike"] = bike;
    slotsEntry["Truck"] = truck;
    slotsEntry["Electric Car"] = ec;
    slotsEntry["Electric Bike"] = eb;

    QJsonDocument doc(slotsEntry);
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

bool logmanager::loadSlotsfromJSON(const QString& filename, MainWindow* window) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "load slots from JSON function Failed to open file for reading:" << filename;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isObject()) {
        qDebug() << "Invalid JSON document";
        return false;
    }

    QJsonObject jsonObj = doc.object();

    int car   = jsonObj.value("Car").toInt(20);
    int bike  = jsonObj.value("Bike").toInt(20);
    int truck = jsonObj.value("Truck").toInt(20);
    int ec    = jsonObj.value("Electric Car").toInt(20);
    int eb    = jsonObj.value("Electric Bike").toInt(20);

    if (window) {
        window->initializeSlots(car, bike, truck, ec, eb);
    }

    return true;
}

void logmanager::updateUser(const QString& username, const QString& password, const QString& empId, const QString& filePath) {
    QFile file(filePath);
    if (!file.exists()) {
        QMessageBox::critical(nullptr, "File Error", "Users file does not exist.");
        return;
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
    bool userFound = false;

    for (QJsonValueRef userVal : usersArray) {
        QJsonObject obj = userVal.toObject();
        if (SignIn::Decoder(obj["employeeId"].toString()) == empId) {
            obj["username"] = createAcc::Encoder(username);
            obj["password"] = createAcc::Encoder(password);
            userVal = obj;
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        QMessageBox::warning(nullptr, "User Not Found", "No user with the given employee ID was found.");
        return;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "File Error", "Could not open users file for writing.");
        return;
    }

    QJsonDocument updatedDoc(usersArray);
    file.write(updatedDoc.toJson());
    file.close();

    QMessageBox::information(nullptr, "Success", "User credentials updated successfully!");
}


bool logmanager::deleteUserFromJSON(const QString& filename, const QString& employeeId) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading";
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format (not an array)";
        return false;
    }

    QJsonArray array = doc.array();
    QJsonArray updatedArray;
    bool found = false;
    for (const QJsonValue& val : array) {
        QJsonObject obj = val.toObject();
        if ((obj["employeeId"].toString()) != createAcc::Encoder(employeeId)) {
            updatedArray.append(obj);
        } else {
            found = true;
        }
    }

    if (!found) {
        qDebug() << "No user with EmployeeID:" << employeeId;
        return false;
    }

    QFile outFile(filename);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing";
        return false;
    }

    QJsonDocument updatedDoc(updatedArray);
    outFile.write(updatedDoc.toJson(QJsonDocument::Indented));
    outFile.close();

    return true;
}
