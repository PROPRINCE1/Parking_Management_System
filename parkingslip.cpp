// parkingSlipDialog.cpp
#include "parkingslip.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>

parkingslip::parkingslip(const QString &license, const QString &type,
                                     const QString &slot, const QString &time,
                                     QWidget *parent)
    : QDialog(parent) {

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setFixedSize(300, 200);
    setStyleSheet("background-color: white; border: 2px solid black;");

    QString text = QString(
                       "<h3 style='text-align:center;'>Parking Slip</h3>"
                       "<p><b>License:</b> %1</p>"
                       "<p><b>Type:</b> %2</p>"
                       "<p><b>Slot:</b> %3</p>"
                       "<p><b>Time:</b> %4</p>"
                       "<p style='text-align:center;'>Thank you!</p>"
                       ).arg(license, type, slot, time);

    infoLabel = new QLabel(text);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-family: Courier; font-size: 12px;");

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(infoLabel);

    // Auto close after 5 seconds
    autoCloseTimer = new QTimer(this);
    connect(autoCloseTimer, &QTimer::timeout, this, &parkingslip::close);
    autoCloseTimer->start(5000);
}

parkingslip::parkingslip(const QString &license, const QString &type,
                         const QString &slot,const double &fees, const QString &time,
                         QWidget *parent)
    : QDialog(parent) {

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setFixedSize(300, 200);
    setStyleSheet("background-color: white; border: 2px solid black;");

    QString text = QString(
                       "<h3 style='text-align:center;'>Parking Slip</h3>"
                       "<p><b>License:</b> %1</p>"
                       "<p><b>Type:</b> %2</p>"
                       "<p><b>Slot:</b> %3</p>"
                       "<p><b>Fees:</b> %4</p>"
                       "<p><b>Time:</b> %5</p>"
                       "<p style='text-align:center;'>Thank you!</p>"
                       ).arg(license, type, slot, QString::number(fees), time);

    infoLabel = new QLabel(text);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-family: Courier; font-size: 12px;");

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(infoLabel);

    // Auto close after 5 seconds
    autoCloseTimer = new QTimer(this);
    connect(autoCloseTimer, &QTimer::timeout, this, &parkingslip::close);
    autoCloseTimer->start(5000);
}

// Dialogue box closing function (Enter key)
void parkingslip::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        this->accept();
    } else {
        QDialog::keyPressEvent(event);
    }
}
