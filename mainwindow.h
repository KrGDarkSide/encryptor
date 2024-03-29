#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Button_Caesar_clicked();

    void on_Button_Polybius_clicked();

    void on_Button_info_clicked();

    void on_Button_Homophonic_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
