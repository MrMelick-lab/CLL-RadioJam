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
