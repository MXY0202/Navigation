#ifndef NAVI_H
#define NAVI_H
#include <vector>
#include <string>
#include "point.h"
#include <QStack>
#include <QMap>
using namespace std;
#define MINTIME 0
#define MINDIS 1
#define WALK 0
#define BIKE 1
class Navi
{
public:
    vector<QString> wayPoint;//途径点的名称
    QMap<QString, int> buildingTable; //存储点名称与点的对应
    QStack<int> route; //存储最终路径
    Point* roadPoint; //存储图中所有的点
    int pointNum; //图中所有点的个数
    int secondBegin;//记录第二个校区点开始的地方
    bool travelWay; //出行方式
    bool travelStrategy; //出行策略
    int door1;
    int door2;
    int doors1[4];
    int doors2[2];


    Navi();
    ~Navi();
    void selectStrategy();//根据vector中的数量和是否再同一个校区的点判断执行怎样的策略
    int dijkstra(int start, int* end, int num, bool storeRoute); //执行dijkstra算法，将路径存在route栈中,storeRoute代表本次计算是否存入栈中
    int multiPoint(int** weight, int num, int *path, bool storeRoute);//途径多点计算,weight为权值数组，num为点个数，storeRoute代表本次计算是否存入栈中
    bool isSameCampus(int last, int current); //判断当前点和上一个点是否在同一个校区
    int getPointX(const int pointSeq);
    int getPointY(const int pointSeq);
    int getDir(const int first, const int second);
    int getDis(const int first, const int second);//得到两点之间距离
};
#endif // NAVI_H
