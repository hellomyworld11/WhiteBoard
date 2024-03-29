#include "cboardoper.h"
#include "cboardview.h"
CboardOper::CboardOper(CBoardView *pView):m_plocView(pView)
{

}

CboardOper::~CboardOper()
{

}

bool CboardOper::onPressEvent(QMouseEvent *event)
{
    return false;
}

bool CboardOper::onMoveEvent(QMouseEvent *event)
{
    return false;
}

bool CboardOper::onReleaseEvent(QMouseEvent *event)
{
    m_plocView->setOper(new CBoardDefaultOper(m_plocView));
    return false;
}

bool CboardOper::onKeyPressEvent(QKeyEvent *event)
{
    return false;
}

CBoardDefaultOper::CBoardDefaultOper(CBoardView *pView):CboardOper(pView)
{

}

CBoardDefaultOper::~CBoardDefaultOper()
{

}

bool CBoardDefaultOper::onPressEvent(QMouseEvent *event)
{
    auto selectitems = m_plocView->scene()->selectedItems();
    auto items = m_plocView->items(event->pos());

    CBoardView::Mode curMode = m_plocView->getMode();
    if(curMode == CBoardView::Mode::SelectItem)
    {
        if (/*selectitems.size() > 1 &&*/ items.size() > 0)
        {
            CBoardMoveSelectOper * moveSelectOper = new CBoardMoveSelectOper(m_plocView);
            m_plocView->setOper(moveSelectOper);
            return moveSelectOper->onPressEvent(event);
        }
    }
    return true;
}

bool CBoardDefaultOper::onMoveEvent(QMouseEvent *event)
{
    return false;
}

bool CBoardDefaultOper::onReleaseEvent(QMouseEvent *event)
{
    return false;
}

bool CBoardDefaultOper::onKeyPressEvent(QKeyEvent *event)
{
    return false;
}

CBoardMoveSelectOper::CBoardMoveSelectOper(CBoardView *pView):CboardOper(pView)
{

}

CBoardMoveSelectOper::~CBoardMoveSelectOper()
{

}

bool CBoardMoveSelectOper::onPressEvent(QMouseEvent *event)
{
    m_items = m_plocView->scene()->selectedItems();
    m_scenePos = m_plocView->mapToScene(event->pos());
    return CboardOper::onPressEvent(event);
}

bool CBoardMoveSelectOper::onMoveEvent(QMouseEvent *event)
{
    QPointF pos = m_plocView->mapToScene(event->pos());
    qreal xIntervalue = pos.x() - m_scenePos.x();
    qreal yIntervalue = pos.y() - m_scenePos.y();
    m_scenePos = pos;

    foreach (auto item, m_items) {
        QPointF itemPos = item->pos();
        itemPos.setX(itemPos.x() + xIntervalue);
        itemPos.setY(itemPos.y() + yIntervalue);
        item->setPos(itemPos);
    }
    return CboardOper::onMoveEvent(event);
}

bool CBoardMoveSelectOper::onReleaseEvent(QMouseEvent *event)
{
    return CboardOper::onReleaseEvent(event);
}
