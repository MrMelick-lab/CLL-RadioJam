#ifndef THREAD_RECEPTION_H
#define THREAD_RECEPTION_H

#include <QThread>
#include <Phonon>
#include<QTcpSocket>
#include <QDir>
#include <thread_lien_serveur.h>

class Thread_Reception : public QThread
{
    Q_OBJECT
public:
    Thread_Reception(QString IP, QString Nom, int Instrument);

private:
    QString m_IP;
    QString m_Nom;
    QStringList m_ListeSon;
    int m_Instrument;
    bool m_Etat;
    QString m_NomInstrument;
    QByteArray m_baReception;

    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

    void JouerSon(int note);

protected:
    void run();

signals:
    void NoteRecue(int note);

    void PartirThreadSon();
};

#endif // THREAD_RECEPTION_H
