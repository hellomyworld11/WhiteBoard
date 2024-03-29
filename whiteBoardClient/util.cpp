#include "util.h"

bool doubleCompare(qreal d1,qreal d2,int ac)
{
    if (abs(d1 - ac) <= ac)
        return true;
    return false;
}

qreal pntDistance(QPointF pnt1,QPointF pnt2)
{
    QVector2D vec1(pnt1);
    QVector2D vec2(pnt2);
    return vec1.distanceToPoint(vec2);
}
