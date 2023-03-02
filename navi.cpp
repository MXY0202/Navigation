#include "navi.h"
#include <QFile>
#include <QTextStream>
#include <fstream>
#include "point.h"
#include <iostream>
const int N = 20, M = 1 << N;
int dp[M][N];
using namespace std;
Navi::Navi()
{
//    //读取点与名称的对应
    QFile in(":/text/buildingTable.txt");
    if(!in.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream fstrm(&in);
    fstrm.setCodec("UTF-8");
    int num;
    fstrm >> num;
    for (int i = 0; i < num; i++)
    {
        QString building;
        int seq;
        fstrm >> building >> seq;
        buildingTable[building] = seq;
    }
    in.close();
    door1 = 4;
    door2 = 2;
    doors1[0] = 1;
    doors1[1] = 57;
    doors1[2] = 11;
    doors1[3] = 70;
    doors2[0] = 75;
    doors2[1] = 83;

    travelStrategy = MINTIME;//初始化出行策略为最短时间
    travelWay = WALK;//初始化出行方式为步行

}

Navi::~Navi()
{
        delete [] roadPoint;
}

void Navi::selectStrategy()
{
    //只有两个点
    if (2 == wayPoint.size())
    {
        QString startName = wayPoint[0];
        QString endName = wayPoint[1];
        int startPoint = buildingTable[startName];
        int endPoint = buildingTable[endName];
        //如果当前两点在同一个校区,直接执行,并且直接将路线存入route栈中
        if (true == isSameCampus(startPoint, endPoint))
        {
            int *end = new int[1];
            end[0] = endPoint;
            dijkstra(startPoint, end, 1, true);
        }
        else//不在同一个校区，找到各自点离校门最近的路径
        {
            if (startPoint < secondBegin)//如果在校区一
            {
                int minDis = INT_MAX;
                int minDoor;
                int *endPoint2 = new int[1];
                endPoint2[0] = endPoint;
                for (int i = 0; i < door2; i++)//先算校区2的门到终点的最小距离
                {
                    int dis = dijkstra(doors2[i], endPoint2, 1, false);
                    if (minDis > dis)
                    {
                        minDis = dis;
                        minDoor = i;
                    }
                }
                dijkstra(doors2[minDoor], endPoint2, 1, true);//将门到终点最短路径入栈

                int *end = new int[door1];
                for (int i = 0; i < door1; i++)
                    end[i] = doors1[i];
                dijkstra(startPoint, end, door1, false);//将start到各门的距离都计算出来,存回end数组
                minDis = INT_MAX;
                int *door = new int[1];
                for (int i = 0; i < door1; i++)
                {
                    if (end[i] < minDis)
                    {
                        minDis = end[i];
                        door[0] = doors1[i];//将距离最小的赋值geidoor
                    }
                }
                dijkstra(startPoint, door, 1, true);//将start到门的最短路径入栈
            }
            else
            {
                int minDis = INT_MAX;
                int minDoor;
                int *endPoint1 = new int[1];
                endPoint1[0] = endPoint;
                for (int i = 0; i < door1; i++)//先算校区1的门到终点的最小距离
                {
                    int dis = dijkstra(doors1[i], endPoint1, 1, false);
                    if (minDis > dis)
                    {
                        minDis = dis;
                        minDoor = i;
                    }
                }
                dijkstra(doors1[minDoor], endPoint1, 1, true);//将门到终点最短路径入栈

                int *end = new int[door2];
                for (int i = 0; i < door2; i++)
                    end[i] = doors2[i];
                dijkstra(startPoint, end, door2, false);//将start到各门的距离都计算出来,存回end数组
                minDis = INT_MAX;
                int *door = new int[1];
                for (int i = 0; i < door2; i++)
                {
                    if (end[i] < minDis)
                    {
                        minDis = end[i];
                        door[0] = doors2[i];//将距离最小的赋值给door
                    }
                }
                dijkstra(startPoint, door, 1, true);//将start到门的最短路径入栈
            }
        }
    }
    else//途径多点
    {
        int multiNum = wayPoint.size();
        int* path = new int[multiNum]; //存储路径
        vector<pair<int, int>> correspondence;
        int *end = new int[multiNum];
        int *tmp = new int[multiNum];
        for (int i = 0; i < multiNum; i++)
        {
            pair<int, int> temp;
            temp.first = i; //为计算途径多点需要用到的
            temp.second = buildingTable[wayPoint[i]];//在原地图中的对应点
            end[i] = temp.second;
            tmp[i] = temp.second;
            cout << temp.second << " ";
            correspondence.push_back(temp);
        }
        cout << endl;
        int **weight = new int *[multiNum];
        for (int i = 0; i < multiNum; i++)
            weight[i] = new int[multiNum];
        for (int i = 0; i < multiNum; i++)
        {
            int start = buildingTable[wayPoint[i]];
            dijkstra(start, end, multiNum, false);//计算该点到所有点的最短距离
            for (int j = 0; j < multiNum; j++)
            {
                weight[i][j] = end[j];//将最短距离赋值给weight
                end[j] = tmp[j];
            }
        }
        //计算途径多点最短路径
        multiPoint(weight, multiNum, path, true);
        //释放weight和path和end内存

        //将点根据对应关系改为原地图中的点
        for (int i = 0; i < multiNum; i++)
        {
            int j = path[i];
            path[i] = correspondence[j].second;
        }
        for (int i = 1; i < multiNum; i++)
        {
            int *end = new int[1];
            end[0] = path[i - 1];
            dijkstra(path[i], end, 1, true);
            route.pop();
        }
        route.push(path[multiNum - 1]);
    }
}
int Navi::dijkstra(int start, int* end, int num, bool storeRoute)
{
    double* dist = new double[pointNum]; //dist是存start到各点最短距离
    bool* s = new bool[pointNum];  //s存储各点是否被访问过
    int* path = new int[pointNum]; //path存储最短路径时某一点前的一点
    //初始化各数组
    for (int i = 0; i < pointNum; i++)
    {
        dist[i] = INT_MAX;
        s[i] = false;
        path[i] = -1;
    }
    //初始化start到邻点距离
    dist[start] = 0;
    s[start] = true;
    nextSeq currency = roadPoint[start].getNext();
    while (currency->next != NULL)
    {
        currency = currency->next;
        int adjoin = currency->seq;//当前访问的邻点
        double dis;
        if (MINDIS == travelStrategy)
            dis = roadPoint[start].dis(roadPoint[adjoin]);
        else
            dis = roadPoint[start].dis(roadPoint[adjoin]) * currency->congestion; //出行策略为最短时间，距离就要乘上拥挤度
        //出行方式为步行，或者为自行车且当前道路满足自行车，才算邻点
        if (WALK == travelWay || (BIKE == travelWay && true == currency->isBike))
        {
            dist[adjoin] = dis;
            path[adjoin] = start;
        }
    }
    //Dijkstra主要算法
    for (int i = 0; i < pointNum; i++)
    {
        float min = INT_MAX;
        int k = -1;
        //找到未访问点中距离最短的点
        for (int j = 0; j < pointNum; j++)
        {
            if (!s[j] && dist[j] < min)
            {
                k = j;
                min = dist[j];
            }
        }
        if (-1 == k)//没有满足条件的点
            continue;
        s[k] = true;//记为已访问
        // 更新该点邻近点（未被访问的）最短距离
        nextSeq currency = roadPoint[k].getNext();
        int adjoin;
        while (currency->next != NULL)
        {
            currency = currency->next;
            adjoin = currency->seq;
            double dis;
            if (MINDIS == travelStrategy)
                dis = roadPoint[k].dis(roadPoint[adjoin]);
            else
                dis = roadPoint[k].dis(roadPoint[adjoin]) * currency->congestion; //出行策略为最短时间，距离就要乘上拥挤度
            //出行方式为步行，或者为自行车且当前道路满足自行车，才算邻点
            if (WALK == travelWay || (BIKE == travelWay && true == currency->isBike))
            {
                if (!s[adjoin] && dis + min < dist[adjoin])
                {
                    dist[adjoin] = dis + min;
                    path[adjoin] = k;
                }
            }
        }
    }
    if (1 != num)//需要计算start到多点的距离,一定不需要存储
    {
        for (int i = 0; i < num; i++)
        {
            int j = end[i];
            end[i] = dist[j];
        }
        return 0;
    }
    //只需计算两点之间
    int endPoint = end[0];
    //如果不需要存储路径,直接返回距离
    if (false == storeRoute)
        return dist[endPoint];
    //需要存储路径
    int i = endPoint;
    while (i != start)
    {
        route.push(i);
        i = path[i];
    }
    route.push(i);
    return dist[endPoint];
}

//途径多点计算,weight为权值数组，num为点个数，storeRoute代表本次计算是否存入栈中
int Navi::multiPoint(int** weight, int num, int *path, bool storeRoute)
{
    //创建状态数组
    //dp[i][j]为从0走到j，且路径为i的最短距离
//    int **dp = new int *[1 << num];
//    for (int i = 0; i < 1 << num; i++)
//        dp[i] = new int[num];
    int **state = new int *[1 << num];
    for (int i = 0; i < 1 << num; i++)
        state[i] = new int[num];
    //初始化dp数组
//    for (int i = 0; i < 1 << num; i++)
//        for (int j = 0; j < num; j++)
//        {
//            state[i][j] = 0;
//            dp[i][j] = 0x3f;
//        }
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 0; i < 1 << num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            // 保证i路径包含j这个点
            if (i >> j & 1)
            {
                //从k转移到j
                for (int k = 0; k < num; k++)
                {
                    //i路径去掉j时一定要包括k
                    if ((i - (1 << j)) >> k & 1)
                    {
                        //如果当前的距离大于上一个点为k当前点为j时的距离
                        if (dp[i][j] > dp[i - (1 << j)][k] + weight[k][j])
                        {
                            //cout << i << " " << j << " " << k << endl;
                            state[i][j] = k;//保存最短路径中此点的上一个点
                            dp[i][j] = dp[i - (1 << j)][k] + weight[k][j];
                        }
                    }
                }
            }
        }
    }
    //如果不需要存储路径，直接返回最短距离
    if (false == storeRoute)
        return dp[(1 << num) - 1][num - 1];
    //需要存储路径，将路径存储在route栈中
    int i = (1 << num) - 1, j = num - 1;
    path[0] = j;
    //cout << path[0] << endl;
    for (int k = 1; k < num; k++)
    {
        int previous;
        previous = state[i][j];
        path[k] = previous;
        i = i - (1 << j);
        j = previous;
    }
    return dp[(1 << num) - 1][num - 1];
}

bool Navi::isSameCampus(int last, int current)
{
    //如果在同一校区，返回true
    if((last < secondBegin && current < secondBegin) || (last >= secondBegin && current >= secondBegin))
        return true;
    else
        return false;
}

int Navi::getPointX(const int pointSeq)
{
    return roadPoint[pointSeq].x;
}

int Navi::getPointY(const int pointSeq)
{
    return roadPoint[pointSeq].y;
}

int Navi::getDir(const int first, const int second)
{
    int x1 = roadPoint[first].x;
    int y1 = roadPoint[first].y;
    int x2 = roadPoint[second].x;
    int y2 = roadPoint[second].y;
    if (x1 ==  x2)
    {
        //first在second的下边
        if (y1 > y2)
            return 1;
        else
            return 2;
    }
    else
    {
        //first在second的右边
        if (x1 > x2)
            return 3;
        else
            return 4;
    }
}

int Navi::getDis(const int first, const int second)
{
    int dis = roadPoint[first].dis(roadPoint[second]);
    return dis;
}
