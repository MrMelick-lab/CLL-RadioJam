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
//gdfgdfgdfgdfg
}

//Prend les touches du clavier et on les envois au thread qui les envois au serveur
void Radio_Jam_Client::on_txtNote_textEdited(QString touche )
{

}
