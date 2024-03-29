#ifndef CTRANGLEITEM_H
#define CTRANGLEITEM_H
#include "citembase.h"
#include <QGraphicsPolygonItem>
#include <QPolygonF>


class CTrangleItem :public CItemBase, public QGraphicsPolygonItem
{
public:
    CTrangleItem(QGraphicsItem *parent = nullptr);
public:
    void SetFirstPt(QPointF pt);
    void SetEndPt(QPointF pt);
    void update();
    QJsonObject getJson(bool bSt = false, bool bEnd = false);
private:
    QPointF FirstPt;
    QPointF SecondPt;
};

#endif // CTRANGLEITEM_H
