#include "ctrangleitem.h"
#include <QPen>

CTrangleItem::CTrangleItem(QGraphicsItem *parent)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(255,0,0));
    setPen(pen);
}

void CTrangleItem::SetFirstPt(QPointF pt)
{
    FirstPt = mapFromScene(pt);
}

void CTrangleItem::SetEndPt(QPointF pt)
{
    QPointF localEndPt = mapFromScene(pt);
    QPointF secondPt(FirstPt.x(),localEndPt.y());
    SecondPt = localEndPt;
    QPolygonF aPolygon;
    aPolygon << FirstPt << secondPt << localEndPt;
    this->setPolygon(aPolygon);
}

void CTrangleItem::update()
{
    QPen pen;
    pen.setWidth(this->m_nPenWidth);
    pen.setColor(this->m_cPenColor);
    setPen(pen);
}

QJsonObject CTrangleItem::getJson(bool bSt, bool bEnd)
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
        {"ItemType",4},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bStart",bSt},
        {"bEnd",bEnd}
    };
    return object;
}
