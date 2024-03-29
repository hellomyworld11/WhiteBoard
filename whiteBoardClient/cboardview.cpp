#include "cboardview.h"
#include <QDebug>
#include "util.h"
#include "mainwindow.h"
#include "cpathlineitem.h"
#include "clineitem.h"
#include "ccircleitem.h"
#include "crectitem.h"
#include "ctrangleitem.h"
#include "ceraseitem.h"

CBoardView::CBoardView(QWidget *parent):
    QGraphicsView(parent),m_pCurItem(nullptr)
    ,width(1),mainWin(nullptr)
{
   // this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setOper(new CBoardDefaultOper(this));
    color =  QColor(255,0,0);
}

void CBoardView::setMode(Mode mode)
{
    this->m_mode = mode;
}

CBoardView::Mode CBoardView::getMode()
{
    return this->m_mode;
}

void CBoardView::setItemType(ItemType type)
{
    this->m_itemType = type;
}

bool CBoardView::createItem(ItemType type,QPointF scenePos)
{
    this->m_itemType = type;

    switch (type) {
    case Line:
        m_pCurItem = new CLineItem;
        this->scene()->addItem(m_pCurItem);
        static_cast<CLineItem*>(m_pCurItem)->setWidth(width);
        static_cast<CLineItem*>(m_pCurItem)->setColor(color);
        static_cast<CLineItem*>(m_pCurItem)->update();
        static_cast<CLineItem*>(m_pCurItem)->SetFirstPt(scenePos);
        sendJson = static_cast<CLineItem*>(m_pCurItem)->getJson(true,false);
        break;
    case Circle:
        m_pCurItem = new CCircleItem;
        this->scene()->addItem(m_pCurItem);
        static_cast<CCircleItem*>(m_pCurItem)->setWidth(width);
        static_cast<CCircleItem*>(m_pCurItem)->setColor(color);
        static_cast<CCircleItem*>(m_pCurItem)->update();
         static_cast<CCircleItem*>(m_pCurItem)->setFirstPt(scenePos);
        sendJson = static_cast<CCircleItem*>(m_pCurItem)->getJson(true,false);
        break;
    case Rect:
        m_pCurItem = new CRectItem;
        this->scene()->addItem(m_pCurItem);
        static_cast<CRectItem*>(m_pCurItem)->SetFirstPt(scenePos);
        static_cast<CRectItem*>(m_pCurItem)->setWidth(width);
        static_cast<CRectItem*>(m_pCurItem)->setColor(color);
        static_cast<CRectItem*>(m_pCurItem)->update();
        sendJson = static_cast<CRectItem*>(m_pCurItem)->getJson(true,false);
        break;
    case Trangle:
        m_pCurItem = new CTrangleItem;
        this->scene()->addItem(m_pCurItem);
        static_cast<CTrangleItem*>(m_pCurItem)->SetFirstPt(scenePos);
        static_cast<CTrangleItem*>(m_pCurItem)->setWidth(width);
        static_cast<CTrangleItem*>(m_pCurItem)->setColor(color);
        static_cast<CTrangleItem*>(m_pCurItem)->update();
        sendJson = static_cast<CTrangleItem*>(m_pCurItem)->getJson(true,false);
        break;
    case Erase:
        m_pCurItem = new CEraseItem();
        if(!m_pCurItem) return false;
        this->scene()->addItem(m_pCurItem);
        static_cast<CEraseItem*>(m_pCurItem)->setStartPos(scenePos);
        static_cast<CEraseItem*>(m_pCurItem)->setWidth(width);
        static_cast<CEraseItem*>(m_pCurItem)->setColor(color);
        static_cast<CEraseItem*>(m_pCurItem)->update();
        sendJson = static_cast<CEraseItem*>(m_pCurItem)->getJson(true,false);
        break;
    default:
        break;
    }
    cleanSelectItems();
    m_pCurItem->setSelected(true);
    return true;
}

bool CBoardView::createPath(QPointF scenePos)
{
    m_pCurItem = new CPathLineItem();
    if(!m_pCurItem) return false;

    this->scene()->addItem(m_pCurItem);
    cleanSelectItems();
    m_pCurItem->setSelected(true);
    static_cast<CPathLineItem*>(m_pCurItem)->setStartPos(scenePos);
    static_cast<CPathLineItem*>(m_pCurItem)->setColor(color);
    static_cast<CPathLineItem*>(m_pCurItem)->setWidth(width);
    static_cast<CPathLineItem*>(m_pCurItem)->update();
    sendJson = static_cast<CPathLineItem*>(m_pCurItem)->getJson(true, false);
    return true;
}

