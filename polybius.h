#ifndef POLYBIUS_H
#define POLYBIUS_H

#include <QDialog>

namespace Ui {
class Polybius;
}

class Polybius : public QDialog
{
    Q_OBJECT

public:
    explicit Polybius(QWidget *parent = nullptr);
    ~Polybius();

private:
    Ui::Polybius *ui;
};

#endif // POLYBIUS_H
