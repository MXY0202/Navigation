#include "single.h"
#include "ui_single.h"
#include "global.h"
#include <QCompleter>
#include "log.h"
#include <QDebug>
Single::Single(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Single)
{
    ui->setupUi(this);
    setWindowTitle("单点路径导航");

    QCompleter * build = new QCompleter(buildingList);
    ui->pointEdit->setCompleter(build);

}

Single::~Single()
{
    delete ui;
}

void Single::on_pointEdit_textChanged(const QString &arg1)
{
    endPoint = arg1;//将pointEdit的内容赋给endPoint
}

void Single::on_quitBtn_clicked()
{
    this->close();
}

void Single::on_startBtn_clicked()
{
    Log log;
    QString thisLog = "";
    thisLog = "单点路径导航   起点：" + currentSite + "   终点： " + endPoint + "\n";
    log.print(thisLog);
    navi.wayPoint.push_back(currentSite);//将当前位置存入
    navi.wayPoint.push_back(endPoint);//将目的地存入
    currentSite = endPoint;
    navi.selectStrategy();
    currentPoint = navi.route.pop();
    nextPoint = navi.route.pop();
    qDebug() << nextPoint;
    startNavi = true; //可以开始导航
    this->close();
}
