#ifndef CCIRCLEITEM_H
#define CCIRCLEITEM_H

#include "citembase.h"
#include <QGraphicsEllipseItem>



class CCircleItem : public  CItemBase,public QGraphicsEllipseItem
{
public:
    CCircleItem(QGraphicsItem *parent = nullptr);
public:
    void setFirstPt(QPointF pt);
    void setEndPt(QPointF pt);
    void update();
    QJsonObject getJson(bool bSt = false,bool bEnd = false);
private:
    QPointF firstPt;
    QPointF secondPt;
    qreal  width = 1;
    qreal  hight = 1;
};

#endif // CCIRCLEITEM_H
