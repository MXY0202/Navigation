#include "multipoints.h"
#include "ui_multipoints.h"
#include "global.h"
#include "log.h"
#include <QCompleter>
#include <QDebug>
MultiPoints::MultiPoints(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiPoints)
{
    ui->setupUi(this);
    setWindowTitle("途径多点导航");

    QWidget *con = new QWidget(this);
    grad = new QGridLayout(this);

    multiNum = 0;
    grad->setMargin(5);
    grad->setSpacing(5);
    con->setLayout(grad);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(con);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);

    QCompleter * build = new QCompleter(buildingList);
    ui->endEdit->setCompleter(build);
}

MultiPoints::~MultiPoints()
{
    delete ui;
}

void MultiPoints::addPoints(int num)
{
    while(num > multiNum)
    {
        QLineEdit *m = new QLineEdit(ui->scrollArea);
        m->setMinimumSize(50, 25);
        QCompleter * build = new QCompleter(buildingList);
        m->setCompleter(build);
        QLabel *l = new QLabel(ui->scrollArea);
        l->setMinimumSize(70, 50);
        l->setText("途径点" + QString::number(multiNum + 1));
        grad->addWidget(l,multiNum,0);
        grad->addWidget(m,multiNum,1);

        buildingEdit.push_back(m);
        myLabel.push_back(l);
        multiNum = buildingEdit.size();
    }
}

void MultiPoints::on_confirmBtn_clicked()
{
    //将输入存进navi.wayPoint中
    Log log;
    QString thisLog = "";
    navi.wayPoint.push_back(currentSite);
    thisLog += "途径多点导航   起点：" + currentSite + "   ";
    int i = 1;
    while(!buildingEdit.isEmpty())
    {
        QLineEdit *m = buildingEdit.back();
        navi.wayPoint.push_back(m->text());
        thisLog += "途径点" + QString::number(i) + ":  " + m->text() + "  ";
        buildingEdit.pop_back();
        i++;
    }
    thisLog += "终点： " + endPoint + "\n";
    log.print(thisLog);
    navi.wayPoint.push_back(endPoint);
    qDebug() << endPoint;
    currentSite = endPoint;
    navi.selectStrategy();
    currentPoint = navi.route.pop();
    nextPoint = navi.route.pop();
    startNavi = true; //可以开始导航
    this->close();
}

void MultiPoints::on_quitBtn_clicked()
{
    this->close();
}

void MultiPoints::on_spinBox_valueChanged(int arg1)
{
    addPoints(arg1);
}

void MultiPoints::on_endEdit_returnPressed()
{
    endPoint = ui->endEdit->text();
}
