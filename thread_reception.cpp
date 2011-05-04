#include "thread_reception.h"

Thread_Reception::Thread_Reception(int instrument, QString IP)
{
    m_Instrument = instrument;
    m_IP = IP;
    //Reste à mettre la variable QDIR qui va contenir la liste des fichiers
}

void Thread_Reception::run()
{
    QTcpSocket socket;
    QByteArray baReception;
    Phonon::MediaObject *mediaObject = new Phonon::MediaObject(this);;
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    mediaObject->setCurrentSource(Phonon::MediaSource("variable QDIR pas encore fait"));

    socket.connectToHost(m_IP,22224); // À vérifier pour avoir le bon numéro de port
    if (socket.waitForConnected(1000)) //Attente d'1 sec maximum sinon, fermer le socket
    {
        if(socket.waitForReadyRead(1000))
        {
            baReception.append(socket.readAll());
            //Vérifie la réception
            if(baReception.at(0) == '#')
                 m_Etat = true;
        }
        baReception.clear(); // Vidage de la variable de réception pour la réutiliser
        while(m_Etat)
        {
            if(socket.readyRead(100))
            baReception.append(socket.readAll());
            switch (baReception.at(0))
            {
                case 65: //Ascii de a, reste à savoir comment le serveur va répondre avec un char ou une valeur en ASCII directe

                break;
            }
        }
    }
    socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    socket.close(); // Fermeture du socket
}
