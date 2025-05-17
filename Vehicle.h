#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

class Vehicle {
protected:
    QString licensePlate;
    QString vehicleType;

public:
    Vehicle(const QString& plate, const QString& type);
    virtual ~Vehicle();

    QString getLicensePlate() const;
    QString getVehicleType() const;
};

#endif // VEHICLE_H
