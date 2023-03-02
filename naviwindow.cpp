#include "naviwindow.h"
#include "ui_naviwindow.h"
#include "global.h"
#include "single.h"
#include "multipoints.h"
#include "choosesite.h"
#include "dialogdin.h"
#include "dialogdinben.h"
#include "dialogbui.h"
#include "dialoggui.h"
#include "log.h"
#include "dialoglib.h"
#include "dialoglibben.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QPair>
#include <toothermap.h>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <QCompleter>
#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4
const int speed = 2;
NaviWindow::NaviWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NaviWindow)
{
    ui->setupUi(this);

    initialMap();//将图片加载到pixmap中
    initialShoolBus();//将校车信息加载到shoolBusTable中
    initialClassTimeTable();//将课程信息读入classTimeTable
    beautify();
    ui->textEdit->setText("欢迎使用校园导航系统");
    setWindowTitle("校园导航系统");

    QCompleter * claCompleter = new QCompleter(classTimeTable);
    ui->goToClass->setCompleter(claCompleter);
    ui->goToClass->setClearButtonEnabled(true);
    busTime = 80;//公交车需要80分钟到达
    busInterval = 10;//公交车一趟10分钟

    x = navi.getPointX(currentPoint);
    y = navi.getPointY(currentPoint);
    startTimer(100);
}
void NaviWindow::beautify()
{
    this->setPalette(QPalette(Qt::white));
    ui->singlePointBtn->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->multiPointBtn->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->dinBtn->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->libBtn->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->searchByName->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->newStudents->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
}
void NaviWindow::initialClassTimeTable()
{
    QString cla, claSite;
    int classNum;
    QFile in(":/text/classTimeTable.txt");
    if(!in.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream fstrm(&in);
    cla = fstrm.readLine();
    classNum = cla.toInt();
    for(int i = 0; i < classNum; i++)
    {
        cla = fstrm.readLine();
        claSite = fstrm.readLine();
        classTimeTable << cla;
        classSite[cla] = claSite;
    }
}
void NaviWindow::initialShoolBus()
{
    QFile in(":/text/shoolBusTable.txt");
    if(!in.open(QIODevice::ReadOnly))
        exit(-1);
    QTextStream fstrm(&in);
    fstrm >> shoolBusTime;
    int num;
    fstrm >> num;
    for(int i = 0; i < num; i++)
    {
        QPair<int, int>* timeTable = new QPair<int, int>;
        fstrm >> timeTable->first >> timeTable->second;
        shoolBusTable.push_back(timeTable);
    }

}
void NaviWindow::initialMap()
{
    map1.load(":/pictures/map1.jpg");
    map2.load(":/pictures/map2.jpg");
    pixmap[0] = map1;
    pixmap[1] = map2;
    person.load(":/pictures/person.jpg");
    bike.load(":/pictures/bike.jpg");
    pixWay[0] = person;
    pixWay[1] = bike;
}
void NaviWindow::paintEvent(QPaintEvent *)
{
    QPainter mapPainter(this);
    mapPainter.setRenderHint(QPainter::HighQualityAntialiasing);
    mapPainter.drawPixmap(0, 0, 1484, 1050, pixmap[mapID]);
    // 1132 800 图片像素比  3508 2480
    QPainter wayPainter(this);
    wayPainter.setRenderHint(QPainter::HighQualityAntialiasing);
    wayPainter.drawPixmap(x, y, 40, 40, pixWay[wayID]);
}
NaviWindow::~NaviWindow()
{
    delete ui;
}

void NaviWindow::timerEvent(QTimerEvent *)
{
    //时间模块，显示当前时间
    showTime();

    if(true == isToOtherMap)//如果当前正在前往另一个校区
    {
        if(true == alreadyChosen && alreadyCal == false)//已经选择了前往另一个校区的方式且计算了到达时间
        {
            calArriveTime(hour, minute);
            alreadyCal = true;
        }
        if(alreadyCal == true)//如果已经计算，就等到达
        {
            if(hour == arriveHour && minute == arriveMinute)//如果已经到达
            {
                mapID = !mapID;//换图
                currentPoint = navi.route.pop();
                x = navi.getPointX(currentPoint);
                y = navi.getPointY(currentPoint);
                nextPoint = navi.route.pop();
                cout << "currentPoint:" << currentPoint << endl;
                cout << "nextPoint:" << nextPoint << endl;
                isToOtherMap = false;
                alreadyCal = false;
                alreadyChosen = false;
                update();
                return;
            }
        }
        return;
    }
    if(false == startNavi)//如果当前没有导航任务，退出
           return;
    //如果已经到达nextPoint
    if(x == navi.getPointX(nextPoint) && y == navi.getPointY(nextPoint))
    {
        currentPoint = nextPoint;
        if(!navi.route.isEmpty())//如果不空继续画
        {
            nextPoint = navi.route.pop();
            if(!navi.isSameCampus(currentPoint, nextPoint))//如果下一个点与当前点不在一个校区
            {
                isToOtherMap = true;//表示开始前往另一个校区
                navi.route.push(nextPoint);//将下一个校区的第一个点再入栈
                ToOtherMap *toOtherMap = new ToOtherMap;
                toOtherMap->show();
                return;
            }
        }
        else//如果已经为空,说明已经完成导航任务
        {
            navi.wayPoint.erase(navi.wayPoint.begin(), navi.wayPoint.end());
            startNavi = false;
            return;
        }
    }
    int dir = navi.getDir(currentPoint, nextPoint);
    if(dir == NORTH)
        y -= speed;
    else if(dir == SOUTH)
        y += speed;
    else if(dir == EAST)
        x -= speed;
    else if(dir == WEST)
        x += speed;
    update();
}
void NaviWindow::calArriveTime(const int currentHour, const int currentMinute)
{
    QString text;
    if(shoolBusOrBus == BUS)//如果选择的是公交车
    {
        int comeTime = 0;
        if(currentMinute % 10 == 0)//公交车已经来了
            text += "公交车已经来了，快上车吧！\n";
        else
        {
            comeTime = 10 - currentMinute % 10;
                    text += "公交车还有" + QString::number(comeTime) + "分钟到达！\n";
        }
        arriveMinute  = currentMinute + busTime + comeTime;
    }
    else if(shoolBusOrBus == SHOOLBUS)//如果选择校车，根据shoolBusTable计算
    {
        int comeTime;
        for(int i = 0; i < shoolBusTable.size(); i++)
        {
            int time = 60 * shoolBusTable[i]->first + shoolBusTable[i]->second;
            if(time >= 60 * currentHour + currentMinute)
            {
                comeTime = time - (60 * currentHour + currentMinute);
                if(comeTime == 0)
                    text += "校车已经到了，快上车吧！\n";
                else
                    text += "校车还有" + QString::number(comeTime) + "分钟到达！\n";
                arriveMinute = currentMinute + shoolBusTime + comeTime;
                break;
            }
        }
    }
    if(arriveMinute > 60)
    {
        arriveHour = currentHour + arriveMinute / 60;
        arriveMinute = arriveMinute % 60;
    }
    else
        arriveHour = currentHour + 1;
    text = text + "您将在" + QString::number(arriveHour) + ":" + QString::number(arriveMinute) + "到达!";
    ui->textEdit->clear();
    ui->textEdit->setText(text);
    return;
}
void NaviWindow::showTime()
{
    if(minute == 59)
    {
        minute = 0;
        hour ++;
    }
    else
        minute++;
    if(hour == 24)
    {
        hour = 0;
    }
    QString hourTemp = "";
    if(hour <= 9)
        hourTemp = '0';
    QString timeHour = QString::number(hour);
    timeHour = hourTemp + timeHour;
    QString minuteTemp = "";
    if(minute <= 9)
        minuteTemp = '0';
    QString timeMinute = QString::number(minute);
    timeMinute = minuteTemp + timeMinute;
    QString time = timeHour + ":" + timeMinute;
    ui->lcdTime->setGeometry(1550, 50, 300, 60);
    ui->lcdTime->display(time);
}

void NaviWindow::on_singlePointBtn_clicked()
{
    Single* single = new Single;//创建单点导航窗口
    single->show();
}

void NaviWindow::on_multiPointBtn_clicked()
{
    MultiPoints* multiPoints = new MultiPoints;
    multiPoints->show();
}

void NaviWindow::on_searchByScope_editingFinished()
{
    Log log;
    QString thisLog = "";
    QString temp = ui->searchByScope->text();
    QString text = "";
    bool flag = false;
    int scope = temp.toInt();
    thisLog += "按范围查询周围建筑物   当前点" + currentSite + "查询范围：" + QString::number(scope) + "米\n";
    log.print(thisLog);
    QMap<QString, int>::iterator iter = navi.buildingTable.begin();
    qDebug() << navi.secondBegin;
    qDebug() << currentSite << " " << currentPoint;
    while(iter != navi.buildingTable.end())
    {
        if(navi.isSameCampus(currentPoint, iter.value()) && navi.getDis(currentPoint, iter.value()) <= scope);//如果在输入范围内
        {
            text += iter.key() + "\n";
            flag = true;
        }
        iter++;
    }
    ui->textEdit->clear();
    if(false == flag)
        ui->textEdit->setText("该范围内不存在建筑物");
    else
        ui->textEdit->setText(text);
    return;
}



void NaviWindow::on_goToClass_editingFinished()
{
    Log log;
    QString thisLog = "";

    QString cla = ui->goToClass->text();
    thisLog += "去上课   课程：" + cla + "\n";
    log.print(thisLog);
    QString end = classSite[cla];
    navi.wayPoint.push_back(currentSite);
    navi.wayPoint.push_back(end);
    navi.selectStrategy();
    currentPoint = navi.route.pop();
    nextPoint = navi.route.pop();
    startNavi = true;
}

void NaviWindow::on_bikeCheck_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->walkCheck->blockSignals(true);
        ui->walkCheck->setCheckState(Qt::CheckState::Unchecked);
        ui->walkCheck->blockSignals(false);
        navi.travelWay = BIKE;
        wayID = 1;
    }
}

