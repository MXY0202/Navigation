#include "dialoggui.h"
#include "ui_dialoggui.h"


DialogGui::DialogGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGui)
{
    ui->setupUi(this);
    //ui->selectBtn->setText();
    QMenu* menu = new QMenu;
    QAction* act1 = menu->addAction("计算机院");
    QAction* act2 =  menu->addAction("信通院");
    QAction* act3 = menu->addAction("电子院");
    ui->selectBtn->setMenu(menu);
    connect(act1,&QAction::triggered,this,[=]{
       qDebug()<<"计算机院欢迎你" ;
       this->close();
    });
    connect(act2,&QAction::triggered,this,[=]{
       qDebug()<<"信通院欢迎你" ;
       this->close();
    });
    connect(act3,&QAction::triggered,this,[=]{
       qDebug()<<"电子院欢迎你" ;
       this->close();
    });
    QPixmap pixmap = QPixmap(":/pictures/badge.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

}

DialogGui::~DialogGui()
{
    delete ui;
}
