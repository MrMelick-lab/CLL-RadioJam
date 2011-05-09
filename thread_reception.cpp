#include "thread_reception.h"

Thread_Reception::Thread_Reception(int instrument, QString IP)
{
    m_IP = IP;
    QDir dossier;
    if(instrument == 0)
    {
        dossier = QDir(QDir::currentPath() + "/Bass");
        m_NomInstrument = "Bass/";
    }
    else
    {
        dossier = QDir(QDir::currentPath() + "/Drum");
        m_NomInstrument = "Drum/";
    }
    m_ListeSon = dossier.entryList();
}

void Thread_Reception::run()
{
    QTcpSocket socket;
    QByteArray baReception;
    socket.connectToHost(m_IP,22224);
    if (socket.waitForConnected(1000)) //Attente d'1 sec maximum sinon, fermer le socket
    {
        while(m_Etat)
        {
            if (socket.waitForReadyRead(100))
            {
                baReception.append(socket.readAll());
                JouerSon(baReception.at(0));
                baReception.clear(); // Vidage de la variable de réception pour la réutiliser
                //VA CHIER JE T'AI MODIFIÉ!!!!!!!!! ALORS COMMIT TOI!!!
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
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(0)));
        break;
        case 87: //Ascii de W
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(1)));
        break;
        case 69: //Ascii de E
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(2)));
        break;
        case 82: //Ascii de R
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(3)));
        break;
        case 84: //Ascii de T
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(4)));
        break;
        case 89: //Ascii de Y
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(5)));
        break;
        case 85: //Ascii de U
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(6)));
        break;
        case 65: //Ascii de A
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(7)));
        break;
        case 83: //Ascii de S
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(8)));
        break;
        case 68: //Ascii de D
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(9)));
        break;
        case 70: //Ascii de F
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(10)));
        break;
        case 71: //Ascii de G
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(11)));
        break;
        case 72: //Ascii de H
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(12)));
        break;
        case 74: //Ascii de J
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(13)));
        break;
        case 75: //Ascii de K
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(14)));
        break;
    }
    mediaObject->play();
}
