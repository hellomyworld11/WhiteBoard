#ifndef CBOARDOPER_H
#define CBOARDOPER_H
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>

class CBoardView;


//白板操作类， 针对图元的选择，移动，删除
class CboardOper
{
public:
    CboardOper(CBoardView *pView = nullptr);
    virtual ~CboardOper();

    virtual bool onPressEvent(QMouseEvent *event);
    virtual bool onMoveEvent(QMouseEvent *event);
    virtual bool onReleaseEvent(QMouseEvent *event);
    virtual bool onKeyPressEvent(QKeyEvent *event);
protected:
    CBoardView* m_plocView = nullptr;
};

//default oper
class CBoardDefaultOper : public CboardOper{
public:
    CBoardDefaultOper(CBoardView *pView = nullptr);
    ~CBoardDefaultOper();
    bool onPressEvent(QMouseEvent *event);  //用来分发 按下事件。 比如是选择就分配给对应的选择事件处理
    bool onMoveEvent(QMouseEvent *event);
    bool onReleaseEvent(QMouseEvent *event);
    bool onKeyPressEvent(QKeyEvent *event);
};

class CBoardMoveSelectOper:public CboardOper{
public:
   CBoardMoveSelectOper(CBoardView *pView = nullptr);
   ~CBoardMoveSelectOper();
   bool onPressEvent(QMouseEvent *event);
   bool onMoveEvent(QMouseEvent *event);
   bool onReleaseEvent(QMouseEvent *event);
private:
    QPointF m_scenePos;
    QList<QGraphicsItem *> m_items;
};






#endif // CBOARDOPER_H
