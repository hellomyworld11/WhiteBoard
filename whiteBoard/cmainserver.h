#ifndef CMAINSERVER_H
#define CMAINSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include "cconnection.h"
#include <QVector>
#include <QJsonObject>

//服务器
class CMainServer : public QTcpServer
{
public:
    CMainServer(QObject *parent = 0);
    ~CMainServer();

protected:
    virtual void incomingConnection(qintptr handle);

protected slots:
    void sendToClientfun(QJsonObject aJson);
private:
    QVector<CConnection*> arrConnection;
};

#endif // CMAINSERVER_H
