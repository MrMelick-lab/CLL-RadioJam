#ifndef THREAD_RECEPTION_H
#define THREAD_RECEPTION_H

#include <QThread>
#include <Phonon>
#include<QTcpSocket>

class Thread_Reception : public QThread
{
    Q_OBJECT
public:
    Thread_Reception(int instrument, QString IP);

private:
    int m_Instrument;
    QString m_IP;
    bool m_Etat;

protected:
    void run();
};

#endif // THREAD_RECEPTION_H
