#include "mainwindow.h"
#include "signin.h"
#include "ParkingLot.h"
#include "ParkingManager.h"
#include <QApplication>
#include <QDateTime>
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/src/PMSicon.png"));

    while (true) {
        SignIn signIn;
        if (signIn.exec() == QDialog::Accepted) {
            MainWindow w;
            w.show();
            int result = a.exec();
            if (w.loggedOut) {
                continue;
            }
            break;
        } else {
            // Exit if Sign In exit button is pressed
            break;
        }
    }

    return 0;
}
