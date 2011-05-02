#include <QtGui/QApplication>
#include "radio_jam_client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Radio_Jam_Client w;
    w.show();

    return a.exec();
}
