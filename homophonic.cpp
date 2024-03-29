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



// Create a MultiMap that, as keys, has alphabetic characters and values from 0 to 999.
QMultiMap<QChar, int> create_alphabetMap(QString &keyW)
{
    QMultiMap<QChar, int> map;
    int num = 0;

    // Fill the MultiMap by only key word.
    for (int i = 0; i < keyW.length(); i++)
    {
        // Find start indexes for key letters
        int index;
        for (int j = 0; j < 35; j++)
        {
            if (keyW[i] == QChar(alphabet[j]))
            {
                index = j;
                break;
            }
        }
        for (int j = 0; j < 35 ; j++)
        {
            if (index == 35) { index = 0; }
            map.insert(QChar(alphabet[index]), num);
            index++;
            num++;
        }
    }

    // Fill the multimap with the remaining numbers starting from a to z
    while (num != 999)
    {
        for (int i = 0; i < 35; i++)
        {
            if (num == 999)
            {
                map.insert(QChar(alphabet[i]), num);
                break;
            }
            map.insert(QChar(alphabet[i]), num);
            num++;
        }
    }

    return map;
}

// Making values which is made from 3 characters. For example 007
QString prepare_value(int val)
{
    QString new_value = QString::number(val);

    if (new_value.length() == 1) { new_value = "00" + new_value; }
    else if (new_value.length() == 2) { new_value = "0" + new_value; }

    return new_value;
}

// Clean values (delete 0 prefix)
int unpak_value(QString val)
{
    int new_value;

    if (val[0] == '0' && val[1] == '0') { new_value = val[2].digitValue(); }
    else if (val[0] == '0') { new_value = val[1].digitValue() * 10 + val[2].digitValue(); }
    else
    {
        new_value = val[0].digitValue() * 100;
        new_value += val[1].digitValue() * 10;
        new_value += val[2].digitValue();
    }

    return new_value;
}

QString homophonic_encryption(QString &text, QString &keyW)
{
    QMultiMap<QChar, int> alphabetMap = create_alphabetMap(keyW);
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
            else { continue; }
        }

        // generate pseudo random number if key_value is not null
        if (!key_values.empty())
        {
            int index = rand() % key_values.size();
            new_word += prepare_value(key_values.at(index));
        }
    }

//    for (auto i = alphabetMap.cbegin(), end = alphabetMap.cend(); i != end; ++i)
//        new_word += QString(i.key()) + ":" + QString::number(i.value()) + " --> ";

    return new_word;
}

QString homophonic_Decryption(QString &text, QString &keyW)
{
    QMultiMap<QChar, int> alphabetMap = create_alphabetMap(keyW);
    QString new_word = "";

    for (int i = 0; i < text.length();  i+=3)
    {
        // "Convert" string to int
        int char_value = unpak_value(text.mid(i, 3));

        for (auto x = alphabetMap.begin(); x != alphabetMap.end(); x++)
        {
            if (x.value() == char_value)
            {
                new_word += x.key();
                break;
            }
            else { continue; }
        }
    }

    return new_word;
}



// ENCRYPT button
void Homophonic::on_En_Button_clicked()
{
    // Clear read only field
    ui->En_outputText->clear();

    // Take text from QTextEdit and convert it to lowercase
    QString text = (ui->En_inputText->toPlainText()).toLower();
    QString keyW = (ui->En_inputKey->text()).toLower();

    // Check if text and key are empty
    if(text.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "To encrypt a message, you must provide some text to be encrypted!", QMessageBox::Ok);
    }
    else if (keyW.isEmpty() || keyW.length() < 2)
    {
        QMessageBox::warning(this, "Warning", "You need to enter the key!\nKey can contain only letters (2-28).", QMessageBox::Ok);
    }
    else
    {
        ui->En_outputText->append(homophonic_encryption(text, keyW));
    }
}

// DECRYPT button
void Homophonic::on_De_Button_clicked()
{
    // RegEx
    static QRegularExpression rx("^([0-9]{3})*$");

    // Clear read only field
    ui->De_outputText->clear();

    // Take inserted text and keyword and convert it to lowercase
    QString text = (ui->De_inputText->toPlainText()).toLower();
    QString keyW = (ui->De_inputKey->text()).toLower();

    // Check if keyword and inserted test are empty
    if(text.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "To encrypt a message, you must provide some text to be encrypted!", QMessageBox::Ok);
    }
    else if (keyW.isEmpty() || keyW.length() < 2)
    {
        QMessageBox::warning(this, "Warning", "You need to enter the key!\nKey can contain only letters (2-28).", QMessageBox::Ok);
    }
    else
    {
        if(!text.contains(rx))
        {
            QMessageBox::warning(this, "Warning", "Only numeric characters may be entered!\n(The number of characters must be divisible by three)", QMessageBox::Ok);
        }
        else
        {
            ui->De_outputText->append(homophonic_Decryption(text, keyW));
        }
    }
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




