#include "polybius.h"
#include "ui_polybius.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <sstream>

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
            ui->tableWidget2->setItem(i, j, new QTableWidgetItem(square[i][j]));
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

        // Checking if actual character is number
        if (current_char >= QChar(0x30) && current_char <= QChar(0x39))
        {
            new_word += ':' + current_char;
        }
        else
        {
            // Stepping into the alphabet table
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 7; k++)
                {
                    if (arr[j][k] == current_char)
                    {
                        // If we used 'QChar(k)' then we will get '▯'
                        new_word += QString::number(k + 1);
                        new_word += QString::number(j + 1);
                        break;
                    }
                }
            }
        }
    }

    return new_word;
}

QString polibius_square_decryption(QString text, QChar arr[5][7])
{
    QString new_word = "";

    for (int i = 0; i < text.length(); i += 2)
    {
        QChar current_char1 = text[i];
        QChar current_char2 = text[i + 1];

        if(current_char1 == ':')
        {
            new_word += current_char2;
        }
        else
        {
            new_word += arr[current_char2.digitValue() - 1][current_char1.digitValue() - 1];
        }
    }

    return new_word;
}

// CONVERT QString to octal number saved in QString type.
QString toOCT(QString message)
{
    QString new_message = "#";
    new_message += QString::number(rand() % 4);

    // Run across all character
    for (int i = 1; i < message.length(); i += 2)
    {
        // create number from two other numbers. Two because one letter in normal encryption give us two number (column; row)
        int number = message[i - 1].digitValue() * 10 + message[i].digitValue();
        QString oct = "";

        while (number != 0)
        {
            oct = QString::number(number % 8) + oct;
            number /= 8;
        }
        new_message += oct;
        oct = "";
    }

    return new_message;
}

void Polybius::on_pushButton2_clicked()
{
    generate_new_array(square);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            ui->tableWidget1->setItem(i, j, new QTableWidgetItem(square[i][j]));
            ui->tableWidget2->setItem(i, j, new QTableWidgetItem(square[i][j]));
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

        // CONVERT RESOULT TO OCTAL
        if (ui->radioButton->isChecked())
        {
            encrypted_message = toOCT(encrypted_message);
        }
        // CONVERT TO UTF-8
        else if (ui->radioButton_2->isChecked())
        {

        }
        // WHEN NOTHING IS CHOUSE FROM RADIOBUTTONS OR USER CLIC NONE we WILL SKIP if else SECTION.
        ui->textEdit2->append(encrypted_message);
    }
}

void Polybius::on_Button_decrypt_clicked()
{
    ui->textEdit4->clear();

    QString text = (ui->textEdit3->toPlainText()).toLower();

    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "You must enter any text if you want to run that process!", QMessageBox::Ok);
    }
    else
    {
        QString decrypted_message = polibius_square_decryption(text, square);
        ui->textEdit4->append(decrypted_message);
    }
}

