#include "cmainserver.h"

CMainServer::CMainServer(QObject *parent):QTcpServer(parent)
{

}

CMainServer::~CMainServer()
{

}

void CMainServer::incomingConnection(qintptr handle)
{
    qDebug() << Q_FUNC_INFO << " isComingConnection run";
    CConnection *pConn = new CConnection(this);
    if(pConn == nullptr) return;

    connect(pConn, &CConnection::sendToClients,
            this, &CMainServer::sendToClientfun);

    pConn->setSocketDescriptor(handle);
    arrConnection.push_back(pConn);
}

void CMainServer::sendToClientfun(QJsonObject aJson)
{
    CConnection* senderCon = qobject_cast<CConnection*>(sender());

    for (auto con : arrConnection) {
        if(senderCon == con) continue;
        con->sendData(aJson);
    }
}
