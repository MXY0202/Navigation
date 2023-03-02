#ifndef POINT_H
#define POINT_H


#pragma once
typedef struct Seq* nextSeq;
struct Seq
{
    int seq;  //点的序号
    float congestion;//代表拥挤度
    bool isBike; //代表该条路是否能用自行车行走
    nextSeq next; //指向下一个点
};
class Point
{
public:
    int dis(const Point otherPoint);	//返回otherPoint与当前点的距离
    Point(int seq, int x, int y, nextSeq adjPoint);//带参构造函数
    Point(); //无参构造函数
    void Print();//打印当前点的信息
    nextSeq getNext();//得到当前点指向邻点指针

    int seq;  //序号
    int x;    //x坐标
    int y;    //y坐标
    nextSeq next; //指向邻点
};

#endif // POINT_H
