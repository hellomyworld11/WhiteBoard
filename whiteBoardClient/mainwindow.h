#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QTcpSocket>
#include <QMessageBox>
#include "util.h"
class CBoardView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void initUi();

    void initConnect();

    void setToolbar();

    void setScene();

    void sendData(QString str);

    void sendData(QByteArray data);
protected slots:
    //画直线
    void onClickedLineButton(bool bChecked);
    //画圆形
    void onClickedCirButton(bool bChecked);
    //画矩形
    void onClickedRecButton(bool bChecked);
    //画三角形
    void onClickedTrangButton(bool bChecked);
    //画自由线
    void onClickedPathButton(bool bChecked);
    //橡皮擦
    void onClickedEreaseButton(bool bChecked);
    //选择 TODO
    void onClickedSelectButton(bool bChecked);
    //宽度
    void onClicedWidthbtn(bool bChecked);
    //颜色
    void onClicedColorbtn(bool bChecked);
    //测试
    void onClicedTest(bool bChecked);

    void on_penwidth_value(int ival);

    void on_color_value(QColor color);
    //通信
    void on_readyread();

    void on_occurerror(QAbstractSocket::SocketError socketError);

public:
    bool bSend; //绘画模式，不绘制接收的数据 废弃 TODO DELETE
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    CBoardView  *view;
    QTcpSocket  *socket;  //和服务器通信
    int         curPenWidth = 10;
};
#endif // MAINWINDOW_H
