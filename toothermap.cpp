#include "toothermap.h"
#include "ui_toothermap.h"
#include <iostream>
#include "global.h"
using namespace  std;
ToOtherMap::ToOtherMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToOtherMap)
{
    ui->setupUi(this);
    setWindowTitle("交通工具选择");
}

ToOtherMap::~ToOtherMap()
{
    delete ui;
}

void ToOtherMap::on_shoolBusBtn_clicked()
{
    cout << "选择了校车" << endl;
    shoolBusOrBus = SHOOLBUS;

}

void ToOtherMap::on_busBtn_clicked()
{
    shoolBusOrBus = BUS;
    cout << "选择了公交车" << endl;
}

void ToOtherMap::on_confirmBtn_clicked()
{
    alreadyChosen = true;
    this->close();
}