bool CBoardView::endItem(ItemType type, QPointF scenePos)
{
    this->m_itemType = type;
    if(m_pCurItem == nullptr)
        return false;
    switch (type) {
    case Line:
        static_cast<CLineItem*>(m_pCurItem)->SetEndPt(scenePos);
        break;
    case Circle:
       static_cast<CCircleItem*>(m_pCurItem)->setEndPt(scenePos);
        break;
    case Rect:
        static_cast<CRectItem*>(m_pCurItem)->SetEndPt(scenePos);
        break;
    case Trangle:
        static_cast<CTrangleItem*>(m_pCurItem)->SetEndPt(scenePos);
        break;
    case Erase:
        static_cast<CEraseItem*>(m_pCurItem)->addPoint(scenePos);
        break;
    default:
        break;
    }
    return true;
}

bool CBoardView::moveItem(ItemType type, QPointF scenePos)
{
    this->m_itemType = type;
    if(m_pCurItem == nullptr)
        return false;
    switch (type) {
    case Line:
        static_cast<CLineItem*>(m_pCurItem)->SetEndPt(scenePos);
        break;
    case Circle:
       static_cast<CCircleItem*>(m_pCurItem)->setEndPt(scenePos);
        break;
    case Rect:
        static_cast<CRectItem*>(m_pCurItem)->SetEndPt(scenePos);
        break;
    case Trangle:
        static_cast<CTrangleItem*>(m_pCurItem)->SetEndPt(scenePos);
        break;
    case Erase:
        static_cast<CEraseItem*>(m_pCurItem)->addPoint(scenePos);
        break;
    default:
        break;
    }
    return true;
}

void CBoardView::setOper(CboardOper *pOper)
{
    this->m_pOper = pOper;
}

void CBoardView::exportAs(ExportType type)
{
    switch (type) {
    case Ex_Png:
        break;
    case Ex_PDF:
    default:
        break;
    }
}

void CBoardView::cleanSelectItems()
{
    auto itmes =  this->scene()->selectedItems();
    for(int i = 0;i < itmes.size();i++)
    {
        QGraphicsItem *pItem = itmes[i];
        pItem->setSelected(false);
    }
}

void CBoardView::setColor(QColor color)
{
    this->color = color;
}

void CBoardView::setWidth(int widht)
{
    this->width = widht;
}

void CBoardView::setMainWin(MainWindow *p)
{
    this->mainWin = p;
}

void CBoardView::sendData(QString str)
{
     QJsonDocument jsonDoc(sendJson);
     this->mainWin->sendData(jsonDoc.toJson());
}

void CBoardView::sendMode(bool open)
{
    this->mainWin->bSend = open;
}

void CBoardView::autodraw(Mode mode, ItemType itemType, QString firstPt, QString secondPt, bool bSt,bool bEnd)
{
    m_mode = mode;
    m_itemType = itemType;
    QStringList strlist1 = firstPt.split(QLatin1Char(','));
    QStringList strlist2 = secondPt.split(QLatin1Char(','));
    QPointF locFirst,locSecond;
    if(strlist1.size() == 2)
    {
        locFirst = QPointF(strlist1[0].toFloat()/*+10*/,strlist1[1].toFloat());
    }
    if(strlist2.size() == 2)
    {
        locSecond = QPointF(strlist2[0].toFloat()/*+10*/,strlist2[1].toFloat());
    }
    if(m_mode == InsertNone || (m_mode == InsertItem && m_itemType == None))
    {
       return ;
    }
    if(bSt)//开始状态
    {
        if(m_mode == InsertItem)
        {
            alog.LogS("createItem");
            createItem(m_itemType,locFirst);
        }else if(m_mode == InsertLine)
        {
            createPath(locFirst);
        }
    }else if(bEnd)//结束状态
    {
        if(m_mode == InsertItem)
        {
            alog.LogS("endItem");
            endItem(m_itemType,locSecond);
        }else if(m_mode == InsertLine)
        {
            //createPath(locFirst);
            static_cast<CPathLineItem*>(m_pCurItem)->endDrawPos();
        }
    }else{//持续状态
        if(m_mode == InsertItem)
        {
            alog.LogS("持续endItem");
            endItem(m_itemType,locSecond);
        }else if(m_mode == InsertLine)
        {
            //createPath(locFirst);
             static_cast<CPathLineItem*>(m_pCurItem)->addPoint(locSecond);
        }

    }
}

void CBoardView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mouse press";
    sendMode(true);
    //sendData("hello");
    if(m_mode == InsertNone || (m_mode == InsertItem && m_itemType == None))
    {
       return ;
    }
    if(m_mode == InsertItem)
    {
        QPointF scenePos = mapToScene(event->pos());
        createItem(m_itemType,scenePos);

    }else if(m_mode == InsertLine)
    {
        QPointF scenePos = mapToScene(event->pos());
        createPath(scenePos);
    }else if(m_mode == SelectItem)
    {
        bool ret = m_pOper->onPressEvent(event);
        if(!ret) return;
    }
    sendData("press 发送json");

    return QGraphicsView::mousePressEvent(event);
}

