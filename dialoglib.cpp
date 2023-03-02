#include "dialoglib.h"
#include "ui_dialoglib.h"
#include "global.h"
#include "log.h"
DialogLib::DialogLib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLib)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap("://library"));
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
        thisLog += "图书馆导航   目的地：图书馆一层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区二)");//将目的地存入
        currentSite = "图书馆西门(校区二)";
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
        thisLog += "图书馆导航   目的地：图书馆二层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区二)");//将目的地存入
        currentSite = "图书馆西门(校区二)";
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
        thisLog += "图书馆导航   目的地：图书馆三层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区二)");//将目的地存入
        currentSite = "图书馆西门(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
        this->close();
    });

    QMenu* menu4 = new QMenu;
    QAction* act4_1 = menu4->addAction("四层  语言、文学");
    QAction* act4_2 = menu4->addAction("走，去感受人文的熏陶！");
    ui->floor4Btn->setMenu(menu4);
    connect(act4_1,&QAction::triggered,this,[=]
    {
       ui->label4->setText("《平凡的世界》《朝花夕拾》《汪曾祺散文集》《告诉我书的消息》");
       ui->label5->setText("《追风筝的人》《麦田里的守望者》《百年孤独》《巴黎圣母院》");
       ui->label6->setText("《少年维特的烦恼》《边城》《时间旅行者的妻子》《读物》");
       ui->label7->setText("《演讲与口才》《口才听说训练》《李敖有话说》《中国文字学》");
       ui->label8->setText("《中国语言学史》《训诂简论》《西方语言学名著选读》");
    });
    connect(act4_2,&QAction::triggered,this,[=]
    {
        //传出来图书馆四层
        Log log;
        QString thisLog = "";
        thisLog += "图书馆导航   目的地：图书馆四层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区二)");//将目的地存入
        currentSite = "图书馆西门(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
        this->close();
    });

    QMenu* menu5 = new QMenu;
    QAction* act5_1 = menu5->addAction("五层  历史、地理、天文");
    QAction* act5_2 = menu5->addAction("走，去探寻世界的奥秘！");
    ui->floor5Btn->setMenu(menu5);
    connect(act5_1,&QAction::triggered,this,[=]
    {
       ui->label4->setText("《全球通史》《世界人民的历史：从石器时代到新千年》《历史学是什么》");
       ui->label5->setText("《美国史》《一战史》《历史之谜：一个经济学的答案》");
       ui->label6->setText("《图像证史》《西方史学史：古代、中世纪和近代》");
       ui->label7->setText("《这里是中国》《中国景色》《旅行故事》《撒野非洲》");
       ui->label8->setText("《天文学新概论》《天象大观》《基础天文学》");
    });
    connect(act5_2,&QAction::triggered,this,[=]
    {
        //传出来图书馆五层
        Log log;
        QString thisLog = "";
        thisLog += "图书馆导航   目的地：图书馆五层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("图书馆西门(校区二)");//将目的地存入
        currentSite = "图书馆西门(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
        this->close();
    });
}

DialogLib::~DialogLib()
{
    delete ui;
}
