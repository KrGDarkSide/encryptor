#include "polybius.h"
#include "ui_polybius.h"

Polybius::Polybius(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polybius)
{
    ui->setupUi(this);

    ui->tableWidget1->setStyleSheet("background-color: #f0f0f0;");
    ui->tableWidget2->setStyleSheet("background-color: #f0f0f0;");
}

Polybius::~Polybius()
{
    delete ui;
}
