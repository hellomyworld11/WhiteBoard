#include "penwidth.h"
#include "ui_penwidth.h"

PenWidth::PenWidth(int width, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PenWidth),
    dWidth(width)
{
    ui->setupUi(this);
    int low = 1;
    int high = 100;
    //dWidth = 50;
    ui->horizontalSlider->setMinimum(low);
    ui->horizontalSlider->setMaximum(high);
    ui->horizontalSlider->setSliderPosition(width);
    QString str;
    str = QString("%1").arg(width);
    ui->plainTextEdit->setPlainText(str);
}

PenWidth::~PenWidth()
{
    delete ui;
    emit setval(dWidth);
}

void PenWidth::on_horizontalSlider_valueChanged(int value)
{
    QString str;
    str = QString("%1").arg(value);
    ui->plainTextEdit->setPlainText(str);
    dWidth = value;
}

