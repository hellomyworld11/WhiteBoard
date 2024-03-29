#include "citembase.h"
#include <cmath>
#include <math.h>

QImage CItemBase::m_closeIcon;
QImage CItemBase::m_resizeIcon;
QImage CItemBase::m_rotateIcon;

CItemBase::CItemBase(QGraphicsItem *parent)
    :m_cPenColor(255, 0, 0)
,m_cBrushColor(200, 100, 100)
{
    initIcon();
}

CItemBase::~CItemBase()
{

}

void CItemBase::setColor(QColor color)
{
    this->m_cPenColor = color;
}

void CItemBase::setWidth(int width)
{
    this->m_nPenWidth = width;
}




QRectF CItemBase::getCustomRect() const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}

void CItemBase::initIcon()
{
    if (m_closeIcon.isNull())
        m_closeIcon.load(":/res/close.jpg");
    if (m_resizeIcon.isNull())
        m_resizeIcon.load(":/res/resize.jpg");
    if (m_rotateIcon.isNull())
        m_rotateIcon.load("./Images/rotate.png");

    m_closePixmap = QPixmap::fromImage(m_closeIcon);
    m_resizePixmap = QPixmap::fromImage(m_resizeIcon);
    m_rotatePixmap = QPixmap::fromImage(m_rotateIcon);
}

