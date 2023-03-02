#include "log.h"
#include "QFile"
#include <QTextStream>
#include <QDateTime>
Log::Log()
{

}

void Log::print(QString temp)
{
    //主要功能有查询建筑物用名称
    //范围
    //导航，分多点单点
    //图书馆
    //食堂
    //新生导航
    QString log = "";
    QFile out("D:/Navigation/Navigation/log.txt");
    if(!out.exists())
        exit(-1);
    if(!out.open(QIODevice::WriteOnly | QIODevice::Append))
        exit(-1);
    QTextStream fstrm(&out);
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString time = curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    log += time + "      " + temp;
    fstrm << log;
    out.close();
}
