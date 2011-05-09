#include "thread_reception.h"

Thread_Reception::Thread_Reception(int instrument, QString IP)
{
    m_IP = IP;
    QDir dossier;
    if(instrument == 0)
        dossier = QDir(QDir::currentPath() + "/Bass");
    else
        dossier = QDir(QDir::currentPath() + "/Drum");
    m_ListeSon = dossier.entryList();
}

void Thread_Reception::run()
{
    QTcpSocket socket;
    QByteArray baReception;
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
            if (socket.waitForReadyRead(100))
            {
                baReception.append(socket.readAll());
                JouerSon(baReception.at(0));
            }
        }
    }
    socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    socket.close(); // Fermeture du socket
}

void Thread_Reception::JouerSon(int note)
{
    Phonon::MediaObject *mediaObject = new Phonon::MediaObject();
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory);
    Phonon::createPath(mediaObject, audioOutput);
    QMutex mutex; //Synchroniser accès à un fichier
    switch(note) // suite va de q à u et de a à k
    {
        case 81: //Ascii de Q
            mediaObject->setCurrentSource(Phonon::MediaSource(m_ListeSon.at(0)));
        break;
        case 87: //Ascii de W
            mediaObject->setCurrentSource(Phonon::MediaSource(m_ListeSon.at(1)));
        break;
        case 69: //Ascii de E
            mediaObject->setCurrentSource(Phonon::MediaSource(m_ListeSon.at(2)));
        break;
        case 82: //Ascii de R
            mediaObject->setCurrentSource(Phonon::MediaSource(m_ListeSon.at(3)));
        break;
        case 84: //Ascii de T
            mediaObject->setCurrentSource(Phonon::MediaSource(m_ListeSon.at(4)));
        break;
        case 89: //Ascii de Y
            mediaObject->setCurrentSource(Phonon::MediaSource(m_ListeSon.at(3)));
        break;
    }
    mediaObject->play();
}
