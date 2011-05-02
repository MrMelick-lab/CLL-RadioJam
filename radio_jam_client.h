#ifndef RADIO_JAM_CLIENT_H
#define RADIO_JAM_CLIENT_H

#include <QMainWindow>

namespace Ui {
    class Radio_Jam_Client;
}

class Radio_Jam_Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Radio_Jam_Client(QWidget *parent = 0);
    ~Radio_Jam_Client();

private:
    Ui::Radio_Jam_Client *ui;
};

#endif // RADIO_JAM_CLIENT_H
