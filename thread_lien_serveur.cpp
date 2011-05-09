#include "thread_lien_serveur.h"

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
            if(socket.waitForReadyRead(100))
            {
                baReception.append(socket.readAll());
                if(baReception.at(0) == 'N')//Si il y a un nouveau client connecté au serveur
                {
                    //Il va falloir lire le nom et le no d'instru
                }
                baReception.clear();// Vidage de la variable de réception
                Thread_Reception* Thread_JouerSon = new Thread_Reception(m_Instrument,m_IP);// Thread qui va faire jouer les sons selon les touches reçues
                Thread_JouerSon->start();
            }
            baReception.clear();
        }
    }
    socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    socket.close(); // Fermeture du socket
}
