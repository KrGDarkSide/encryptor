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

private slots:
    void on_Button_encrypt_clicked();

    void on_Button_decrypt_clicked();

private:
    Ui::Caesar *ui;
};

#endif // CAESAR_H
