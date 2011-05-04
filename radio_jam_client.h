#ifndef RADIO_JAM_CLIENT_H
#define RADIO_JAM_CLIENT_H

#include <QMainWindow>
#include <QMessageBox>
#include <Qt>
#include <thread_lien_serveur.h>

namespace Ui {
    class Radio_Jam_Client;
}

class Radio_Jam_Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Radio_Jam_Client(QWidget *parent = 0);
    ~Radio_Jam_Client();

private slots:
    void on_lineEdit_textEdited(QString );

    void on_txtNote_textEdited(QString );

    void on_btnConnection_clicked();

private:
    Ui::Radio_Jam_Client *ui;

    Thread_Lien_Serveur *m_ThreadEnvois;
};

#endif // RADIO_JAM_CLIENT_H
