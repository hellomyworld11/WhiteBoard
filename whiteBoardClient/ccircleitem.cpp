#include "ccircleitem.h"
#include <QPen>
CCircleItem::CCircleItem(QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
    this->update();
}

void CCircleItem::setFirstPt(QPointF pt)
{
     firstPt =  QGraphicsEllipseItem::mapFromScene(pt);
}

void CCircleItem::setEndPt(QPointF pt)
{
    QPointF localEndPt = QGraphicsEllipseItem::mapFromScene(pt);
    secondPt = localEndPt;
    width = localEndPt.x() - firstPt.x();
    hight = localEndPt.y() - firstPt.y();
    this->setRect(firstPt.x(),firstPt.y(),width,hight);
    //this->setLine(QLineF(FirstPt,localEndPt));
}

void CCircleItem::update()
{
   QPen pen;
   pen.setWidth(this->m_nPenWidth);
   pen.setColor(this->m_cPenColor);
   setPen(pen);
}

QJsonObject CCircleItem::getJson(bool bSt, bool bEnd)
{
    QPointF FirstPtScene;
    QPointF SecondPtScene;
    FirstPtScene = mapToScene(firstPt);
    SecondPtScene = mapToScene(secondPt);
    QString pt1 = QString("%1,%2")
            .arg(FirstPtScene.x()).arg(FirstPtScene.y());
    QString pt2 = QString("%1,%2")
            .arg(SecondPtScene.x()).arg(SecondPtScene.y());

    if(bSt)
    {
        pt2 = pt1;
    }
    QJsonObject result;
    QJsonObject object
    {
        {"Mode",1},
        {"ItemType",2},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bStart",bSt},
        {"bEnd",bEnd}
    };
    return object;
}
