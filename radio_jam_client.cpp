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

//Prend les touches du clavier et on les envois au thread qui les envois au serveur
void Radio_Jam_Client::on_txtNote_textEdited(QString touche)
{
    touche = touche.toUpper(); //Met en majuscule la touche entrée pour valider
    QByteArray note = touche.toAscii(); //Met en ascii dans un tableau d'octet pour comparer
    emit NoteJouer(note[0]); //Envois de la touche du clavier au thread lien serveur pour qu'il l'envois au serveur
    ui->txtNote->setText(""); //Remet à rien les touches entrés pour traiter une seule note à la fois
}

void Radio_Jam_Client::on_btnConnection_clicked()
{
    //Initialisation du thread qui va faire le lien et la réception avec le serveur
    if(ui->btnConnection->text() == "Connection")
    {
        ui->txtIP->setReadOnly(true);
        ui->btnConnection->setText("Deconnection");
        m_ThreadEnvois = new Thread_Lien_Serveur(ui->cboInstrument->currentIndex(),ui->txtNom->text(),ui->txtIP->text());
        m_ThreadEnvois->start();
        connect(this,SIGNAL(NoteJouer(int)),m_ThreadEnvois,SLOT(EnvoisNote(int)));
        connect(m_ThreadEnvois, SIGNAL(ServeurFerme()),this,SLOT(DeconnexionServeur()));
        connect(m_ThreadEnvois, SIGNAL(CreerThreadReception(QString,int)),this,SLOT(PartirThreadReception(QString,int)));
    }
    else
    {
        m_ThreadEnvois->m_Etat =false;
        ui->txtIP->setReadOnly(false);
        ui->btnConnection->setText("Connection");
    }
}

void Radio_Jam_Client::PartirThreadReception(QString nom, int Instrument)
{
   Thread_Reception* NouveauRecepteur = new Thread_Reception(ui->txtIP->text(),nom,Instrument);
   ui->lclient->addItem(nom);
   NouveauRecepteur->start();
}

void Radio_Jam_Client::DeconnexionServeur()
{
    ui->btnConnection->setText("Connection");
    QMessageBox::information(this,"Déconnexion du serveur","Le serveur à mis fin à la connexion.");
}


void Radio_Jam_Client::on_pbMUTE_clicked()
{

}
