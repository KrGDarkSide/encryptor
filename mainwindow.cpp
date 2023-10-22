#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "caesar.h"
#include "polybius.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Button_info->setIcon(QIcon(":/new/prefix1/Resource/info.png"));
    ui->Button_info->setIconSize(QSize(23, 23));
    ui->Button_info->setToolTip("<strong>encryptor</strong>"
                                "<table>"
                                "<tr><td>Version:</td>"
                                "<td>0.0.1</td></tr>"
                                "<tr><td>Creator:</td>"
                                "<td>Krystian Grzesiak<td></tr>"
                                "<tr><td>Contact:</td>"
                                "<td>jul.mdama08@gmail.com<td></tr>"
                                "</table>");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Button_Caesar_clicked()
{
    hide();
    Caesar caesarWindow;
    caesarWindow.setModal(true);
    caesarWindow.exec();
}


void MainWindow::on_Button_Polybius_clicked()
{
    hide();
    Polybius polybiusWindow;
    polybiusWindow.setModal(true);
    polybiusWindow.exec();
}


void MainWindow::on_Button_info_clicked()
{
    QMessageBox::information(this, "Informations", "<strong>encryptor</strong><table><tr><td>Version:</td><td>0.0.1</td></tr><tr><td>Creator:</td><td>Krystian Grzesiak<td></tr><tr><td>Contact:</td><td>jul.mdama08@gmail.com</td></tr></table>", QMessageBox::Ok);
}

