#include "log.h"

Log alog;


Log::Log(QString name):QFile(name),name_(name)
{
    this->Clear();
    this->open(QIODevice::WriteOnly | QIODevice::Append);
}

Log::~Log()
{
    this->close();
}

void Log::Clear()
{
   // this->open(Truncate);
}

void Log::LogS(QString str)
{
    QTextStream text_stream(this);
    QString current_date_time = QDateTime::currentDateTime().
            toString("yyyy-MM-dd hh:mm:ss ddd");
    //QString current_date = QString("(%1)").arg(current_date_time);
    text_stream <<  current_date_time << str << "\r\n";
    this->flush();
}


