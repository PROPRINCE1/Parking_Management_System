#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <QObject>
#include <QLCDNumber>

class lcdmanager : public QObject{
public:
    explicit lcdmanager(QLCDNumber *lcd1, QLCDNumber *lcd2, QLCDNumber *lcd3, QLCDNumber *lcd4, QLCDNumber *lcd5, QObject *parent = nullptr);

    void updateLcds(int);

    void updateLcds(int,int);

    void updateLcds(int,int,int,int,int);

private:
    QLCDNumber *m_lcd1;
    QLCDNumber *m_lcd2;
    QLCDNumber *m_lcd3;
    QLCDNumber *m_lcd4;
    QLCDNumber *m_lcd5;
};

#endif // LCDMANAGER_H
