#include "crectitem.h"
#include <QPen>

CRectItem::CRectItem(QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(255,0,0));
    setPen(pen);
}

void CRectItem::SetFirstPt(QPointF pt)
{
    FirstPt = mapFromScene(pt);
}

void CRectItem::SetEndPt(QPointF pt)
{
    QPointF localEndPt = mapFromScene(pt);
    SecondPt = localEndPt;
    qreal  width = localEndPt.x() - FirstPt.x();
    qreal  hight = localEndPt.y() - FirstPt.y();
    this->setRect(FirstPt.x(),FirstPt.y(),width,hight);
}

void CRectItem::update()
{
    QPen pen;
    pen.setWidth(this->m_nPenWidth);
    pen.setColor(this->m_cPenColor);
    setPen(pen);
}

QJsonObject CRectItem::getJson(bool bSt, bool bEnd)
{
    QString pt1 = QString("%1,%2")
            .arg(FirstPt.x()).arg(FirstPt.y());
    QString pt2 = QString("%1,%2")
            .arg(SecondPt.x()).arg(SecondPt.y());
    if(bSt)
    {
        pt2 = pt1;
    }
    QJsonObject result;
    QString strJson;
    QJsonObject object
    {
        {"Mode",1},
        {"ItemType",3},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bStart",bSt},
        {"bEnd",bEnd}
    };
    return object;
}
