#ifndef CCONNECTION_H
#define CCONNECTION_H
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

//连接
class CConnection : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CConnection(QObject *parent = nullptr);
    ~CConnection();
    QString info();
    void initConnect();
    QJsonObject getJson();
    void sendData(QJsonObject ajson);
signals:
    void sendToClients(QJsonObject ajson);
protected slots:
    void onReadyRead();
};

#endif // CCONNECTION_H
