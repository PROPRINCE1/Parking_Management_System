#ifndef PARKINGMANAGER_H
#define PARKINGMANAGER_H

#include "ParkingLot.h"
#include <QDebug>

#include <QString>

class ParkingManager {
private:
    ParkingLot* parkingLot;

public:
    ParkingManager();
    explicit ParkingManager(ParkingLot* lot): parkingLot(lot){}
    ~ParkingManager();

    bool parkVehicle(const QString& vehicleType, const QString& licensePlate);
    double removeVehicle(const QString& licensePlate);
    void displayAvailableSpaces() const;
    void resizeParkingLot(int newCar, int newBike, int newTruck, int newEC, int newEB);

    int getAvailableSpacesCount(const QString& vehicleType) const;
    QString getVehicleTypeForLicensePlate(const QString& licensePlate) const;
    int getSpaceIdForLicensePlate(const QString& licensePlate) const;
};

#endif
