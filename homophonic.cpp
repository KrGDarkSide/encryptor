#include "homophonic.h"
#include "ui_homophonic.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>

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

    // Checking validation of entered text
    // Result read only
    ui->En_outputText->setReadOnly(true);
    ui->De_outputText->setReadOnly(true);
}

Homophonic::~Homophonic()
{
    delete ui;
}

// ENCRYPT button
void Homophonic::on_En_Button_clicked()
{
    // REGULAR EXPRESSION
    static QRegularExpression rx("^[\\p{L}0-9\\s]*$");

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
        if (!text.contains(rx))
        {
            QMessageBox::warning(this, "Warning", "Invalid input!\nOnly letters and numbers!", QMessageBox::Ok);
        }
        else
        {
            // FUNCTION
        }
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




