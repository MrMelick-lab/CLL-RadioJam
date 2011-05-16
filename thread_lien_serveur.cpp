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
    QByteArray baReception;

    m_socket.connectToHost(m_IP, 22222);
    if(m_socket.waitForConnected()) // Attente d'1 sec maximum sinon, fermer le socket
    {
        if(m_socket.waitForReadyRead(5000))
        {
            m_socket.readAll();
            //Envoi des données identifiants l'utilisateur: nom et instrument choisi.
            m_socket.write(m_Nom.toAscii());
            m_socket.waitForBytesWritten();

            if(m_socket.waitForReadyRead(5000))
            {
                baReception.append(m_socket.readAll());
                //Vérifie la réception
                if(baReception.at(0) == '#')
                 {
                     m_socket.write(QString::number(m_Instrument,10).toAscii());//Envoi du no d'instrument
                     m_socket.waitForBytesWritten();
                     m_Etat = true;
                 }
            }
            baReception.clear(); // Vidage de la variable de réception pour la réutiliser
            while(m_Etat)
            {
                if(m_socket.waitForReadyRead(1000))
                {
                    baReception.append(m_socket.read(1));
                    if(baReception.at(0) == 'N')//Si il y a un nouveau client connecté au serveur
                    {
                        if(m_socket.waitForReadyRead(1000))
                        {
                            baReception.append(m_socket.read(1));//Réception du nom
                            if(m_socket.waitForReadyRead(1000))
                            {
                                baReception.append(m_socket.read(1));//Réception de l'instrument
                                Thread_Reception* NouveauRecepteur = new Thread_Reception(baReception.at(2), m_IP);
                                NouveauRecepteur->start();
                            }
                        }
                    }
                    else if (baReception.at(0) == 'L')
                    {
                        m_Etat = false;
                        emit ServeurFerme();
                    }
                    baReception.clear();// Vidage de la variable de réception
                }
            }
        }
    }
    m_socket.write("L");
    m_socket.waitForBytesWritten();
    m_socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    m_socket.close(); // Fermeture du socket
    this->quit();
}

void Thread_Lien_Serveur::EnvoisNote(int note)
{
   QByteArray BufferEnvois;
   BufferEnvois[0] = note;
   //if(m_socket
   m_socket.write(BufferEnvois);
}
