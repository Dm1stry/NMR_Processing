#ifndef ILOGGABLE_H
#define ILOGGABLE_H

#include <QObject>

class ILoggable : public QObject
{
Q_OBJECT
signals:
    void printLog(const QString&);
};

Q_DECLARE_INTERFACE(ILoggable, "log-interface")

#endif