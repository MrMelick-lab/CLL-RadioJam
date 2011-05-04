#include "radio_jam_client.h"
#include "ui_radio_jam_client.h"

Radio_Jam_Client::Radio_Jam_Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Radio_Jam_Client)
{
    ui->setupUi(this);
}

Radio_Jam_Client::~Radio_Jam_Client()
{
    delete ui;
}

void Radio_Jam_Client::on_lineEdit_textEdited(QString touche)//A deleter
{

}

//Prend les touches du clavier et on les envois au thread qui les envois au serveur
void Radio_Jam_Client::on_txtNote_textEdited(QString touche)
{
    touche = touche.toUpper(); //Met en majuscule la touche entrée pour valider
    QByteArray note = touche.toAscii(); //Met en ascii dans un tableau d'octet pour comparer et envoyer au serveur
    switch(note[0])
    {
        case 65:// touche A
            QMessageBox::information(this,"yeah","yeah");
            break;
    }
    ui->txtNote->setText(""); //Remet à rien les touches entrés pour traiter une seule note à la fois
}

void Radio_Jam_Client::on_btnConnection_clicked()
{
    //Initialisation du thread qui va faire le lien et la réception avec le serveur
    Thread_Lien_Serveur* ThreadEnvois = new Thread_Lien_Serveur(ui->cboInstrument->currentIndex(),ui->txtNom->text(),ui->txtIP->text());
    ThreadEnvois->start();
    //Il va y avoir un thread/socket pour la réception et un autre pour l'émission
}

void Radio_Jam_Client::on_cboInstrument_currentIndexChanged(int index)
{

}
