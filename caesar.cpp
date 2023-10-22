#include "caesar.h"
#include "ui_caesar.h"
#include <QMessageBox>

int alphabet_big[] = { 0x41, 0x104, 0x42, 0x43, 0x106, 0x44, 0x45, 0x118, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x141, 0x4d, 0x4e, 0x143, 0x4f, 0xd3, 0x50, 0x51, 0x52, 0x53, 0x15a, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x179, 0x17b };
int alphabet_small[] = { 0x61, 0x105, 0x62, 0x63, 0x107, 0x64, 0x65, 0x119, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x142, 0x6d, 0x6e, 0x144, 0x6f, 0xf3, 0x70, 0x71, 0x72, 0x73, 0x15b, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x17a, 0x17c };


Caesar::Caesar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Caesar)
{
    QIntValidator* validator = new QIntValidator(this);

    ui->setupUi(this);

    ui->lineEdit1->setValidator(validator);
    ui->textEdit2->setReadOnly(true);
    ui->lineEdit2->setValidator(validator);
    ui->textEdit4->setReadOnly(true);
}

Caesar::~Caesar()
{
    delete ui;
}

QString caesar_cipher_encryption(QString text, int shift)
{
    QString new_word = "";
    shift = shift % 35;

    if (shift != 0)
    {
        for (int i = 0; i < text.length(); i++)
        {
            QChar current_char = text[i];

            for (int j = 0; j < 35; j++)
            {
                if (current_char == QChar(alphabet_big[j]))
                {
                    if (j + shift < 35)
                    {
                        new_word += QChar(alphabet_big[j + shift]);
                    }
                    else
                    {
                        new_word += QChar(alphabet_big[j + shift - 35]);
                    }
                }
                else if (current_char == QChar(alphabet_small[j]))
                {
                    if (j + shift < 35)
                    {
                        new_word += QChar(alphabet_small[j + shift]);
                    }
                    else
                    {
                        new_word += QChar(alphabet_small[j + shift - 35]);
                    }
                }
            }
        }
    }
    else
    {
        new_word = text;
    }

    return new_word;
}

QString caesar_cipher_decryption(QString text, int shift)
{
    QString new_word = "";
    shift = shift % 35;

    if (shift != 0)
    {
        for (int i = 0; i < text.length(); i++)
        {
            QChar current_char = text[i];

            for (int j = 0; j < 35; j++)
            {
                if (current_char == QChar(alphabet_big[j]))
                {
                    if (j - shift >= 0)
                    {
                        new_word += QChar(alphabet_big[j - shift]);
                    }
                    else
                    {
                        new_word += QChar(alphabet_big[j - shift + 35]);
                    }
                }
                else if (current_char == QChar(alphabet_small[j]))
                {
                    if (j - shift >= 0)
                    {
                        new_word += QChar(alphabet_small[j - shift]);
                    }
                    else
                    {
                        new_word += QChar(alphabet_small[j - shift + 35]);
                    }
                }
            }
        }
    }
    else
    {
        new_word = text;
    }

    return new_word;
}

void Caesar::on_Button_encrypt_clicked()
{
    ui->textEdit2->clear();

    QString text = ui->textEdit1->toPlainText();
    int shift = ui->lineEdit1->text().toInt();

    if(text.isEmpty() || shift < 0)
    {
        QMessageBox::warning(this, "Warning", "You should specify any value for input boxes!", QMessageBox::Ok);
    }
    else
    {
        QString encrypted_message = caesar_cipher_encryption(text, shift);
        ui->textEdit2->append(encrypted_message);
    }
}

void Caesar::on_Button_decrypt_clicked()
{
    ui->textEdit4->clear();

    QString text = ui->textEdit3->toPlainText();
    int shift = ui->lineEdit2->text().toInt();

    if(text.isEmpty() || shift < 0)
    {
        QMessageBox::warning(this, "Warning", "You should specify any value for input boxes!", QMessageBox::Ok);
    }
    else
    {
        QString decryptde_messsage = caesar_cipher_decryption(text, shift);
        ui->textEdit4->append(decryptde_messsage);
    }
}

