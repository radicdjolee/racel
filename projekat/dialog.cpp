#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::senzori);
    connect(timer, &QTimer::timeout, this, &Dialog::prikazVremena);
    timer -> start(1000);

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &Dialog::count);

    pinMode(21, OUTPUT);

    series = new QLineSeries();

    QChart *chart = new QChart();
     chart->legend()->hide();
     chart->addSeries(series);
     chart->createDefaultAxes();

     chart->axisX()->setRange(0, 60); //sekunde
     chart->axisY()->setRange(0, 100); //procenat vlage

     chart->setTitle("Osuncanost biljke u toku 1 minuta");

     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);

     ui -> verticalLayout -> addWidget(chartView);

     brojac = 0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::senzori() {

        fd = wiringPiI2CSetup(PCF8591);

            wiringPiI2CReadReg8(fd, PCF8591 + 2);
            adcSvetlo = wiringPiI2CReadReg8(fd, PCF8591 + 2);
            svetlo = 100 - (adcSvetlo*100/255);

            wiringPiI2CReadReg8(fd, PCF8591 + 1);
            adcVlaga = wiringPiI2CReadReg8(fd, PCF8591 + 1);

            if (adcVlaga > 240) {
                vlaga = 0;
            } else if(adcVlaga > 235){
                vlaga = 10;
            } else if(adcVlaga > 230){
                vlaga = 20;
            } else if(adcVlaga > 225){
                vlaga = 30;
            } else if(adcVlaga > 220){
                vlaga = 40;
            } else if(adcVlaga > 215){
                vlaga = 50;
            } else if(adcVlaga > 210){
                vlaga = 60;
            } else if(adcVlaga > 205){
                vlaga = 70;
            } else if(adcVlaga > 200){
                vlaga = 80;
            } else if(adcVlaga > 195){
                vlaga = 90;
            } else {
                vlaga = 100;
            }

            ui->progressBar->setValue(vlaga);

            ui->progressBar_2->setValue(svetlo);

            if(brojac == 0) {
                series->clear();
            }

            series -> append(brojac, svetlo);

            brojac =(brojac+1)%60;
}

void Dialog::on_pushButton_clicked(bool checked)
{
    if(checked == true) {

        digitalWrite(21, 1);

    } else if (checked == false) {

        digitalWrite(21, 0);

    }
}

void Dialog::on_pushButton_2_clicked()
{
        series -> clear();
        brojac = 0;
}

void Dialog::prikazVremena()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh : mm : ss");

    ui->label_5->setText(text);
}


void Dialog::on_pushButton_3_clicked()
{
    minut = ui->spinBox->value();
    val = minut*60000;
    timer1 ->start(val);

}

void Dialog::count()
{
    digitalWrite(21, 1);
    delay(2000);
    digitalWrite(21, 0);
}

