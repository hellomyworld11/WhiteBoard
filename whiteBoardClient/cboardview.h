#ifndef CBOARDVIEW_H
#define CBOARDVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QVector>
#include <QPainterPath>
#include <QJsonObject>
#include "cboardoper.h"

class MainWindow;

//主视图类，承载画图和显示
class CBoardView : public QGraphicsView
{
public:
    enum Mode {InsertNone, InsertItem, InsertLine, InsertText,SelectItem ,MoveItem };
    enum ItemType{None,Line,Circle,Rect,Trangle,Erase};
    enum ExportType{Ex_Png,Ex_PDF};

    CBoardView(QWidget *parent = nullptr);

    void setMode(Mode mode);

    Mode getMode();

    void setItemType(ItemType type);

    bool createItem(ItemType type, QPointF scenePos);

    bool createPath( QPointF scenePos);

    bool endItem(ItemType type,QPointF scenePos);

    bool moveItem(ItemType type,QPointF scenePos);

    void setOper(CboardOper *pOper);

    void exportAs(ExportType type);

    void cleanSelectItems();

    void setColor(QColor color);

    void setWidth(int widht);

    void setMainWin(MainWindow *p);

    void sendData(QString str);

    void sendMode(bool open = true);

    void autodraw(Mode mode,ItemType itemType,QString firstPt,QString secondPt,bool bSt,bool bEnd);
protected:
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);
signals:
    void itemSelectedChanged(void);
private:
    MainWindow      *mainWin;
    CboardOper      *m_pOper;
    QGraphicsItem   *m_pCurItem;
    Mode            m_mode;
    ItemType        m_itemType;
    int             width;
    QColor          color;
    QJsonObject     sendJson;
};

#endif // CBOARDVIEW_H
