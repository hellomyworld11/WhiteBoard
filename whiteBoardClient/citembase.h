#ifndef CITEMBASE_H
#define CITEMBASE_H
#include "util.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <cmath>
#include <math.h>


class CItemBase :public QObject
{
    Q_OBJECT
public:
    enum ItemOp{
        Op_None,
        Op_Move,
        Op_Resize,
        Op_Rotate
    };
    CItemBase(QGraphicsItem *parent = nullptr);
    ~CItemBase();
public:
    void setItemResizeable(bool resizeable);
    void setItemResizeRatioable(bool resizeable,qreal ratioValue);
    void setColor(QColor color);
    void setWidth(int width);
public slots:
private:
    void initIcon();
protected:
    // 获取自定义绘制所需要的矩形
    QRectF getCustomRect(void) const;
protected:
    QSize m_size;
    ItemOp m_itemOper = Op_None;

    QPixmap m_closePixmap;   //选择item时显示的框的图片
    QPixmap m_resizePixmap;
    QPixmap m_rotatePixmap;

    static QImage m_closeIcon;
    static QImage m_resizeIcon;
    static QImage m_rotateIcon;
    // 设置是否能够更改尺寸
    bool m_isResizeable = true;
    bool m_isRatioScale = true;
    qreal m_ratioValue = 1.0;

    // 画笔设置
    QColor m_cPenColor;
    int m_nPenWidth = 1;
    // 画刷设置
    QColor m_cBrushColor;

    int m_nInterval = 20;
    int m_nEllipseWidth = 12;    // 半径

    QPointF m_pos;              // 本地所坐标点击的点
    QPointF m_pressedPos;       // 场景坐标点击的点
    QPointF m_startPos;         // Item再场景坐标的起始坐标
    QTransform m_transform;     // 变换矩阵
    qreal m_rotate = 0.0;       // 当前旋转角度

};

#endif // CITEMBASE_H
