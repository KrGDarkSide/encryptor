#include "homophonic.h"
#include "ui_homophonic.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>
#include <QMultiMap>
#include <cstdlib>
#include <ctime>

const int alphabet[] = { 0x61, 0x105, 0x62, 0x63, 0x107, 0x64, 0x65, 0x119, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x142, 0x6d, 0x6e, 0x144, 0x6f, 0xf3, 0x70, 0x71, 0x72, 0x73, 0x15b, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x17a, 0x17c };

Homophonic::Homophonic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Homophonic)
{
    ui->setupUi(this);

    // Regular Expression for key
    static QRegularExpression rx("^[\\p{L}]{2,28}$");

    QValidator *validator = new QRegularExpressionValidator(rx, this);

    // Checking validation of entered key
    ui->En_inputKey->setValidator(validator);
    ui->De_inputKey->setValidator(validator);

    // Result read only
    ui->En_outputText->setReadOnly(true);
    ui->De_outputText->setReadOnly(true);

    srand (time(NULL));
}

Homophonic::~Homophonic()
{
    delete ui;
}



// Create multiMap that as keys have alphabet characters and as values numbers from 0 to 999.
QMultiMap<QChar, int> create_alphabetMap(QString &key)
{
    QMultiMap<QChar, int> map;
    int num = 0;

    // Fill multiMap with numbers depending on the key word
    for (int i = 0; i < key.length(); i++)
    {
        bool find_kLetter = false;
        for (int j = 0; j < 35; j++)
        {
            if (key[i] == QChar(alphabet[j]))
            {
                map.insert(QChar(alphabet[j]), num);
                num++;
                find_kLetter = true;
            }
            if (find_kLetter)
            {
                if (j == 34)
                {
                    j = -1;
                }
                map.insert(QChar(alphabet[j]), num);
                num++;
            }
        }
    }

    // After used key word start filling multimap form 'a' to 'ż' by numbers till num will be 999.
    while (num != 999)
    {
        for (int i = 0; i < 35; i++)
        {
            map.insert(QChar(alphabet[i]), num);
            num++;
            if (num >= 999)
            {
                break;
            }
        }
    }

    return map;
}

QString prepare_value(int val)
{
    QString new_value = QString::number(val);

    if (new_value.length() == 1) { new_value = "00" + new_value; }
    else if (new_value.length() == 2) { new_value = "0" + new_value; }

    return new_value;
}

QString homophonic_encryption(QString text, QString key)
{
    QMultiMap<QChar, int> alphabetMap = create_alphabetMap(key);
    QString new_word = "";

    for (int i = 0; i < text.length(); i++)
    {
        QList<int> key_values;
        for (auto x = alphabetMap.begin(); x != alphabetMap.end(); x++)
        {
            if (x.key() == text[i])
            {
                key_values.append(x.value());
            }
        }

        // generate pseudo random number
        int index = rand() % key_values.size();
        new_word += prepare_value(key_values.at(index));
    }

    return new_word;
}



// ENCRYPT button
void Homophonic::on_En_Button_clicked()
{
    // Take text from QTextEdit and convert it to lowercase
    QString text = (ui->En_inputText->toPlainText()).toLower();
    QString key = (ui->En_inputKey->text()).toLower();

    // Check if text and key are empty
    if(text.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "To encrypt a message, you must provide some text to be encrypted!", QMessageBox::Ok);
    }
    else if (key.isEmpty() || key.length() < 2)
    {
        QMessageBox::warning(this, "Warning", "You need to enter the key!\nKey can contain only letters (2-28).", QMessageBox::Ok);
    }
    else
    {
        ui->En_outputText->append(homophonic_encryption(text, key));
    }
}

// DECRYPT button
void Homophonic::on_De_Button_clicked()
{

}



// IMPORT key for encryption and next method for decryption
void Homophonic::on_En_importBt_clicked()
{
    // Prepare dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import key"), "", tr("Encryptor key (*.enckey);;All Files (*)"));

    if (fileName.isEmpty()){ return; }
    else
    {
        // Get file name
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        }

        QTextStream in(&file);
        QString input = "";
        in.setEncoding(QStringConverter::Utf8);

        in >> input;

        ui->En_inputKey->setText(input);
        ui->De_inputKey->setText(input);

        // Close file stream.
        file.close();
    }
}

void Homophonic::on_De_importBt_clicked()
{
    Homophonic::on_En_importBt_clicked();
}

// SAVE key
void Homophonic::on_saveBt_clicked()
{
    // Set title and files posible to save
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save key"), "", tr("Encryptor key (*.enckey);;All Files (*)"));

    if (fileName.isEmpty()) { return; }
    else
    {
        // Take file name and open file to write
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        }

        QTextStream out(&file);
        QString key = ui->En_inputKey->text();

        // Set encoding to UTF-8
        out.setEncoding(QStringConverter::Utf8);
        out << key;

        // Cloase file stream
        file.close();
    }
}




