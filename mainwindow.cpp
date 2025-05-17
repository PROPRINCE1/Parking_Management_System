#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_signin.h"
#include "CarParkingSpace.h"
#include "lcdmanager.h"
#include "logmanager.h"
#include "ParkingLot.h"
#include "ParkingManager.h"
#include "parkingslip.h"
#include "signin.h"
#include <QApplication>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>
#include <QDebug>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("Parking Management System");


    ui->setupUi(this);

    slotlog = new logmanager(this);

    if(slotlog->loadSlotsfromJSON("slots.json",this)){
        carCount=carTotal;
        bikeCount=bikeTotal;
        truckCount=truckTotal;
        ecCount=ecTotal;
        ebCount=ebTotal;
    }

    pl = new ParkingLot(carTotal,bikeTotal,truckTotal,ecTotal,ebTotal);
    pm = new ParkingManager(pl);


    ui->carspinBox->setValue(carTotal);
    ui->bikespinBox->setValue(bikeTotal);
    ui->truckspinBox->setValue(truckTotal);
    ui->evcspinBox->setValue(ecTotal);
    ui->evbspinBox->setValue(ebTotal);

    totalSpace=carTotal+bikeTotal+truckTotal+ecTotal+ebTotal;


    lcdm_1 = new lcdmanager(ui->CarLCD, ui->BikeLCD, ui->TruckLCD, ui->ECLCD, ui->EBLCD, this);
    lcdm_2 = new lcdmanager(ui->CarLCD_2, ui->BikeLCD_2, ui->TruckLCD_2, ui->ECLCD_2, ui->EBLCD_2, this);
    lcdm_3 = new lcdmanager(ui->CarLCD_3, ui->BikeLCD_3, ui->TruckLCD_3, ui->ECLCD_3, ui->EBLCD_3, this);

    lcdm_1->updateLcds(carCount,bikeCount,truckCount,ecCount,ebCount);
    lcdm_2->updateLcds(carCount,bikeCount,truckCount,ecCount,ebCount);
    lcdm_3->updateLcds(carTotal,bikeTotal,truckTotal,ecTotal,ebTotal);

    ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));

    vehiclelog = new logmanager(ui->logTable, this);
    vehiclelog->loadLogFromJSON("logdata.json");

    userlog = new logmanager(ui->userlogtable, this);
    userlog->loadLogFromJSON(1,"accounts.json");

    ui->ChangeusernameEdit->setPlaceholderText(SignIn::userName);
    ui->ChangepasswordEdit->setPlaceholderText("*******");
    ui->CurrentpasswordEdit->setPlaceholderText("Enter Current Password");

// Tabs Names

    ui->tabWidget->setTabText(0, "Vehicle Entry");
    ui->tabWidget->setTabText(1, "Vehicle Exit");
    ui->tabWidget->setTabText(2, "Parking Slots");
    ui->tabWidget->setTabText(3, "Log");
    ui->tabWidget->setTabText(4, "Settings");

    QString role = SignIn::userRole;
    int userlogidx = ui->tabWidget->count()-1;

    if (role == "admin") {
        ui->tabWidget->setTabVisible(userlogidx, true);
        ui->tabWidget->setTabText(userlogidx,"UserLog");
        ui->label_12->setText("Settings (Admin)");
    } else {
        ui->tabWidget->setTabVisible(userlogidx, false);
        ui->label_12->setText("Settings (Employee)");
    }

// Tabs Names

// TableWidget
    // Log Table
    ui->logTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList headers;
    headers << "License Plate" << "Vehicle Type" << "Slot ID" << "Time,Date" << "Status";

    ui->logTable->setHorizontalHeaderLabels(headers);

    // User Log Table
    ui->userlogtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList headers2;
    headers2 << "Employee No" << "Username" << "Role" << "Password" << "Select";
    ui->userlogtable->setHorizontalHeaderLabels(headers2);

    for (int row = 0; row < ui->userlogtable->rowCount(); ++row) {
        QTableWidgetItem* roleItem = ui->userlogtable->item(row, 2);
        if (roleItem && roleItem->text().toLower() != "admin") {
            QTableWidgetItem* checkBoxItem = new QTableWidgetItem();
            checkBoxItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            checkBoxItem->setCheckState(Qt::Unchecked);
            ui->userlogtable->setItem(row, 4, checkBoxItem);
        }
    }


// TableWidget

