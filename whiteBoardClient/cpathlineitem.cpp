#include "cpathlineitem.h"


CPathLineItem::CPathLineItem(QGraphicsItem* parentItem)
    :QGraphicsItem(parentItem)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QRectF CPathLineItem::boundingRect() const
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

void CPathLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    if (!m_closePixmap.isNull())
        painter->drawPixmap(QRect(outLintRect.topRight().x() - m_nEllipseWidth / 2, \
                                  outLintRect.topRight().y() - m_nEllipseWidth / 2, \
                                  m_nEllipseWidth, m_nEllipseWidth), m_closePixmap);

  painter->drawEllipse(outLintRect.bottomLeft(), m_nEllipseWidth, m_nEllipseWidth);
    if (!m_rotatePixmap.isNull())
        painter->drawPixmap(QRect(outLintRect.bottomLeft().x() - m_nEllipseWidth / 2, \
                                  outLintRect.bottomLeft().y() - m_nEllipseWidth / 2, \
                                  m_nEllipseWidth, m_nEllipseWidth), m_rotatePixmap);

   if (m_isResizeable)
   {
       painter->drawEllipse(outLintRect.bottomRight(), m_nEllipseWidth, m_nEllipseWidth);
        if (!m_resizePixmap.isNull())
            painter->drawPixmap(QRect(outLintRect.bottomRight().x() - m_nEllipseWidth / 2, \
                                      outLintRect.bottomRight().y() - m_nEllipseWidth / 2, \
                                      m_nEllipseWidth, m_nEllipseWidth), m_resizePixmap);
   }
}

void CPathLineItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    QPen pen;
    pen.setWidth(m_nPenWidth);
    pen.setColor(m_cPenColor);
    painter->setPen(pen);

    painter->drawPath(m_painterPath);
    painter->restore();
}

QRectF CPathLineItem::getCustomRect() const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}

void CPathLineItem::addPoint(const QPointF &scenePos)
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

void CPathLineItem::setStartPos(const QPointF &startScenePos)
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

void CPathLineItem::endDrawPos()
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

QJsonObject CPathLineItem::getJson(bool bSt, bool bEnd)
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
    QJsonObject object
    {
        {"Mode",2},
        {"ItemType",0},
        {"firstPnt",pt1},
        {"secondPnt",pt2},
        {"bStart",bSt},
        {"bEnd",bEnd}
    };
    return object;
}


QPainterPath CPathLineItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

//void CPathLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    QRectF itemRect = this->getCustomRect();
//    QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

//    // 获取当前模式
//    QPointF pos = event->pos();
//    QPointF scenePos = event->scenePos();
//    if (itemRect.contains(pos))
//        m_itemOper = Op_Move;
//    else if (pntDistance(pos, outLintRect.topRight()) <= m_nEllipseWidth)
//        this->deleteLater();
//    else if (pntDistance(pos, outLintRect.bottomLeft()) <= m_nEllipseWidth)
//        m_itemOper = Op_Rotate;
//    else if (pntDistance(pos, outLintRect.bottomRight()) <= m_nEllipseWidth)
//        m_itemOper = Op_Resize;

//    // 保存当前的一些信息
//    m_pos = pos;
//    m_pressedPos = scenePos;
//    m_startPos = this->pos();
//    return QGraphicsItem::mousePressEvent(event);
//}

//void CPathLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    // 获取场景坐标和本地坐标
//    QPointF scenePos = event->scenePos();
//    QPointF pos = event->pos();

//    if (m_itemOper == Op_Move)
//    {
//        // 处理移动
//        mouseMoveMoveOperator(scenePos, pos);
//    }
//    else if (m_itemOper == Op_Resize)
//    {
//        // 处理更改大小
//        mouseMoveResizeOperator(scenePos, pos);
//    }
//    else if (m_itemOper == Op_Rotate)
//    {
//        // 处理旋转
//        mouseMoveRotateOperator(scenePos, pos);
//    }

//    return QGraphicsItem::mouseMoveEvent(event);
//}

//void CPathLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    m_itemOper = Op_None;
//    return QGraphicsItem::mouseReleaseEvent(event);
//}

void CPathLineItem::mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    qreal xInterval = scenePos.x() - m_pressedPos.x();
    qreal yInterval = scenePos.y() - m_pressedPos.y();

    this->setPos(m_startPos + QPointF(xInterval, yInterval));
    this->update();
}

void CPathLineItem::mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    if (!m_isResizeable)
        return;

    qreal ratio = m_ratioValue;
    qreal itemWidth = abs(loacalPos.x()) * 2 - m_nInterval - m_nEllipseWidth;
    qreal itemHeight = abs(loacalPos.y()) * 2 - m_nInterval - m_nEllipseWidth;
    if (m_isRatioScale)
        itemHeight = itemWidth * 1.0 / ratio;

    // 设置图片的最小大小为10
    if (itemWidth < 10 || itemHeight < 10)
        return;

    m_size = QSize(itemWidth, itemHeight);
 //   m_pWidthAttribute->setCurrentValue(m_size.width());
 //   m_pHeightAttribute->setCurrentValue(m_size.height());

    this->update();
}

void CPathLineItem::mouseMoveRotateOperator(const QPointF& scenePos, const QPointF& loacalPos)
{
    // 获取并设置为单位向量
    QVector2D startVec(m_pos.x() - 0, m_pos.y() - 0);
    startVec.normalize();
    QVector2D endVec(loacalPos.x() - 0, loacalPos.y() - 0);
    endVec.normalize();

    // 单位向量点乘，计算角度
    qreal dotValue = QVector2D::dotProduct(startVec, endVec);
    if (dotValue > 1.0)
        dotValue = 1.0;
    else if (dotValue < -1.0)
        dotValue = -1.0;

    dotValue = qAcos(dotValue);
    if (isnan(dotValue))
        dotValue = 0.0;

    // 获取角度
    qreal angle = dotValue * 1.0 / (PI / 180);

    // 向量叉乘获取方向
    QVector3D crossValue = QVector3D::crossProduct(QVector3D(startVec, 1.0),QVector3D(endVec, 1.0));
    if (crossValue.z() < 0)
        angle = -angle;
    m_rotate += angle;

    // 设置角度在0~360之间
    if (m_rotate >= 360)
        m_rotate -= 360;
    else if (m_rotate < 0)
        m_rotate += 360;

    // 设置变化矩阵
    QTransform transform;
    transform.rotate(m_rotate);
    this->setTransform(transform);
 //   m_pRotateAttribute->setCurrentValue(m_rotate);

    this->update();
}


