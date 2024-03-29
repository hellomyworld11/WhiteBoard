#ifndef CERASEITEM_H
#define CERASEITEM_H

#include <QGraphicsItem>
#include <QVector>
#include <QPainter>



class CEraseItem : public QGraphicsItem
{
public:
    CEraseItem(QGraphicsItem* parentItem = nullptr);
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    virtual void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // 获取自定义绘制所需要的矩形
    QRectF getCustomRect(void) const;
    // 添加点
    void addPoint(const QPointF& scenePos);
    // 设置起始点
    void setStartPos(const QPointF& startScenePos);
    // 结束设置
    void endDrawPos(void);

    void initAttribute(void);

    void setColor(QColor color);
    void setWidth(int width);

    QJsonObject getJson(bool bSt = false,bool bEnd = false);
public:
    QSize m_size;
    int m_nInterval = 20;
    int m_nEllipseWidth = 12;    // 半径
    // 画笔设置
    QColor m_cPenColor;
    int m_nPenWidth = 1;
    // 画刷设置
    QColor m_cBrushColor;
    QPainterPath m_painterPath;
    bool m_hasPoints = false;
    bool m_hadAddPointFinished = false;
    QPointF m_painterStartPos;

    QPointF m_tempPoint;
private:
    QVector<double> arrPt;
};

#endif // CPATHLINEITEM_H