void NaviWindow::on_walkCheck_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->bikeCheck->blockSignals(true);
        ui->bikeCheck->setCheckState(Qt::CheckState::Unchecked);
        ui->bikeCheck->blockSignals(false);
        navi.travelWay = WALK;
        wayID = 0;
    }
}

void NaviWindow::on_minDisCheck_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->minTimeCheck->blockSignals(true);
        ui->minTimeCheck->setCheckState(Qt::CheckState::Unchecked);
        ui->minTimeCheck->blockSignals(false);
        navi.travelStrategy = MINDIS;
    }
}

void NaviWindow::on_minTimeCheck_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->minDisCheck->blockSignals(true);
        ui->minDisCheck->setCheckState(Qt::CheckState::Unchecked);
        ui->minDisCheck->blockSignals(false);
        navi.travelStrategy = MINTIME;
    }
}

void NaviWindow::on_dinBtn_clicked()
{
    if(currentPoint > navi.secondBegin)//如果是校区二
    {
        DialogDin *dialogDin = new DialogDin;
        dialogDin->show();
    }
    else
    {
        DialogDinBen *dialogDinBen = new DialogDinBen;
        dialogDinBen->show();
    }
}

void NaviWindow::on_libBtn_clicked()
{
    if(currentPoint > navi.secondBegin)
    {
        DialogLib *dialogBin = new DialogLib;
        dialogBin->show();
    }
    else
    {
        DialogLibBen *dialogLibBen = new DialogLibBen;
        dialogLibBen->show();
    }
}

void NaviWindow::on_searchByName_clicked()
{
    dialogBui *DialogBui = new dialogBui;
    DialogBui->show();
}

void NaviWindow::on_newStudents_clicked()
{
    DialogGui *dialogGui = new DialogGui;
    dialogGui->show();
}
