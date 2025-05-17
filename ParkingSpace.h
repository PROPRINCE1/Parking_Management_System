#ifndef PARKINGSPACE_H
#define PARKINGSPACE_H

#include <QDateTime>
#include <QString>

class ParkingSpace {
protected:
    int spaceID;
    bool occupied;
    QString licensePlate;
    QDateTime entryTime;

public:
    ParkingSpace(int id);
    virtual ~ParkingSpace();

    bool isOccupied() const;
    int getSpaceID() const;
    QString getLicensePlate() const;
    virtual QString getVehicleType() const = 0;
    QDateTime getEntryTime() const;

    void parkVehicle(const QString& licensePlate);
    void removeVehicle();
    virtual double calculateFee() const = 0;
};

#endif // PARKINGSPACE_H
