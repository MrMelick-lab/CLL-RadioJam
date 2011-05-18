#ifndef THREAD_SON_H
#define THREAD_SON_H
#include <QThread>
#include <Phonon>
#include<QTcpSocket>
#include <QDir>

class Thread_Son : public QThread
{
    Q_OBJECT
    public:
        Thread_Son(QString, int);

    private:
        QString m_Nom;
        QString m_NomInstrument;
        QStringList m_ListeSon;
        int m_Instrument;

    private slots:
       void JouerSon(int note);


};

#endif // THREAD_SON_H
