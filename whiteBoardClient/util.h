#ifndef UTIL_H
#define UTIL_H

#define is_ptr_vaild(ptr) (ptr!=Q_NULLPTR)
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QToolBar>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QVector2D>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "log.h"
#define PI 3.1415926
bool doubleCompare(qreal d1, qreal d2, int ac = 0.000001);
qreal pntDistance(QPointF pnt1, QPointF pnt2);


const  QString serverIp  = "192.168.0.103";
const  quint16 serverPort = 10086;




#endif // UTIL_H

