#include "dialoglibben.h"
#include "ui_dialoglibben.h"
#include "global.h"
#include "log.h"
DialogLibBen::DialogLibBen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLibBen)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap("://librarybenbu"));
    ui->label->setScaledContents(true);
    ui->label3->setPixmap(QPixmap("://cloud"));
    ui->label3->setScaledContents(true);
    QMenu* menu1 = new QMenu;
    QAction* act1_1 = menu1->addAction("一层  马列主义、哲学、政治");
    QAction* act1_2 = menu1->addAction("走，去看马哲！");
    ui->floor1Btn->setMenu(menu1);
    connect(act1_1,&QAction::triggered,this,[=]
    {
       ui->label4->setText("《马克思恩格斯选集》《列宁选集》《斯大林选集》");
       ui->label5->setText("《毛泽东选集》《共产党宣言》《共产主义原理》");
       ui->label6->setText("《关于工人阶级的政治行动》《政治经济学批判》");
       ui->label7->setText("《资本论》《社会主义从空想到科学的发展》");
       ui->label8->setText("《无产阶级革命与叛徒考茨基》《马克思主义基本原理概论》");
    });
    connect(act1_2,&QAction::triggered,this,[=]
    {
        //传出来图书馆一层
        Log log;
        QString thisLog = "";
        thisLog += "图书馆导航   目的地：图书馆一层(校区一)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区一)");//将目的地存入
        currentSite = "图书馆西门(校区一)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
        this->close();
    });

    QMenu* menu2 = new QMenu;
    QAction* act2_1 = menu2->addAction("二层  数理科学");
    QAction* act2_2 = menu2->addAction("走，去夯实数理基础！");
    ui->floor2Btn->setMenu(menu2);
    connect(act2_1,&QAction::triggered,this,[=]
    {
       ui->label4->setText("《自然哲学的数学原理》《狭义相对论》《数学之美》《什么是数学》");
       ui->label5->setText("《数学：它的内容，方法和意义》《重温微积分》《古今数学思想》");
       ui->label6->setText("《吉米多维奇》《九章算术》《上帝掷骰子吗》《物理学进化》");
       ui->label7->setText("《见微知著》《从一到无穷大》《无机化学》《有机化学》《物理化学》");
       ui->label8->setText("《结构化学》《生物化学》");
    });
    connect(act2_2,&QAction::triggered,this,[=]
    {
           //传出来图书馆二层
        Log log;
        QString thisLog = "";
        thisLog += "图书馆导航   目的地：图书馆二层(校区一)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区一)");//将目的地存入
        currentSite = "图书馆西门(校区一)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
        this->close();
    });

    QMenu* menu3 = new QMenu;
    QAction* act3_1 = menu3->addAction("三层  艺术、体育");
    QAction* act3_2 = menu3->addAction("走，德智体美全面发展！");
    ui->floor3Btn->setMenu(menu3);
    connect(act3_1,&QAction::triggered,this,[=]
    {
       ui->label4->setText("《当代艺术》《哗众取宠》《观看之道》《艺术世界中的7天》");
       ui->label5->setText("《艺术的共谋》《美的历史》《丑的历史》《艺术的故事》");
       ui->label6->setText("《詹森艺术史》《现代艺术150年：一个未完成的故事》");
       ui->label7->setText("《散文与访谈》《清思集》《高水平竞技运动体能训练研究》");
       ui->label8->setText("《无器械健身：用自身体重锻炼》《拉伸》");
    });
    connect(act3_2,&QAction::triggered,this,[=]
    {
         //传出来图书馆三层
        Log log;
        QString thisLog = "";
        thisLog += "图书馆导航   目的地：图书馆三层(校区一)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区一)");//将目的地存入
        currentSite = "图书馆西门(校区一)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
        this->close();
    });

}

DialogLibBen::~DialogLibBen()
{
    delete ui;
}
