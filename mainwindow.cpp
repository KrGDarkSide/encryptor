#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "caesar.h"
#include "polybius.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // shows window
    ui->setupUi(this);
    // Add image to button, then size
    ui->Button_info->setIcon(QIcon(":/new/prefix1/Resource/info.png"));
    ui->Button_info->setIconSize(QSize(23, 23));
    // setToolTip shows tip when mous is on button
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

// Button linking to the Caesar cipher
void MainWindow::on_Button_Caesar_clicked()
{
    // hide main window
    hide();
    Caesar caesarWindow;
    caesarWindow.setModal(true);
    // Disable possibility of resizing window
    caesarWindow.setFixedSize(caesarWindow.size());
    caesarWindow.exec();
}

// Button linking to the Polybius square
void MainWindow::on_Button_Polybius_clicked()
{
    // hide main window
    hide();
    Polybius polybiusWindow;
    polybiusWindow.setModal(true);
    // Disable possibility of resizing window
    polybiusWindow.setFixedSize(polybiusWindow.size());
    polybiusWindow.exec();
}

// Open dialogbox with informations {version, autho ...}
void MainWindow::on_Button_info_clicked()
{
    QMessageBox::information(this, "Informations", "<strong>encryptor</strong><table><tr><td>Version:</td><td>0.0.1</td></tr><tr><td>Creator:</td><td>Krystian Grzesiak<td></tr><tr><td>Contact:</td><td>jul.mdama08@gmail.com</td></tr></table>", QMessageBox::Ok);
}

