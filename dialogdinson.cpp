#include "dialogdinson.h"
#include "ui_dialogdinson.h"

dialogdinSon::dialogdinSon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogdinSon)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap("://teacher"));
    ui->label->setScaledContents(true);
}

dialogdinSon::~dialogdinSon()
{
    delete ui;
}
