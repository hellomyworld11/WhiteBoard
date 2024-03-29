#ifndef CPATHLINEITEM_H
#define CPATHLINEITEM_H
#include <QGraphicsItem>
#include <QVector>
#include <QPainter>
#include "citembase.h"
#include <cmath>
#include <math.h>
#include <QVector2D>
#include <QVector3D>
#include <QtMath>

class CPathLineItem : public CItemBase,public QGraphicsItem
{
public:
    CPathLineItem(QGraphicsItem* parentItem = nullptr);
    //所有item实现的******************
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // 获取自定义绘制所需要的矩形
    QRectF getCustomRect(void) const;

    QPainterPath shape() const override;
    //TODO
#if 0
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
#endif
    // 处理Item上的类型
    virtual void mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveRotateOperator(const QPointF& scenePos, const QPointF& loacalPos);
    //******************************
   // void update();
public:
    // 添加点
    void addPoint(const QPointF& scenePos);
    // 设置起始点
    void setStartPos(const QPointF& startScenePos);
    // 结束设置
    void endDrawPos(void);

    QJsonObject getJson(bool bSt = false,bool bEnd = false);
public:
    QPainterPath m_painterPath;
    bool m_hasPoints = false;
    bool m_hadAddPointFinished = false;
    QPointF m_painterStartPos;

    QPointF m_tempPoint;
};

#endif // CPATHLINEITEM_H
