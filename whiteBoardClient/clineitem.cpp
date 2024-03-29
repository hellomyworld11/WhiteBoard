#include "clineitem.h"
#include <QPen>
CLineItem::CLineItem(QGraphicsItem *parent)
    :QGraphicsLineItem(parent)
{
//    QPen pen;
//    pen.setWidth(1);
//    pen.setColor(QColor(255,0,0));
//    setPen(pen);
}

void CLineItem::SetFirstPt(QPointF pt)
{ 
    //QPointF scenePos = mapToScene(pt);
    FirstPt =  mapFromScene(pt);
}

void CLineItem::SetEndPt(QPointF pt)
{
     QPointF localEndPt = mapFromScene(pt);
     SecondPt = localEndPt;
     this->setLine(QLineF(FirstPt,localEndPt));
     //更新json表示
}

void CLineItem::update()
{
    QPen pen;
    pen.setWidth(this->m_nPenWidth);
    pen.setColor(this->m_cPenColor);
    setPen(pen);
}

QJsonObject CLineItem::getJson(bool bSt,bool bEnd)
{
    QPointF FirstPtScene;
    QPointF SecondPtScene;
    FirstPtScene = mapToScene(FirstPt);
    SecondPtScene = mapToScene(SecondPt);
    QString pt1 = QString("%1,%2")
            .arg(FirstPtScene.x()).arg(FirstPtScene.y());
    QString pt2 = QString("%1,%2")
            .arg(SecondPtScene.x()).arg(SecondPtScene.y());
    if(bSt)
    {
        pt2 = pt1;
    }
    QJsonObject result;
    QString strJson;
    QJsonObject object
    {
        {"Mode",1},
        {"ItemType",1},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bStart",bSt},
        {"bEnd",bEnd}
    };
    return object;
//    strJson = QString("{"
//                      ""Mode":%1,"
//                      ""ItemType":%2,"
//                      ""firstPnt":%3,"
//                      ""secondPnt":%4,"
//                      ""bEnd":%5"
//                      "}").arg(1).arg(1).arg(pt1).arg(pt2).arg(bEnd);
}
