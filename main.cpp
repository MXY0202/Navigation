#include "mainwindow.h"
#include <QFile>
#include "QTextStream"
#include <QApplication>
#include "navi.h"
#include "global.h"
#include "log.h"
#include <QDebug>

Point* initialMap(int& pointNum, int& secondBegin);//将地图读入navi中的roadPoint邻接表
void initBuildingList();
int main(int argc, char *argv[])
{
    navi.roadPoint = initialMap(navi.pointNum, navi.secondBegin);

    initBuildingList();
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("校园导航系统");
    w.show();
    return a.exec();
}

Point* initialMap(int& pointNum, int& secondBegin)
{
    int seq, x, y, num;
    QFile in(":/text/map.txt");
    if(!in.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream fstrm(&in);
    fstrm >> pointNum >> secondBegin;
    Point* roadPoint = new Point[pointNum];
    for (int i = 0; i < pointNum; i++)
    {
        fstrm >> seq >> x >> y >> num; //分别为当前点序号，坐标，邻点个数
        nextSeq adjPoint = new struct Seq;
        nextSeq currency = adjPoint;
        for (int j = 1; j <= num; j++)
        {

            int point;//邻点序号
            float congenstion;//拥挤度
            int isBike; //自行车是否能通过
            currency->next = new struct Seq;
            currency = currency->next;
            fstrm >> point >> congenstion >> isBike;
            currency->seq = point;
            currency->congestion = congenstion;
            currency->isBike = isBike;
        }
        currency->next = NULL;
        roadPoint[i] = Point(i, x, y, adjPoint);
    }
    in.close();
    return roadPoint;
}
void initBuildingList()
{
    QFile in(":/text/building.txt");
    if(!in.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream fstrm(&in);
    while (fstrm.atEnd() == 0)
    {
        QString building;
        fstrm >> building;
        //qDebug() << building;
        buildingList << building;
    }
    return;
}
