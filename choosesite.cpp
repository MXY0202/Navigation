#include "choosesite.h"
#include "ui_choosesite.h"
#include "global.h"
#include "naviwindow.h"
#include <QCompleter>
#include <QDebug>
ChooseSite::ChooseSite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseSite)
{
    ui->setupUi(this);
    setWindowTitle("当前位置获取");
    QCompleter * build = new QCompleter(buildingList);
    ui->lineEdit->setCompleter(build);
}

ChooseSite::~ChooseSite()
{
    delete ui;
}

void ChooseSite::on_lineEdit_editingFinished()
{
    site = ui->lineEdit->text();
}

void ChooseSite::on_confirmBtn_clicked()
{
    currentSite = site;
    QMap<QString, int>::iterator iter = navi.buildingTable.begin();
    while(iter != navi.buildingTable.end())
    {
        if(currentSite == iter.key())//如果建筑名相同
        {
            currentPoint = iter.value();
            break;
        }
        iter++;
    }
    if(currentPoint < navi.secondBegin) //如果在校区1
        mapID = 1;
    else
        mapID = 0;
    int x = navi.getPointX(currentPoint);
    int y = navi.getPointY(currentPoint);
    qDebug() << currentSite << currentPoint << " "<< x << " "<< y;

    NaviWindow* naviWindow = new NaviWindow;
    naviWindow->show();
    this->close();
}
