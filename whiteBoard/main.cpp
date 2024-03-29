#include "mainwindow.h"
#include "cmainserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    CMainServer mainServer;
    QHostAddress address("192.168.0.103");
    mainServer.listen(address,10086);
    return a.exec();
}
