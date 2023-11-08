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

private slots:
    void on_pushButton2_clicked();

    void on_Button_encrypt_clicked();

    void on_Button_decrypt_clicked();

private:
    Ui::Polybius *ui;
};

#endif // POLYBIUS_H
