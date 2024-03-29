#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cboardview.h"
#include "penwidth.h"
#include "colorsel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      scene{nullptr},
      view(nullptr),
      socket(nullptr),
      bSend(false)
{
    //ui->setupUi(this);
    initUi();
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    setWindowTitle("电子白板v1.0");
    //设置大小
   // this->setWindowState(Qt::WindowMaximized);
   // int winWidth = 2048;  //1442  2048
   // int winHeight = 1050;   //710 1050
    //    setFixedSize(winWidth, winHeight);
    resize(800, 600);

    //v1.0 顶端显示各类图形符号
    setToolbar();

    //绘图框架
    setScene();
}

void MainWindow::initConnect()
{
    //连接服务器
    socket = new QTcpSocket(this);
    QHostAddress ip(serverIp);

   // connect(socket,&QTcpSocket::er);

    socket->connectToHost(ip,serverPort);

    connect(socket,&QTcpSocket::readyRead,
            this,&MainWindow::on_readyread);

    connect(socket,&QTcpSocket::errorOccurred,
            this,&MainWindow::on_occurerror);

}

void MainWindow::setToolbar()
{
    //添加工具栏
    //设置各类图标
    //QIcon iConCircle;
    //QIcon iConSquare;
    QToolBar* toolbar =  this->addToolBar("toolbar");
   //toolbar->setGeometry(0,0,this->width(),50);
    if(is_ptr_vaild(toolbar))
    {
        QAction *actionLine = new QAction(QIcon("://res/line.jpg"),"直线");
        QObject::connect(actionLine, &QAction::triggered, this, &MainWindow::onClickedLineButton);
        toolbar->addAction(actionLine);

        QAction *actionCir= new QAction(QIcon("://res/circle.jpg"),"圆形");
        QObject::connect(actionCir, &QAction::triggered, this, &MainWindow::onClickedCirButton);
        toolbar->addAction(actionCir);

        QAction *actionTrangle = new QAction(QIcon("://res/trangle.jpg"),"三角形");
        QObject::connect(actionTrangle, &QAction::triggered, this, &MainWindow::onClickedTrangButton);
        toolbar->addAction(actionTrangle);

        QAction *actionPath = new QAction(QIcon("://res/path.jpg"),"自由");
        QObject::connect(actionPath, &QAction::triggered, this, &MainWindow::onClickedPathButton);
        toolbar->addAction(actionPath);

        QAction *actionRec = new QAction(QIcon("://res/rec.jpg"),"矩形");
        QObject::connect(actionRec, &QAction::triggered, this, &MainWindow::onClickedRecButton);
        toolbar->addAction(actionRec);

        QAction *actionErase = new QAction(QIcon("://res/erase.jpg"),"橡皮擦");
        QObject::connect(actionErase, &QAction::triggered, this, &MainWindow::onClickedEreaseButton);
        toolbar->addAction(actionErase);

        QAction *actionSelect = new QAction(QIcon("://res/arrow.jpg"),"选择");
        QObject::connect(actionSelect, &QAction::triggered, this, &MainWindow::onClickedSelectButton);
        toolbar->addAction(actionSelect);


    }
   //添加大小和颜色设置
    QPushButton* penWbtn = new QPushButton();
    penWbtn->setText("画笔大小");
    toolbar->addSeparator();
    toolbar->addWidget(penWbtn);

    QPushButton* penColor = new QPushButton();
    penColor->setText("颜色");
    toolbar->addSeparator();
    toolbar->addWidget(penColor);

    //测试
    QPushButton* btnTest = new QPushButton();
    btnTest->setText("测试");
    toolbar->addSeparator();
    toolbar->addWidget(btnTest);

    connect(penWbtn,&QPushButton::clicked,
            this,&MainWindow::onClicedWidthbtn);
    connect(penColor,&QPushButton::clicked,
            this,&MainWindow::onClicedColorbtn);

    connect(btnTest,&QPushButton::clicked,
            this,&MainWindow::onClicedTest);
}
#include <QGraphicsEllipseItem>
void MainWindow::setScene()
{
    scene = new QGraphicsScene(this);
   // scene->addLine(-500,-100,100,100);
   // scene->addText("hello");
    qDebug() << "widht " << size().width() << "hight " << size().height();
    scene->setSceneRect(0,30,size().width(),size().height());
    //CTrangleItem *pTest  = new CTrangleItem;
   // scene->addItem(pTest);
   // QGraphicsLineItem *aLine = new QGraphicsLineItem(1,100,100,100);
   // scene->addItem(aLine);
    //QGraphicsEllipseItem *aEllipse = new QGraphicsEllipseItem;
    //aEllipse->setRect(30,30,20,20);
   // scene->addItem(aEllipse);
    view = new CBoardView(this);
    view->setScene(scene);
    view->setMainWin(this);

    //this->setCentralWidget(view);
    view->setGeometry(0,30,size().width(),size().height());
}

