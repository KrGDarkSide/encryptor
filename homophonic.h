#ifndef HOMOPHONIC_H
#define HOMOPHONIC_H

#include <QDialog>

namespace Ui {
class Homophonic;
}

class Homophonic : public QDialog
{
    Q_OBJECT

public:
    explicit Homophonic(QWidget *parent = nullptr);
    ~Homophonic();

private slots:
    void on_En_Button_clicked();

    void on_De_Button_clicked();

    void on_En_importBt_clicked();

    void on_De_importBt_clicked();

    void on_saveBt_clicked();

private:
    Ui::Homophonic *ui;
};

#endif // HOMOPHONIC_H
