#ifndef THREAD_RECEPTION_H
#define THREAD_RECEPTION_H

#include <QThread>
#include <Phonon>
#include<QTcpSocket>
#include <QDir>
#include <QMutex>

class Thread_Reception : public QThread
{
    Q_OBJECT
public:
    Thread_Reception(int instrument, QString IP);
    QStringList m_ListeSon;

private:
    QString m_IP;
    bool m_Etat;

    void JouerSon(int note);

protected:
    void run();
};

#endif // THREAD_RECEPTION_H
