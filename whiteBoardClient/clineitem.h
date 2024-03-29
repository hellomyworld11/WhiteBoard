#ifndef CLINEITEM_H
#define CLINEITEM_H
#include <QGraphicsLineItem>
#include "citembase.h"


class CLineItem : public CItemBase,public QGraphicsLineItem
{
public:
    CLineItem(QGraphicsItem *parent = nullptr);
public:
    void SetFirstPt(QPointF pt);
    void SetEndPt(QPointF pt);
    void update();
    QJsonObject getJson(bool bSt = false,bool bEnd = false);
private:
    QPointF FirstPt;
    QPointF SecondPt;
};

#endif // CLINEITEM_H
