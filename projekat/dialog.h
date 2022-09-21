#ifndef DIALOG_H
#define DIALOG_H

#include <QtCharts/QLineSeries>
#include <QWidget>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <QtGlobal>
#include <QDialog>
#include <stdlib.h>
#include <QtCharts/QChartView>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QProgressBar>
#include <QSpinBox>
#include <QDebug>

using namespace QtCharts;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    const char PCF8591 = 0x48; //adresa
    int fd, adcSvetlo, adcVlaga;
    int svetlo, vlaga, brojac, minut, dozvola_za_brojac=0;
    int val, counter=0;
    int set_brojaca = 0;


    QLineSeries *series;

    ~Dialog();

private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked();
    void senzori();
    void prikazVremena();
    void on_pushButton_3_clicked();
    void count();

private:
    Ui::Dialog *ui;
    QTimer *timer1;
};

#endif // DIALOG_H
