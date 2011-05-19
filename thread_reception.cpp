#include "thread_reception.h"

Thread_Reception::Thread_Reception(QString IP,QString Nom, int Instrument)
{
    m_IP = IP;
    m_Etat = true;
    m_Nom = Nom;
    m_Instrument = Instrument;
    QDir dossier;
    if(Instrument == 1)
    {
        dossier = QDir(QDir::currentPath() + "/Basse");
        m_NomInstrument = "Basse/";
    }
    else
    {
        dossier = QDir(QDir::currentPath() + "/Drum");
        m_NomInstrument = "Drum/";
    }
    m_ListeSon = dossier.entryList();
    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory,this);

}

void Thread_Reception::run()
{

    QTcpSocket socket;
    socket.connectToHost(m_IP,22224);
    if (socket.waitForConnected(1000)) //Attente d'1 sec maximum sinon, fermer le socket
    {
        Phonon::createPath(mediaObject, audioOutput);
        mediaObject->setCurrentSource(Phonon::MediaSource("ouverture_cool.mp3"));
        mediaObject->play();
        while(m_Etat)
        {
            if (socket.waitForReadyRead(100))
            {
                m_baReception.append(socket.read(1));
                JouerSon(m_baReception.at(0));
                m_baReception.clear(); // Vidage de la variable de réception pour la réutiliser
            }
        }
    }
    sleep(10);
    socket.disconnectFromHost(); // Annonce de déconnexion au serveur
    socket.close(); // Fermeture du socket
}

void Thread_Reception::JouerSon(int note)
{

    Phonon::createPath(mediaObject, audioOutput);
    switch(note) // suite va de q à u et de a à k
    {
        case 81: //Ascii de Q
            mediaObject->setCurrentSource(Phonon::MediaSource(QDir::currentPath() + m_NomInstrument + m_ListeSon.at(2)));
            mediaObject->play();
        break;
        case 87: //Ascii de W
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(2)));
            mediaObject->play();
        break;
        case 69: //Ascii de E
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(3)));
            mediaObject->play();
        break;
        case 82: //Ascii de R
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(4)));
            mediaObject->play();
        break;
        case 84: //Ascii de T
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(5)));
            mediaObject->play();
        break;
        case 89: //Ascii de Y
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(6)));
            mediaObject->play();
        break;
        case 85: //Ascii de U
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(7)));
            mediaObject->play();
        break;
        case 65: //Ascii de A
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(8)));
            mediaObject->play();
        break;
        case 83: //Ascii de S
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(9)));
            mediaObject->play();
        break;
        case 68: //Ascii de D
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(10)));
            mediaObject->play();
        break;
        case 70: //Ascii de F
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(11)));
            mediaObject->play();
        break;
        case 71: //Ascii de G
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(12)));
            mediaObject->play();
        break;
        case 72: //Ascii de H
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(13)));
            mediaObject->play();
        break;
        case 74: //Ascii de J
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(14)));
            mediaObject->play();
        break;
        case 75: //Ascii de K
            mediaObject->setCurrentSource(Phonon::MediaSource(m_NomInstrument + m_ListeSon.at(15)));
            mediaObject->play();
        break;
     }
}