void CBoardView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouse release";
    sendMode(true);
    if(m_mode == InsertNone || (m_mode == InsertItem && m_itemType == None))
    {
       return ;
    }
    if(!is_ptr_vaild(m_pCurItem))
    {
       return;
    }
    if(m_mode == InsertItem)
    {
        if(m_itemType == Line)
        {
            QPointF scenePos = mapToScene(event->pos());
            static_cast<CLineItem*>(m_pCurItem)->SetEndPt(scenePos);
            sendJson = static_cast<CLineItem*>(m_pCurItem)->getJson(false,true);
        }else if(m_itemType == Circle){
            QPointF scenePos = mapToScene(event->pos());
            static_cast<CCircleItem*>(m_pCurItem)->setEndPt(scenePos);
            sendJson = static_cast<CCircleItem*>(m_pCurItem)->getJson(false,true);
        }else if(m_itemType == Rect)
        {
            QPointF scenePos = mapToScene(event->pos());
            static_cast<CRectItem*>(m_pCurItem)->SetEndPt(scenePos);
            sendJson = static_cast<CRectItem*>(m_pCurItem)->getJson(false,true);
        }else if(m_itemType == Trangle)
        {
            QPointF scenePos = mapToScene(event->pos());
            static_cast<CTrangleItem*>(m_pCurItem)->SetEndPt(scenePos);
            sendJson = static_cast<CTrangleItem*>(m_pCurItem)->getJson(false,true);

        }else if(m_itemType == Erase)
        {
            QPointF scenePos = mapToScene(event->pos());
            static_cast<CEraseItem*>(m_pCurItem)->addPoint(scenePos);
            sendJson = static_cast<CEraseItem*>(m_pCurItem)->getJson(false,true);
        }

    }else if(m_mode == InsertLine)
    {
        static_cast<CPathLineItem*>(m_pCurItem)->endDrawPos();
        sendJson = static_cast<CPathLineItem*>(m_pCurItem)->getJson(false, true);
    }else if(m_mode == SelectItem)
    {
        bool ret = m_pOper->onReleaseEvent(event);
        if(!ret) return;
    }
    sendData("release 发送json");

    return QGraphicsView::mouseReleaseEvent(event);
}

void CBoardView::mouseMoveEvent(QMouseEvent *event)
{
    sendMode(true);
    if(m_mode == InsertNone || (m_mode == InsertItem && m_itemType == None))
    {
       return ;
    }
    if(!is_ptr_vaild(m_pCurItem))
    {
       return;
    }
    if(event->buttons() & Qt::LeftButton)
    {    
        if(m_mode == InsertItem)
        {
            if(m_itemType == Line)
            { 
                QPointF scenePos = mapToScene(event->pos());
                static_cast<CLineItem*>(m_pCurItem)->SetEndPt(scenePos);
                sendJson = static_cast<CLineItem*>(m_pCurItem)->getJson();
            }else if(m_itemType == Circle){
                QPointF scenePos = mapToScene(event->pos());
                static_cast<CCircleItem*>(m_pCurItem)->setEndPt(scenePos);
                sendJson = static_cast<CCircleItem*>(m_pCurItem)->getJson();
            }else if(m_itemType == Rect)
            {
                QPointF scenePos = mapToScene(event->pos());
                static_cast<CRectItem*>(m_pCurItem)->SetEndPt(scenePos);
                sendJson = static_cast<CRectItem*>(m_pCurItem)->getJson();
            }else if(m_itemType == Trangle)
            {
                QPointF scenePos = mapToScene(event->pos());
                static_cast<CTrangleItem*>(m_pCurItem)->SetEndPt(scenePos);
                sendJson = static_cast<CTrangleItem*>(m_pCurItem)->getJson();
            }else if(m_itemType == Erase)
            {
                QPointF scenePos = mapToScene(event->pos());
                static_cast<CEraseItem*>(m_pCurItem)->addPoint(scenePos);
                sendJson = static_cast<CEraseItem*>(m_pCurItem)->getJson();
            }

        }else if(m_mode == InsertLine)
        {
            QPointF scenePos = mapToScene(event->pos());
            static_cast<CPathLineItem*>(m_pCurItem)->addPoint(scenePos);
            sendJson = static_cast<CPathLineItem*>(m_pCurItem)->getJson(false, false);
        }else if(m_mode == SelectItem)
        {
            bool ret = m_pOper->onMoveEvent(event);
            if(!ret) return;
        }
        sendData("发送json");

        return QGraphicsView::mouseMoveEvent(event);
    }
}
