#include "polybius.h"
#include "ui_polybius.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

const int alphabet[] = { 0x61, 0x105, 0x62, 0x63, 0x107, 0x64, 0x65, 0x119, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x142, 0x6d, 0x6e, 0x144, 0x6f, 0xf3, 0x70, 0x71, 0x72, 0x73, 0x15b, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x17a, 0x17c };
QChar square[5][7];
int additional_difficulties = 0;

void generate_new_array(QChar arr[5][7])
{
    QChar letters_in_arr[35];
    int letters_counter = 0;
    QChar actual_character;

    while (letters_counter != 35)
    {
        actual_character = QChar(alphabet[rand() % 35]);
        bool contain = false;

        for (int i = 0; i < 35; i++)
        {
            if (letters_in_arr[i] == actual_character)
            {
                contain = true;
            }
        }

        if (!contain)
        {
            letters_in_arr[letters_counter] = actual_character;
            letters_counter++;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            arr[i][j] = letters_in_arr[j + (i * 7)];
        }
    }
}

Polybius::Polybius(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polybius)
{   
    ui->setupUi(this);
    srand (time(NULL));

    ui->tableWidget1->setStyleSheet("background-color: #f0f0f0;");
    ui->tableWidget2->setStyleSheet("background-color: #f0f0f0;");
    ui->textEdit2->setReadOnly(true);
    ui->textEdit4->setReadOnly(true);

    generate_new_array(square);

    // Fill table with "random" generated letters.
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            ui->tableWidget1->setItem(i, j, new QTableWidgetItem(square[i][j]));
        }
    }
}

Polybius::~Polybius()
{
    delete ui;
}

QString polibius_square_encryption(QString text, QChar arr[5][7])
{
    QString new_word = "";

    for (int i = 0; i < text.length(); i++)
    {
        QChar current_char = text[i];

        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                if (arr[j][k] == current_char)
                {
                    new_word += QChar(k);
                    new_word += QChar(j);
                    break;
                }
            }
        }
    }

    return new_word;
}

void Polybius::on_pushButton2_clicked()
{
    generate_new_array(square);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            ui->tableWidget1->setItem(i, j, new QTableWidgetItem(square[i][j]));
        }
    }
}


void Polybius::on_Button_encrypt_clicked()
{
    ui->textEdit2->clear();

    QString text = (ui->textEdit1->toPlainText()).toLower();

    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Pleas enter any text in textbox to encrypt it!", QMessageBox::Ok);
    }
    else
    {
        QString encrypted_message = polibius_square_encryption(text, square);
        ui->textEdit2->append(encrypted_message);
    }
}




