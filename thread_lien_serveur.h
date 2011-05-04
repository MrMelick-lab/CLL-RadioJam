#ifndef THREAD_LIEN_SERVEUR_H
#define THREAD_LIEN_SERVEUR_H

#include <QThread>
#include <QTcpSocket>

class Thread_Lien_Serveur : public QThread
{
    public:
        Thread_Lien_Serveur(int Instrument, QString Nom, QString IP);
        bool m_Etat;

    private:
    QString m_Nom;
    QString m_IP;
    int m_Instrument;

    protected:
        void run();
};

#endif // THREAD_LIEN_SERVEUR_H