// Date And Time Status Bar

    QLabel *clockLabel = new QLabel(this);
    ui->statusBar->addPermanentWidget(clockLabel);

    QTimer *timer = new QTimer(this);  // 'this' is the parent widget
    connect(timer, &QTimer::timeout, this, [=]() {
        QDateTime current = QDateTime::currentDateTime();
        QString timeText = current.toString("dd-MM-yyyy  |  hh:mm:ss");
        clockLabel->setText(timeText);
    });
    timer->start(1000);


// Date And Time Status Bar

// Admin Editable section
    if(role == "admin"){
        ui->adminAccessOnly->setStyleSheet(""); // Remove any previously applied styles
        ui->adminAccessOnly->setEnabled(true);
    } else {
        ui->adminAccessOnly->setStyleSheet("background-color: rgba(128,128,128,0.4);");
        ui->adminAccessOnly->setEnabled(false);
    }
// Admin Editable section

    ui->CarEntryEdit->setPlaceholderText("abc-123");
    ui->CarExitEdit->setPlaceholderText("abc-123");

    ui->BikeEntryEdit->setPlaceholderText("abc-123");
    ui->BikeExitEdit->setPlaceholderText("abc-123");

    ui->TruckEntryEdit->setPlaceholderText("abc-123");
    ui->TruckExitEdit->setPlaceholderText("abc-123");

    ui->ECEntryEdit->setPlaceholderText("abc-123");
    ui->ECExitEdit->setPlaceholderText("abc-123");

    ui->EBEntryEdit->setPlaceholderText("abc-123");
    ui->EBExitEdit->setPlaceholderText("abc-123");

    ui->CarButton->setStyleSheet("background-color: rgb(0, 156, 0);""font: 700 20pt Segoe UI;""color: #eeeeee;");
    ui->CarButton_2->setStyleSheet("background-color: #d50000 ;""font: 700 20pt Segoe UI;""color: #eeeeee;");

    ui->BikeButton->setStyleSheet("background-color: rgb(0, 156, 0);""font: 700 20pt Segoe UI;""color: #eeeeee;");
    ui->BikeButton_2->setStyleSheet("background-color: #d50000 ;""font: 700 20pt Segoe UI;""color: #eeeeee;");

    ui->TruckButton->setStyleSheet("background-color: rgb(0, 156, 0);""font: 700 20pt Segoe UI;""color: #eeeeee;");
    ui->TruckButton_2->setStyleSheet("background-color: #d50000 ;""font: 700 20pt Segoe UI;""color: #eeeeee;");

    ui->ECButton->setStyleSheet("background-color: rgb(0, 156, 0);""font: 700 20pt Segoe UI;""color: #eeeeee;");
    ui->ECButton_2->setStyleSheet("background-color: #d50000 ;""font: 700 20pt Segoe UI;""color: #eeeeee;");

    ui->EBButton->setStyleSheet("background-color: rgb(0, 156, 0);""font: 700 20pt Segoe UI;""color: #eeeeee;");
    ui->EBButton_2->setStyleSheet("background-color: #d50000 ;""font: 700 20pt Segoe UI;""color: #eeeeee;");


}

