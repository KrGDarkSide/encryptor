#ifndef CAESAR_H
#define CAESAR_H

#include <QDialog>

namespace Ui {
class Caesar;
}

class Caesar : public QDialog
{
    Q_OBJECT

public:
    explicit Caesar(QWidget *parent = nullptr);
    ~Caesar();

private:
    Ui::Caesar *ui;
};

#endif // CAESAR_H
