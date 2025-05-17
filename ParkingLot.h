#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <vector>
#include <QString>
#include "ParkingSpace.h"
using namespace std;

class ParkingLot {
private:
    vector<ParkingSpace*> allSpaces;
    const int MAX_SPACES = 100;
    int maxSpace;
    int carSpace;
    int bikeSpace;
    int truckSpace;
    int ecSpace;
    int ebSpace;

    void initializeSpaces(int carSpace, int bikeSpace, int truckSpace, int ecSpace, int ebSpace);
    ParkingSpace* createSpaceForType(const QString& type, int id);
    int getStartIndex(const QString& vehicleType) const;
    int getEndIndex(const QString& vehicleType) const;

public:
    ParkingLot(int carSpace, int bikeSpace, int truckSpace, int ecSpace, int ebSpace);
    explicit ParkingLot(const ParkingLot& other);
    ~ParkingLot();

    ParkingSpace* findAvailableSpace(const QString& vehicleType);
    bool parkVehicle(const QString& vehicleType, const QString& licensePlate);
    double removeVehicle(const QString& licensePlate);
    void displayAvailableSpaces() const;

    int getTotalSpaces(const QString& vehicleType) const;
    int getAvailableSpaces(const QString& vehicleType) const;

    QString getVehicleTypeForLicensePlate(const QString& licensePlate) const;
    int getSpaceIdForLicensePlate(const QString& licensePlate) const;
    ParkingSpace* findSpaceByLicensePlate(const QString& licensePlate) const;

    void resizeParkingLot(int newCar, int newBike, int newTruck, int newEC, int newEB);


};

#endif // PARKINGLOT_H
