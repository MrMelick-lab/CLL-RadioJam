#ifndef THREAD_LIEN_SERVEUR_H
#define THREAD_LIEN_SERVEUR_H

#include <QThread>
#include <QTcpSocket>
#include "thread_reception.h"

class Thread_Lien_Serveur : public QThread
{
    Q_OBJECT

    public:
        Thread_Lien_Serveur(int Instrument, QString Nom, QString IP);
        bool m_Etat;

protected:
        void run();

    private:
    QString m_Nom;
    QString m_IP;
    int m_Instrument;
    QTcpSocket m_socket;

   private slots:
        void EnvoisNote(int );

    signals:
        void ServeurFerme();
        void CreerThreadReception(QString, int);
};

#endif // THREAD_LIEN_SERVEUR_H
