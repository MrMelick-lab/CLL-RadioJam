#ifndef THREAD_RECEPTION_H
#define THREAD_RECEPTION_H
#include <QThread>

class Thread_Reception : public QThread
{
    Q_OBJECT
public:
    Thread_Reception();
};

#endif // THREAD_RECEPTION_H
