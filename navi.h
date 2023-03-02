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
    vector<QString> wayPoint;//;���������
    QMap<QString, int> buildingTable; //�洢���������Ķ�Ӧ
    QStack<int> route; //�洢����·��
    Point* roadPoint; //�洢ͼ�����еĵ�
    int pointNum; //ͼ�����е�ĸ���
    int secondBegin;//��¼�ڶ���У���㿪ʼ�ĵط�
    bool travelWay; //���з�ʽ
    bool travelStrategy; //���в���
    int door1;
    int door2;
    int doors1[4];
    int doors2[2];


    Navi();
    ~Navi();
    void selectStrategy();//����vector�е��������Ƿ���ͬһ��У���ĵ��ж�ִ�������Ĳ���
    int dijkstra(int start, int* end, int num, bool storeRoute); //ִ��dijkstra�㷨����·������routeջ��,storeRoute�����μ����Ƿ����ջ��
    int multiPoint(int** weight, int num, int *path, bool storeRoute);//;��������,weightΪȨֵ���飬numΪ�������storeRoute�����μ����Ƿ����ջ��
    bool isSameCampus(int last, int current); //�жϵ�ǰ�����һ�����Ƿ���ͬһ��У��
    int getPointX(const int pointSeq);
    int getPointY(const int pointSeq);
    int getDir(const int first, const int second);
    int getDis(const int first, const int second);//�õ�����֮�����
};
#endif // NAVI_H
