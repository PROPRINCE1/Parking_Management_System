#include "lcdmanager.h"

lcdmanager::lcdmanager(QLCDNumber *lcd1, QLCDNumber *lcd2, QLCDNumber *lcd3,
                       QLCDNumber *lcd4, QLCDNumber *lcd5, QObject *parent)
    : QObject(parent),
    m_lcd1(lcd1), m_lcd2(lcd2),
    m_lcd3(lcd3), m_lcd4(lcd4), m_lcd5(lcd5)
{}

// Initializer
void lcdmanager::updateLcds(int value)
{
    if (m_lcd1) m_lcd1->display(value);
    if (m_lcd2) m_lcd2->display(value);
    if (m_lcd3) m_lcd3->display(value);
    if (m_lcd4) m_lcd4->display(value);
    if (m_lcd5) m_lcd5->display(value);
}
// Used Separately
void lcdmanager::updateLcds(int dig,int value)
{
    if (m_lcd1 && dig==1) m_lcd1->display(value);
    if (m_lcd2 && dig==2) m_lcd2->display(value);
    if (m_lcd3 && dig==3) m_lcd3->display(value);
    if (m_lcd4 && dig==4) m_lcd4->display(value);
    if (m_lcd5 && dig==5) m_lcd5->display(value);
}
void lcdmanager::updateLcds(int car,int bike,int truck,int ec,int eb)
{
    if (m_lcd1) m_lcd1->display(car);
    if (m_lcd2) m_lcd2->display(bike);
    if (m_lcd3) m_lcd3->display(truck);
    if (m_lcd4) m_lcd4->display(ec);
    if (m_lcd5) m_lcd5->display(eb);
}



