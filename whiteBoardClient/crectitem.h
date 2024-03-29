#ifndef CRECTITEM_H
#define CRECTITEM_H
#include "citembase.h"
#include <QGraphicsRectItem>
#include <QGraphicsItem>

class CRectItem :public CItemBase,public QGraphicsRectItem
{
public:
    CRectItem(QGraphicsItem *parent = nullptr);
public:
    void SetFirstPt(QPointF pt);
    void SetEndPt(QPointF pt);
    void update();
    QJsonObject getJson(bool bSt = false, bool bEnd = false);
private:
    QPointF FirstPt;
    QPointF SecondPt;
};

#endif // CRECTITEM_H
