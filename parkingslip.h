// parkingSlipDialog.h
#ifndef PARKINGSLIPDIALOG_H
#define PARKINGSLIPDIALOG_H

#include <QDialog>
#include <QTimer>

class QLabel;

class parkingslip : public QDialog {
    Q_OBJECT
public:
    explicit parkingslip(const QString &license, const QString &type,
                               const QString &slot, const QString &time,
                               QWidget *parent = nullptr);

    explicit parkingslip(const QString &license, const QString &type,
                         const QString &slot,const double &fees, const QString &time,
                         QWidget *parent = nullptr);
private slots:
           void keyPressEvent(QKeyEvent *event);

private:
    QLabel *infoLabel;
    QTimer *autoCloseTimer;
};

#endif // PARKINGSLIPDIALOG_H
