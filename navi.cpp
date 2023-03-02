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
//    //��ȡ�������ƵĶ�Ӧ
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

    travelStrategy = MINTIME;//��ʼ�����в���Ϊ���ʱ��
    travelWay = WALK;//��ʼ�����з�ʽΪ����

}

Navi::~Navi()
{
        delete [] roadPoint;
}

void Navi::selectStrategy()
{
    //ֻ��������
    if (2 == wayPoint.size())
    {
        QString startName = wayPoint[0];
        QString endName = wayPoint[1];
        int startPoint = buildingTable[startName];
        int endPoint = buildingTable[endName];
        //�����ǰ������ͬһ��У��,ֱ��ִ��,����ֱ�ӽ�·�ߴ���routeջ��
        if (true == isSameCampus(startPoint, endPoint))
        {
            int *end = new int[1];
            end[0] = endPoint;
            dijkstra(startPoint, end, 1, true);
        }
        else//����ͬһ��У�����ҵ����Ե���У�������·��
        {
            if (startPoint < secondBegin)//�����У��һ
            {
                int minDis = INT_MAX;
                int minDoor;
                int *endPoint2 = new int[1];
                endPoint2[0] = endPoint;
                for (int i = 0; i < door2; i++)//����У��2���ŵ��յ����С����
                {
                    int dis = dijkstra(doors2[i], endPoint2, 1, false);
                    if (minDis > dis)
                    {
                        minDis = dis;
                        minDoor = i;
                    }
                }
                dijkstra(doors2[minDoor], endPoint2, 1, true);//���ŵ��յ����·����ջ

                int *end = new int[door1];
                for (int i = 0; i < door1; i++)
                    end[i] = doors1[i];
                dijkstra(startPoint, end, door1, false);//��start�����ŵľ��붼�������,���end����
                minDis = INT_MAX;
                int *door = new int[1];
                for (int i = 0; i < door1; i++)
                {
                    if (end[i] < minDis)
                    {
                        minDis = end[i];
                        door[0] = doors1[i];//��������С�ĸ�ֵgeidoor
                    }
                }
                dijkstra(startPoint, door, 1, true);//��start���ŵ����·����ջ
            }
            else
            {
                int minDis = INT_MAX;
                int minDoor;
                int *endPoint1 = new int[1];
                endPoint1[0] = endPoint;
                for (int i = 0; i < door1; i++)//����У��1���ŵ��յ����С����
                {
                    int dis = dijkstra(doors1[i], endPoint1, 1, false);
                    if (minDis > dis)
                    {
                        minDis = dis;
                        minDoor = i;
                    }
                }
                dijkstra(doors1[minDoor], endPoint1, 1, true);//���ŵ��յ����·����ջ

                int *end = new int[door2];
                for (int i = 0; i < door2; i++)
                    end[i] = doors2[i];
                dijkstra(startPoint, end, door2, false);//��start�����ŵľ��붼�������,���end����
                minDis = INT_MAX;
                int *door = new int[1];
                for (int i = 0; i < door2; i++)
                {
                    if (end[i] < minDis)
                    {
                        minDis = end[i];
                        door[0] = doors2[i];//��������С�ĸ�ֵ��door
                    }
                }
                dijkstra(startPoint, door, 1, true);//��start���ŵ����·����ջ
            }
        }
    }
    else//;�����
    {
        int multiNum = wayPoint.size();
        int* path = new int[multiNum]; //�洢·��
        vector<pair<int, int>> correspondence;
        int *end = new int[multiNum];
        int *tmp = new int[multiNum];
        for (int i = 0; i < multiNum; i++)
        {
            pair<int, int> temp;
            temp.first = i; //Ϊ����;�������Ҫ�õ���
            temp.second = buildingTable[wayPoint[i]];//��ԭ��ͼ�еĶ�Ӧ��
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
            dijkstra(start, end, multiNum, false);//����õ㵽���е����̾���
            for (int j = 0; j < multiNum; j++)
            {
                weight[i][j] = end[j];//����̾��븳ֵ��weight
                end[j] = tmp[j];
            }
        }
        //����;��������·��
        multiPoint(weight, multiNum, path, true);
        //�ͷ�weight��path��end�ڴ�

        //������ݶ�Ӧ��ϵ��Ϊԭ��ͼ�еĵ�
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
    double* dist = new double[pointNum]; //dist�Ǵ�start��������̾���
    bool* s = new bool[pointNum];  //s�洢�����Ƿ񱻷��ʹ�
    int* path = new int[pointNum]; //path�洢���·��ʱĳһ��ǰ��һ��
    //��ʼ��������
    for (int i = 0; i < pointNum; i++)
    {
        dist[i] = INT_MAX;
        s[i] = false;
        path[i] = -1;
    }
    //��ʼ��start���ڵ����
    dist[start] = 0;
    s[start] = true;
    nextSeq currency = roadPoint[start].getNext();
    while (currency->next != NULL)
    {
        currency = currency->next;
        int adjoin = currency->seq;//��ǰ���ʵ��ڵ�
        double dis;
        if (MINDIS == travelStrategy)
            dis = roadPoint[start].dis(roadPoint[adjoin]);
        else
            dis = roadPoint[start].dis(roadPoint[adjoin]) * currency->congestion; //���в���Ϊ���ʱ�䣬�����Ҫ����ӵ����
        //���з�ʽΪ���У�����Ϊ���г��ҵ�ǰ��·�������г��������ڵ�
        if (WALK == travelWay || (BIKE == travelWay && true == currency->isBike))
        {
            dist[adjoin] = dis;
            path[adjoin] = start;
        }
    }
    //Dijkstra��Ҫ�㷨
    for (int i = 0; i < pointNum; i++)
    {
        float min = INT_MAX;
        int k = -1;
        //�ҵ�δ���ʵ��о�����̵ĵ�
        for (int j = 0; j < pointNum; j++)
        {
            if (!s[j] && dist[j] < min)
            {
                k = j;
                min = dist[j];
            }
        }
        if (-1 == k)//û�����������ĵ�
            continue;
        s[k] = true;//��Ϊ�ѷ���
        // ���¸õ��ڽ��㣨δ�����ʵģ���̾���
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
                dis = roadPoint[k].dis(roadPoint[adjoin]) * currency->congestion; //���в���Ϊ���ʱ�䣬�����Ҫ����ӵ����
            //���з�ʽΪ���У�����Ϊ���г��ҵ�ǰ��·�������г��������ڵ�
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
    if (1 != num)//��Ҫ����start�����ľ���,һ������Ҫ�洢
    {
        for (int i = 0; i < num; i++)
        {
            int j = end[i];
            end[i] = dist[j];
        }
        return 0;
    }
    //ֻ���������֮��
    int endPoint = end[0];
    //�������Ҫ�洢·��,ֱ�ӷ��ؾ���
    if (false == storeRoute)
        return dist[endPoint];
    //��Ҫ�洢·��
    int i = endPoint;
    while (i != start)
    {
        route.push(i);
        i = path[i];
    }
    route.push(i);
    return dist[endPoint];
}

//;��������,weightΪȨֵ���飬numΪ�������storeRoute�����μ����Ƿ����ջ��
int Navi::multiPoint(int** weight, int num, int *path, bool storeRoute)
{
    //����״̬����
    //dp[i][j]Ϊ��0�ߵ�j����·��Ϊi����̾���
//    int **dp = new int *[1 << num];
//    for (int i = 0; i < 1 << num; i++)
//        dp[i] = new int[num];
    int **state = new int *[1 << num];
    for (int i = 0; i < 1 << num; i++)
        state[i] = new int[num];
    //��ʼ��dp����
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
            // ��֤i·������j�����
            if (i >> j & 1)
            {
                //��kת�Ƶ�j
                for (int k = 0; k < num; k++)
                {
                    //i·��ȥ��jʱһ��Ҫ����k
                    if ((i - (1 << j)) >> k & 1)
                    {
                        //�����ǰ�ľ��������һ����Ϊk��ǰ��Ϊjʱ�ľ���
                        if (dp[i][j] > dp[i - (1 << j)][k] + weight[k][j])
                        {
                            //cout << i << " " << j << " " << k << endl;
                            state[i][j] = k;//�������·���д˵����һ����
                            dp[i][j] = dp[i - (1 << j)][k] + weight[k][j];
                        }
                    }
                }
            }
        }
    }
    //�������Ҫ�洢·����ֱ�ӷ�����̾���
    if (false == storeRoute)
        return dp[(1 << num) - 1][num - 1];
    //��Ҫ�洢·������·���洢��routeջ��
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
    //�����ͬһУ��������true
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
        //first��second���±�
        if (y1 > y2)
            return 1;
        else
            return 2;
    }
    else
    {
        //first��second���ұ�
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