// Vehicle Entry
void MainWindow::on_CarButton_clicked()
{
    QString text = ui->CarEntryEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    } else if(carCount == 0) {
        QMessageBox::warning(this, "Input Error", "No More Space in Lot Available.");
    } else {

        pm->parkVehicle("Car",text);

        // Print Slip
        parkingslip slip(text, "Car",QString::number(pm->getSpaceIdForLicensePlate(text)),QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"car",QString::number(pm->getSpaceIdForLicensePlate(text)),"entry");
        vehiclelog->saveLogToJSON("logdata.json");
        carCount--;
        lcdm_1->updateLcds(1,carCount);
        lcdm_2->updateLcds(1,carCount);
        lcdm_3->updateLcds(1,carCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));

    }
    ui->CarEntryEdit->clear();
}
void MainWindow::on_BikeButton_clicked()
{
    QString text = ui->BikeEntryEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    }  else if(bikeCount == 0) {
        QMessageBox::warning(this, "Input Error", "No More Space in Lot Available.");
    } else {

        pm->parkVehicle("Motorcycle",text);

        // Print Slip
        parkingslip slip(text, "Bike", QString::number(pm->getSpaceIdForLicensePlate(text)),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"bike",QString::number(pm->getSpaceIdForLicensePlate(text)),"entry");
        vehiclelog->saveLogToJSON("logdata.json");
        bikeCount--;
        lcdm_1->updateLcds(2,bikeCount);
        lcdm_2->updateLcds(2,bikeCount);
        lcdm_3->updateLcds(2,bikeCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));

    }
    ui->BikeEntryEdit->clear();
}
void MainWindow::on_TruckButton_clicked()
{
    QString text = ui->TruckEntryEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    }  else if(truckCount == 0) {
        QMessageBox::warning(this, "Input Error", "No More Space in Lot Available.");
    } else {

        pm->parkVehicle("Truck",text);

        // Print Slip
        parkingslip slip(text, "Truck",QString::number(pm->getSpaceIdForLicensePlate(text)),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"truck",QString::number(pm->getSpaceIdForLicensePlate(text)),"entry");
        vehiclelog->saveLogToJSON("logdata.json");
        truckCount--;
        lcdm_1->updateLcds(3,truckCount);
        lcdm_2->updateLcds(3,truckCount);
        lcdm_3->updateLcds(3,truckCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->TruckEntryEdit->clear();
}
void MainWindow::on_ECButton_clicked()
{
    QString text = ui->ECEntryEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    }  else if(ecCount == 0) {
        QMessageBox::warning(this, "Input Error", "No More Space in Lot Available.");
    } else {

        pm->parkVehicle("EV Car",text);

        // Print Slip
        parkingslip slip(text, "Electric Car",QString::number(pm->getSpaceIdForLicensePlate(text)),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"electric car",QString::number(pm->getSpaceIdForLicensePlate(text)),"entry");
        vehiclelog->saveLogToJSON("logdata.json");
        ecCount--;
        lcdm_1->updateLcds(4,ecCount);
        lcdm_2->updateLcds(4,ecCount);
        lcdm_3->updateLcds(4,ecCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->ECEntryEdit->clear();
}
void MainWindow::on_EBButton_clicked()
{
    QString text = ui->EBEntryEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    }  else if(ebCount == 0) {
        QMessageBox::warning(this, "Input Error", "No More Space in Lot Available.");
    } else {

        pm->parkVehicle("EV Motorcycle",text);
        // Print Slip
        parkingslip slip(text, "Electric Bike", QString::number(pm->getSpaceIdForLicensePlate(text)),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"electric bike",QString::number(pm->getSpaceIdForLicensePlate(text)),"entry");
        vehiclelog->saveLogToJSON("logdata.json");
        ebCount--;
        lcdm_1->updateLcds(5,ebCount);
        lcdm_2->updateLcds(5,ebCount);
        lcdm_3->updateLcds(5,ebCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->EBEntryEdit->clear();
}
// Vehicle Entry

// Vehicle Exit
void MainWindow::on_CarButton_2_clicked()
{
    QString text = ui->CarExitEdit->text();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    } else if(vehiclelog->isVehicleCurrentlyParked(text,"car","logdata.json")){
        // Print Slip
        int spaceId = pm->getSpaceIdForLicensePlate(text);
        parkingslip slip(text, "Car",QString::number(spaceId),pm->removeVehicle(text),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"car",QString::number(spaceId),"exit");
        vehiclelog->saveLogToJSON("logdata.json");

        carCount++;
        lcdm_1->updateLcds(1,carCount);
        lcdm_2->updateLcds(1,carCount);
        lcdm_3->updateLcds(1,carCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->CarExitEdit->clear();
}

void MainWindow::on_BikeButton_2_clicked()
{
    QString text = ui->BikeExitEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    } else if(vehiclelog->isVehicleCurrentlyParked(text,"bike","logdata.json")){

        // Print Slip
        int spaceId = pm->getSpaceIdForLicensePlate(text);
        parkingslip slip(text, "Bike", QString::number(spaceId),pm->removeVehicle(text),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"bike",QString::number(spaceId),"exit");
        vehiclelog->saveLogToJSON("logdata.json");



        bikeCount++;
        lcdm_1->updateLcds(2,bikeCount);
        lcdm_2->updateLcds(2,bikeCount);
        lcdm_3->updateLcds(2,bikeCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->BikeExitEdit->clear();
}
void MainWindow::on_TruckButton_2_clicked()
{
    QString text = ui->TruckExitEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    } else if(vehiclelog->isVehicleCurrentlyParked(text,"truck","logdata.json")){
        // Print Slip
        int spaceId = pm->getSpaceIdForLicensePlate(text);
        parkingslip slip(text, "Truck",QString::number(spaceId),pm->removeVehicle(text),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"truck",QString::number(spaceId),"exit");
        vehiclelog->saveLogToJSON("logdata.json");

        truckCount++;

        lcdm_1->updateLcds(3,truckCount);
        lcdm_2->updateLcds(3,truckCount);
        lcdm_3->updateLcds(3,truckCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->TruckExitEdit->clear();
}
void MainWindow::on_ECButton_2_clicked()
{
    QString text = ui->ECExitEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    } else if(vehiclelog->isVehicleCurrentlyParked(text,"electric car","logdata.json")){

        // Print Slip
        int spaceId = pm->getSpaceIdForLicensePlate(text);
        parkingslip slip(text, "Electric Car", QString::number(spaceId),pm->removeVehicle(text),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

       vehiclelog->addLogEntry(text,"electric car",QString::number(spaceId),"exit");
       vehiclelog->saveLogToJSON("logdata.json");

        ecCount++;

        lcdm_1->updateLcds(4,ecCount);
        lcdm_2->updateLcds(4,ecCount);
        lcdm_3->updateLcds(4,ecCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->ECExitEdit->clear();
}
void MainWindow::on_EBButton_2_clicked()
{
    QString text = ui->EBExitEdit->text();

    // Check if the text is empty
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "The field cannot be empty.");
    } else if(vehiclelog->isVehicleCurrentlyParked(text,"electric bike","logdata.json")){


        // Print Slip
        int spaceId = pm->getSpaceIdForLicensePlate(text);
        parkingslip slip(text, "Electric Bike",QString::number(spaceId),pm->removeVehicle(text),
                         QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
        slip.exec();
        // Print Slip

        vehiclelog->addLogEntry(text,"electric bike",QString::number(spaceId),"exit");
        vehiclelog->saveLogToJSON("logdata.json");

        ebCount++;

        lcdm_1->updateLcds(5,ebCount);
        lcdm_2->updateLcds(5,ebCount);
        lcdm_3->updateLcds(5,ebCount);
        ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));
    }
    ui->EBExitEdit->clear();
}
// Vehicle Exit


MainWindow::~MainWindow()
{
    delete vehiclelog;
    delete userlog;
    delete slotlog;
    delete lcdm_1;
    delete lcdm_2;
    delete lcdm_3;
    delete pl;
    delete pm;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    vehiclelog->saveLogToJSON("logdata.json");
    QMainWindow::closeEvent(event);
}

int MainWindow::totalSlots(int a,int b,int c,int d,int e) { return a+b+c+d+e; }

void MainWindow::on_logOutButton_clicked()
{
    loggedOut = true;
    close();
}


void MainWindow::on_AddButton_clicked()
{
    createAcc *accountWindow = new createAcc(this);
    accountWindow->setAttribute(Qt::WA_DeleteOnClose);
    accountWindow->show();
    connect(accountWindow, &createAcc::registerClicked, this, [=]() {
        userlog->loadLogFromJSON(1, "accounts.json");
    });
    for (int row = 0; row < ui->userlogtable->rowCount(); ++row) {
        QTableWidgetItem* checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);
        ui->userlogtable->setItem(row, 4, checkBoxItem);
    }
}

void MainWindow::on_saveSettingsButton_clicked()
{

    if(ui->carspinBox->text().toInt() < (carTotal-carCount) ){
        QMessageBox::warning(this,"Invalid Data","Currently Parked Cars Exceed the new value\nUnable to save data");
        return;
    }
    if(ui->bikespinBox->text().toInt() < (bikeTotal-bikeCount) ){
        QMessageBox::warning(this,"Invalid Data","Currently Parked Cars Exceed the new value\nUnable to save data");
        return;
    }
    if(ui->truckspinBox->text().toInt() < (truckTotal-truckCount) ){
        QMessageBox::warning(this,"Invalid Data","Currently Parked Cars Exceed the new value\nUnable to save data");
        return;
    }
    if(ui->evcspinBox->text().toInt() < (ecTotal-ecCount) ){
        QMessageBox::warning(this,"Invalid Data","Currently Parked Cars Exceed the new value\nUnable to save data");
        return;
    }
    if(ui->evbspinBox->text().toInt() < (ebTotal-ebCount) ){
        QMessageBox::warning(this,"Invalid Data","Currently Parked Cars Exceed the new value\nUnable to save data");
        return;
    }


    QString newUser = ui->ChangeusernameEdit->text().trimmed();
    QString newPass = ui->ChangepasswordEdit->text().trimmed();
    QString currPass = ui->CurrentpasswordEdit->text().trimmed();

    bool userChanged = !newUser.isEmpty() && newUser != SignIn::userName;
    bool passChanged = !newPass.isEmpty() && newPass != SignIn::password;

    if (userChanged || passChanged) {
        if (currPass != SignIn::password) {
            QMessageBox::warning(this, "Authentication Failed", "Current password is incorrect.");
            return;
        }

        if (!userChanged) newUser = SignIn::userName;
        if (!passChanged) newPass = SignIn::password;

        userlog->updateUser(newUser, newPass, SignIn::empId, "accounts.json");
        userlog->loadLogFromJSON(1,"accounts.json");

        SignIn::userName = newUser;
        SignIn::password = newPass;

        if(SignIn::userRole == "employee"){
            QMessageBox::information(this, "Success", "Account information updated successfully!");
        }
    }


    carCount=carTotal-carCount;
    bikeCount=bikeTotal-bikeCount;
    truckCount=truckTotal-truckCount;
    ecCount=ecTotal-ecCount;
    ebCount=ebTotal-ebCount;

    carTotal = ui->carspinBox->text().toInt();
    bikeTotal = ui->bikespinBox->text().toInt();
    truckTotal = ui->truckspinBox->text().toInt();
    ecTotal = ui->evcspinBox->text().toInt();
    ebTotal = ui->evbspinBox->text().toInt();

    carCount=carTotal-carCount;
    bikeCount=bikeTotal-bikeCount;
    truckCount=truckTotal-truckCount;
    ecCount=ecTotal-ecCount;
    ebCount=ebTotal-ebCount;

    slotlog->saveSlotstoJSON(carTotal,bikeTotal,truckTotal,ecTotal,ebTotal,"slots.json");

    pl->resizeParkingLot(carTotal, bikeTotal, truckTotal, ecTotal, ebTotal);

    lcdm_1->updateLcds(carCount,bikeCount,truckCount,ecCount,ebCount);
    lcdm_2->updateLcds(carCount,bikeCount,truckCount,ecCount,ebCount);
    lcdm_3->updateLcds(carCount,bikeCount,truckCount,ecCount,ebCount);
    ui->AvailableSlotsLCD->display(totalSlots(carCount,bikeCount,truckCount,ecCount,ebCount));

    ui->carspinBox->setValue(carTotal);
    ui->bikespinBox->setValue(bikeTotal);
    ui->truckspinBox->setValue(truckTotal);
    ui->evcspinBox->setValue(ecTotal);
    ui->evbspinBox->setValue(ebTotal);

    if(SignIn::userRole == "admin"){
        QMessageBox::information(this, "Success", "Settings updated successfully!");
    }
}

void MainWindow::initializeSlots(int car, int bike, int truck, int ec, int eb){
    carTotal = car;
    bikeTotal = bike;
    truckTotal = truck;
    ecTotal = ec;
    ebTotal = eb;
}

void MainWindow::on_DeleteButton_clicked()
{
    QList<int> rowsToDelete;
    for (int row = 0; row < ui->userlogtable->rowCount(); ++row) {
        QTableWidgetItem* checkItem = ui->userlogtable->item(row, 4);
        QTableWidgetItem* roleItem = ui->userlogtable->item(row, 2);
        if (checkItem && checkItem->checkState() == Qt::Checked) {
            if (roleItem && roleItem->text().toLower() == "admin") {
                QMessageBox::warning(this, "Restricted", "Admin users cannot be deleted.");
                continue;
            }
            rowsToDelete.prepend(row);
        }
    }

    if (rowsToDelete.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select at least one row to delete.");
        return;
    }

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete the selected users?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        for (int row : rowsToDelete) {
            QString employeeId = ui->userlogtable->item(row, 0)->text();
            if (userlog->deleteUserFromJSON("accounts.json", employeeId)) {
                ui->userlogtable->removeRow(row);
            }
        }
        QMessageBox::information(this, "Deleted", "Selected users deleted successfully.");
    }
}

