#include "thread_reception.h"

Thread_Reception::Thread_Reception(QString IP)
{
    m_IP = IP;
    m_Etat = true;
}

void Thread_Reception::run()
{
    QTcpSocket socket;
    socket.connectToHost(m_IP,22224);
    if (socket.waitForConnected(1000)) //Attente d'1 sec maximum sinon, fermer le socket
    {
        while(m_Etat)
        {
            if (socket.waitForReadyRead(100))
            {
                m_baReception.append(socket.read(1));
                emit NoteRecue(m_baReception.at(0));
//                JouerSon(baReception.at(0)); //Jouer le son selon la note reçues
                m_baReception.clear(); // Vidage de la variable de réception pour la réutiliser
            }
        }
    }
    socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    socket.close(); // Fermeture du socket
}

void Thread_Reception::RecevoirNomIns(QString Nom, int Instrument)
{
    Thread_Son* TJouerSon = new Thread_Son(Nom,Instrument);
    connect(this,SIGNAL(NoteRecue(int)),TJouerSon, SLOT(JouerSon(int)));
}
