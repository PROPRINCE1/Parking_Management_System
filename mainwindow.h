#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signin.h"
#include "lcdmanager.h"
#include "logmanager.h"
#include "CarParkingSpace.h"
#include "MotorcycleParkingSpace.h"
#include "TruckParkingSpace.h"
#include "EVCarParkingSpace.h"
#include "EVMotorcycleParkingSpace.h"
#include "ParkingManager.h"
#include "ParkingLot.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool loggedOut = false;

    void initializeSlots(int car, int bike, int truck, int ec, int eb);

protected:
    void closeEvent(QCloseEvent *event) override;


private slots:

    void on_CarButton_clicked();

    void on_BikeButton_clicked();

    void on_TruckButton_clicked();

    void on_ECButton_clicked();

    void on_EBButton_clicked();

    void on_CarButton_2_clicked();

    void on_BikeButton_2_clicked();

    void on_TruckButton_2_clicked();

    void on_ECButton_2_clicked();

    void on_EBButton_2_clicked();

    int totalSlots(int,int,int,int,int);

    void on_AddButton_clicked();

    void on_logOutButton_clicked();

    void on_saveSettingsButton_clicked();

    void on_DeleteButton_clicked();

private:

    Ui::MainWindow *ui;

    lcdmanager* lcdm_1;
    lcdmanager* lcdm_2;
    lcdmanager* lcdm_3;

    logmanager* vehiclelog;
    logmanager* userlog;
    logmanager* slotlog;
    ParkingManager* pm = nullptr;
    ParkingLot* pl = nullptr;

    int carCount;
    int bikeCount;
    int truckCount;
    int ecCount;
    int ebCount;

    int carTotal;
    int bikeTotal;
    int truckTotal;
    int ecTotal;
    int ebTotal;


    int totalSpace;

};
#endif // MAINWINDOW_H
