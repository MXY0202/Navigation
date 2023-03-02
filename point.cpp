#include "point.h"
#include <cmath>
#include <iostream>
using namespace std;
Point::Point()
{
    seq = 0;
    x = 0;
    y = 0;
    next = NULL;
}
Point::Point(int seq, int x, int y, nextSeq adjPoint)
{
    this->seq = seq;
    this->x = x;
    this->y = y;
    this->next = adjPoint;
};
void Point::Print()
{
    cout << seq << " " << x << " " << y << " ";
    nextSeq currency = next;
    while (currency->next != NULL)
    {
        currency = currency->next;
        cout << currency->seq << " " << currency->congestion << " "<< currency->isBike << " ";
    }
    cout << endl;
}
int Point::dis(const Point otherPoint)
{
    int num;
    num = pow(this->x - otherPoint.x, 2) + pow(this->y - otherPoint.y, 2);
    return sqrt(num);
}
nextSeq Point::getNext()
{
    nextSeq thisPointer = this->next;
    return thisPointer;
}