void MainWindow::onClickedLineButton(bool bChecked)
{
    qDebug() << "line click";
    view->setMode(CBoardView::InsertItem);
    view->setItemType(CBoardView::Line);
}

void MainWindow::onClickedCirButton(bool bChecked)
{
    qDebug() << "Circle click";
    view->setMode(CBoardView::InsertItem);
    view->setItemType(CBoardView::Circle);
}

void MainWindow::onClickedRecButton(bool bChecked)
{
    qDebug() << "Rec click";
    view->setMode(CBoardView::InsertItem);
    view->setItemType(CBoardView::Rect);
}

void MainWindow::onClickedTrangButton(bool bChecked)
{
    qDebug() << "Trangle click";
    view->setMode(CBoardView::InsertItem);
    view->setItemType(CBoardView::Trangle);
}

void MainWindow::onClickedPathButton(bool bChecked)
{
    qDebug() << "Path click";
    view->setMode(CBoardView::InsertLine);
}

void MainWindow::onClickedEreaseButton(bool bChecked)
{
     qDebug() << "erase click";
     view->setMode(CBoardView::InsertItem);
     view->setItemType(CBoardView::Erase);
}

void MainWindow::onClickedSelectButton(bool bChecked)
{
    qDebug() << "erase click";
    view->setMode(CBoardView::SelectItem);
    //view->setItemType(CBoardView::Erase);
}

void MainWindow::onClicedWidthbtn(bool bChecked)
{
    //弹出宽度窗口
    PenWidth penWin(curPenWidth);
    connect(&penWin,&PenWidth::setval,
            this,&MainWindow::on_penwidth_value);
    penWin.exec();  
}

void MainWindow::onClicedColorbtn(bool bChecked)
{
    colorSel color;
    connect(&color,&colorSel::setval,
            this,&MainWindow::on_color_value);
    color.exec();
}

void MainWindow::onClicedTest(bool bChecked)
{
    //测试OK
    QString pt1 = QString("100,100");
    QString pt2 = QString("200,200");

    if(view != nullptr)
    {
        view->autodraw(CBoardView::InsertItem,
                       CBoardView::Circle,
                       pt1,pt2,true,false);
        view->autodraw(CBoardView::InsertItem,
                       CBoardView::Circle,
                       pt1,pt2,false,true);
    }
}

void MainWindow::on_penwidth_value(int ival)
{
    qDebug() << ival ;
    if(view != NULL)
    {
        curPenWidth = ival;
        view->setWidth(ival);
    }
}

void MainWindow::on_color_value(QColor color)
{
    qDebug() << color.name();
    if(view != NULL)
    {
        view->setColor(color);
    }
}

void MainWindow::on_readyread()
{
    //获取服务器下发的数据
    //qDebug() << "read";
 //   if(bSend)
 //   {
  //      bSend = false;
  //      return;
 //   }

    QByteArray bytes = socket->readAll();
    alog.LogS(QString(bytes));  //test OK
    //解析
    QJsonDocument jsondoc = QJsonDocument::fromJson(bytes);
    if(jsondoc.isObject())
    {
        QJsonObject jsonobj = jsondoc.object();
        int modeval = jsondoc["Mode"].toInt();
        int itemval = jsondoc["ItemType"].toInt();
        QString firstpt = jsondoc["firstPnt"].toString();
        QString addpt = jsondoc["secondPnt"].toString();
        //注意这里先用toBOOL() 不要用toInt() 不然true和false都会被转成0
        int bSt = jsondoc["bStart"].toBool();
        int bEnd = jsondoc["bEnd"].toBool();
        QString testPara = QString("%1|%2|%3|%4|%5|%6")
                .arg(modeval).arg(itemval).arg(firstpt)
                .arg(addpt).arg(bSt).arg(bEnd);
        alog.LogS(testPara);  //test OK
        if(view != nullptr)
        {
            view->autodraw((CBoardView::Mode)modeval,(CBoardView::ItemType)itemval,firstpt,addpt,bSt,bEnd);
        }
    }
}

void MainWindow::on_occurerror(QAbstractSocket::SocketError socketError)
{
    QString err = socket->errorString();
    QMessageBox::warning(nullptr,"警告",err);
}

void MainWindow::sendData(QString str)
{
    if(socket == nullptr) return;
    QByteArray writedata = str.toUtf8();
    socket->write(writedata);
}

void MainWindow::sendData(QByteArray data)
{
    if(socket == nullptr) return;
    socket->write(data);
}

