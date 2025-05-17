#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QString>
class MainWindow;

class logmanager : public QObject
{
    Q_OBJECT
public:
    explicit logmanager(QTableWidget *tableWidget, QObject *parent = nullptr);

    explicit logmanager(QObject *parent);

    void addLogEntry(const QString &licensePlate,const QString &type,
                     const QString &slotID,const QString &status);

    // To manage Vehicle logs
    void loadLogFromJSON(const QString &filename);
    void saveLogToJSON(const QString &filename);


    // To manage user logs
    void loadLogFromJSON(int id, const QString &filename);
    void saveLogToJSON(int id, const QString &filename);
    bool deleteUserFromJSON(const QString& filename, const QString& empId);
    void updateUser(const QString& username, const QString& password, const QString& empId, const QString& filePath);


    // To manage Vehicle Slots
    void saveSlotstoJSON(int car,int bike, int truck,int ec,int eb,const QString& filename);
    bool loadSlotsfromJSON(const QString& filename, MainWindow* window);



    static QString getEntryTimeIfParked(const QString& licensePlate, const QString& jsonFilePath);

    static bool isVehicleCurrentlyParked(const QString& licensePlate,const QString& type, const QString& filePath);

private:
    QTableWidget *logTable;
};

#endif // LOGMANAGER_H
