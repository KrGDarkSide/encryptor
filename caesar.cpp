#include "caesar.h"
#include "ui_caesar.h"

Caesar::Caesar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Caesar)
{
    ui->setupUi(this);
}

Caesar::~Caesar()
{
    delete ui;
}
