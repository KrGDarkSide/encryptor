#include "polybius.h"
#include "ui_polybius.h"

Polybius::Polybius(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polybius)
{
    ui->setupUi(this);
}

Polybius::~Polybius()
{
    delete ui;
}
