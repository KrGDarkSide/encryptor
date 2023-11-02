#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // Disable possibility of resizing window
    w.setFixedSize(w.size());
    return a.exec();
}
