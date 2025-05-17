#ifndef CREATEACC_H
#define CREATEACC_H

#include <QDialog>

namespace Ui {
class createAcc;
}

class createAcc : public QDialog
{
    Q_OBJECT

public:
    explicit createAcc(QWidget *parent = nullptr);
    ~createAcc();

public slots:
    static QString Encoder(const QString& input);

private slots:

    void on_Register_clicked();

    void saveUser(const QString& username, const QString& password, const QString& empId, const QString& role, const QString& filePath);

    void on_BackButton_clicked();

    static bool isUniqueId(const QString& empId);

private:
    Ui::createAcc *ui;

signals:
    void registerClicked();

};

#endif // CREATEACC_H
