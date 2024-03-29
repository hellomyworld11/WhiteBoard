#include "cconnection.h"

CConnection::CConnection(QObject *parent)
    : QTcpSocket{parent}
{
    initConnect();
}

CConnection::~CConnection()
{

}

QString CConnection::info()
{
    QString str = QString("address:%1,port:%2").arg(this->peerAddress().toString()).arg(this->peerPort());
    return str;
}

void CConnection::initConnect()
{
    connect(this,&CConnection::readyRead,this,&CConnection::onReadyRead);
}

QJsonObject CConnection::getJson()
{
    QString pt1 = QString("%1,%2")
            .arg(200).arg(200);
    QString pt2 = QString("%1,%2")
            .arg(200).arg(400);

    QJsonObject result;
    QString strJson;
    QJsonObject object
    {
        {"Mode",1},
        {"ItemType",1},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bEnd",1}
    };
    return object;
}

void CConnection::sendData(QJsonObject ajson)
{
     QJsonDocument jsonDoc(ajson);
     this->write(jsonDoc.toJson() );
}

void CConnection::onReadyRead()
{
    //qDebug() << "read" ;
    QByteArray data = this->readAll();
    //data.append("send back");
    qDebug() << "read data" << data ;
    //this->write(data);
    QJsonObject json;
    QJsonDocument jsondoc = QJsonDocument::fromJson(data);
    if(jsondoc.isObject())
    {
       json = jsondoc.object();
       //sendData(json);
       emit sendToClients(json);
    }
}

