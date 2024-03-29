#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QApplication>


const qint64 pid = QApplication::applicationPid();
const QString strLogName = QString("logClient_%1.txt").arg(pid) ;


//日志类
class Log : public QFile
{
public:
    Log(QString name = strLogName);
    ~Log();
public:
    void Clear();
    void LogS(QString str);
private:
    QString name_;
};

extern Log alog;

#endif // LOG_H
