#include "thread_lien_serveur.h"
#include "thread_reception.h"

Thread_Lien_Serveur::Thread_Lien_Serveur(int Instrument, QString Nom, QString IP)
{
    m_Instrument = Instrument;
    m_Nom = Nom;
    m_IP = IP;
    m_Etat = false;
}

void Thread_Lien_Serveur::run()
{
    QTcpSocket socket;
    QByteArray baReception;

    socket.connectToHost(m_IP, 22222);
    if(socket.waitForConnected(1000)) // Attente d'1 sec maximum sinon, fermer le socket
    {
        //Envoi des données identifiants l'utilisateur: nom et instrument choisi.
        socket.write(m_Nom.toAscii());
        socket.waitForBytesWritten();

        if(socket.waitForReadyRead(1000))
        {
            baReception.append(socket.readAll());
            //Vérifie la réception
            if(baReception.at(0) == '#')
             {
                 socket.write(QString::number(m_Instrument,10).toAscii());//Envoi du no d'instrument
                 socket.waitForBytesWritten();
                 m_Etat = true;
             }
        }
        baReception.clear(); // Vidage de la variable de réception pour la réutiliser
        while(m_Etat)
        {
            if(socket.waitForReadyRead())
            {
                baReception.append(socket.read(1));
                if(baReception.at(0) == 'N')//Si il y a un nouveau client connecté au serveur
                {
                    if(socket.waitForReadyRead())
                    {
                        baReception.append(socket.read(1));//Réception du nom
                        if(socket.waitForReadyRead())
                        {
                            baReception.append(socket.read(1));//Réception de l'instrument
                            Thread_Reception* NouveauRecepteur = new Thread_Reception(baReception.at(2), m_IP);
                            NouveauRecepteur->start();
                        }
                    }
                }
                baReception.clear();// Vidage de la variable de réception
            }
        }
    }
    socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    socket.close(); // Fermeture du socket
}
