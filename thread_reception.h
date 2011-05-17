#ifndef THREAD_RECEPTION_H
#define THREAD_RECEPTION_H

#include <QThread>
#include <Phonon>
#include<QTcpSocket>
#include <QDir>
#include <QMutex>
#include <thread_son.h>

class Thread_Reception : public QThread
{
    Q_OBJECT
public:
    Thread_Reception(QString IP);
    QStringList m_ListeSon;

private:
    QString m_IP;
    bool m_Etat;
    QString m_NomInstrument;
    QByteArray m_baReception;

protected:
    void run();

signals:
    void NoteRecue(int note);

private slots:
    void RecevoirNomIns(QString, int);
};

#endif // THREAD_RECEPTION_H
