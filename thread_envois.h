#ifndef THREAD_ENVOIS_H
#define THREAD_ENVOIS_H

#include <QThread>
#include <QTcpSocket>
#include <thread_lien_serveur.h>

class Thread_Envois : public QThread //inutile
{
    Q_OBJECT
    public:
        Thread_Envois(int note);

    protected:
        void run();
};

#endif // THREAD_ENVOIS_H
