#include "ceraseitem.h"
#include <QJsonObject>

CEraseItem::CEraseItem(QGraphicsItem* parentItem)
    :QGraphicsItem(parentItem)
    ,m_cPenColor(255, 0, 0)
    ,m_cBrushColor(200, 100, 100)
{
   //  this->setItemResizeable(false);
    m_cPenColor = QColor(255, 255, 255);
    m_nPenWidth = 10;
}

QRectF CEraseItem::boundingRect() const
{
    QPointF centerPos(0, 0);
    QRectF tempRect =  QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
    if (!this->isSelected())
        return tempRect;

    tempRect.adjust(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    tempRect.adjust(-m_nEllipseWidth, -m_nEllipseWidth, m_nEllipseWidth, m_nEllipseWidth);
    return tempRect;
}

void CEraseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // 自定义绘制
    customPaint(painter, option, widget);

    return;
    if (!this->isSelected())
        return;

    // 设置画笔
    QPen pen;
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    QRectF itemRect = this->getCustomRect();

    // 绘制轮廓线
    QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    painter->drawRect(outLintRect);

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_cBrushColor);

    // 绘制控制点
    painter->drawEllipse(outLintRect.topRight(), m_nEllipseWidth, m_nEllipseWidth);
//    if (!m_closePixmap.isNull())
//        painter->drawPixmap(QRect(outLintRect.topRight().x() - m_nEllipseWidth / 2, \
//                                  outLintRect.topRight().y() - m_nEllipseWidth / 2, \
//                                  m_nEllipseWidth, m_nEllipseWidth), m_closePixmap);

    painter->drawEllipse(outLintRect.bottomLeft(), m_nEllipseWidth, m_nEllipseWidth);
//    if (!m_rotatePixmap.isNull())
//        painter->drawPixmap(QRect(outLintRect.bottomLeft().x() - m_nEllipseWidth / 2, \
//                                  outLintRect.bottomLeft().y() - m_nEllipseWidth / 2, \
//                                  m_nEllipseWidth, m_nEllipseWidth), m_rotatePixmap);

 //   if (m_isResizeable)
 //   {
 //       painter->drawEllipse(outLintRect.bottomRight(), m_nEllipseWidth, m_nEllipseWidth);
//        if (!m_resizePixmap.isNull())
//            painter->drawPixmap(QRect(outLintRect.bottomRight().x() - m_nEllipseWidth / 2, \
//                                      outLintRect.bottomRight().y() - m_nEllipseWidth / 2, \
//                                      m_nEllipseWidth, m_nEllipseWidth), m_resizePixmap);
//   }
}

void CEraseItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    QPen pen;
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    painter->setPen(pen);

    painter->drawPath(m_painterPath);
    painter->restore();
}

QRectF CEraseItem::getCustomRect() const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}

void CEraseItem::addPoint(const QPointF &scenePos)
{
    QPointF localPos = this->mapFromScene(scenePos);
    m_tempPoint = localPos;
    m_painterPath.lineTo(localPos);
    // 设置矩形
    QRectF boundRect = m_painterPath.boundingRect();
    m_size = QSize(boundRect.width(), boundRect.height());


    qreal itemWidth = abs(localPos.x()) * 2 - m_nInterval - m_nEllipseWidth;
    qreal itemHeight = abs(localPos.y()) * 2 - m_nInterval - m_nEllipseWidth;

    // 设置图片的最小大小为10
    if (itemWidth < 10 || itemHeight < 10)
        return;

    m_size = QSize(itemWidth, itemHeight);

    this->update();
}

void CEraseItem::setStartPos(const QPointF &startScenePos)
{
    QPointF localPos = this->mapFromScene(startScenePos);

    // 设置起始点
    m_hasPoints = true;
    m_painterStartPos = localPos;
    m_painterPath.moveTo(localPos);

    // 设置矩形
    QRectF boundRect = m_painterPath.boundingRect();
    m_size = QSize(boundRect.width(), boundRect.height());

    this->update();
}

void CEraseItem::endDrawPos()
{
    // 设置矩形
    QRectF boundRect = m_painterPath.boundingRect();
    m_size = QSize(boundRect.width(), boundRect.height());

    QPointF centerPos = boundRect.center();
    this->setPos(centerPos);

    m_painterPath.translate(-centerPos.x(), -centerPos.y());

    m_hadAddPointFinished = true;
    this->prepareGeometryChange();

    this->update();
}

void CEraseItem::setColor(QColor color)
{
   // this->m_cPenColor = color;
    this->m_cPenColor = QColor(255, 255, 255);
}

void CEraseItem::setWidth(int width)
{
    this->m_nPenWidth = width;
}

QJsonObject CEraseItem::getJson(bool bSt, bool bEnd)
{
    QPointF FirstPtScene;
    QPointF SecondPtScene;
    FirstPtScene = mapToScene(m_painterStartPos);
    SecondPtScene = mapToScene(m_tempPoint);
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
        {"ItemType",5},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bStart",bSt},
        {"bEnd",bEnd}
    };
    return object;
}




