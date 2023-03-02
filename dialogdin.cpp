#include "dialogdin.h"
#include "ui_dialogdin.h"
#include<QString>
#include<QTime>
#include "global.h"
#include "log.h"
DialogDin::DialogDin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDin)
{
    ui->setupUi(this);
    //

    ui->label3->setPixmap(QPixmap("://canteen"));
    ui->label3->setScaledContents(true);

    ui->student1Btn->setIcon(QIcon("://student"));  //button的图标设置
    ui->student1Btn->setIconSize(QSize(30,20));
    connect(ui->student1Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "学生食堂一层欢迎你";
    });
    ui->student2Btn->setIcon(QIcon("://student"));
    ui->student2Btn->setIconSize(QSize(30,20));
    connect(ui->student2Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "学生食堂二层欢迎你";
    });
    ui->student3Btn->setIcon(QIcon("://student"));
    ui->student3Btn->setIconSize(QSize(30,20));
    connect(ui->student3Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "学生食堂三层欢迎你";
    });
    ui->student4Btn->setIcon(QIcon("://student"));
    ui->student4Btn->setIconSize(QSize(30,20));
    connect(ui->student4Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "学生食堂四层欢迎你";
    });
    ui->student5Btn->setIcon(QIcon("://student"));
    ui->student5Btn->setIconSize(QSize(30,20));
    connect(ui->student5Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "学生食堂五层欢迎你";
    });
    ui->student5Btn->setIcon(QIcon("://student"));
    ui->student5Btn->setIconSize(QSize(30,20));
    connect(ui->student5Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "学生食堂五层欢迎你";
    });
    ui->teacher1Btn->setIcon(QIcon("://teacher"));
    ui->teacher1Btn->setIconSize(QSize(30,20));
    connect(ui->teacher1Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "教工食堂一层欢迎你";
    });
    ui->teacher2Btn->setIcon(QIcon("://teacher"));
    ui->teacher2Btn->setIconSize(QSize(30,20));
    connect(ui->teacher2Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "教工食堂二层欢迎你";
    });
    ui->teacher3Btn->setIcon(QIcon("://teacher"));
    ui->teacher3Btn->setIconSize(QSize(30,20));
    connect(ui->teacher3Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "教工食堂三层欢迎你";
    });
    ui->teacher4Btn->setIcon(QIcon("://teacher"));
    ui->teacher4Btn->setIconSize(QSize(30,20));
    connect(ui->teacher4Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "教工食堂四层欢迎你";
    });
    ui->teacher5Btn->setIcon(QIcon("://teacher"));
    ui->teacher5Btn->setIconSize(QSize(30,20));
    connect(ui->teacher5Btn,&QPushButton::clicked,this,[=]()
    {
        qDebug() << "教工食堂五层欢迎你";
    });
    ui->randBtn->setIcon(QIcon("://touzi"));
    ui->randBtn->setIconSize(QSize(30,20));
    connect(ui->randBtn,&QPushButton::clicked,this,[=]()
    {
        QString a[10];
        a[0]="去教工一层吧";
        a[1]="去教工二层吧";
        a[2]="去教工三层吧";
        a[3]="去教工四层吧";
        a[4]="去教工五层吧";
        a[5]="去学生一层吧";
        a[6]="去学生二层吧";
        a[7]="去学生三层吧";
        a[8]="去学生四层吧";
        a[9]="去学生五层吧";
        qsrand(time(NULL));
        int n = qrand()%10;
        qDebug() << a[n];           //弄一个长度为10的string数组存储 随机数输出下标
        QString temp = "学生食堂(校区二)";
        if(n % 2 == 0)
            temp = "教工食堂(校区二)";
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("temp");//将目的地存入
        currentSite = "temp";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
    });

    QMenu* menu1 = new QMenu;
    QAction* act1_1 = menu1->addAction("风味介绍");
    QAction* act1_2 =  menu1->addAction("就餐环境");
    QAction* act1_3 = menu1->addAction("专属美食");
    QAction* act1_4 = menu1->addAction("就这么愉快地决定了");
    ui->student1Btn->setMenu(menu1);
    connect(act1_1,&QAction::triggered,this,[=]
    {
        qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("学一以基本伙为主。学一的优势在于营业时间超长，哪怕晚上八点也不打烊。代表菜有烤冷面手抓饼。鸡蛋灌饼也是不错的选择。");

    });
    connect(act1_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://xueyi"));
        ui->label1->setScaledContents(true);
    });
    connect(act1_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://xueyicai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act1_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：学生食堂一层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("学生食堂(校区二)");//将目的地存入
        currentSite = "学生食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu2 = new QMenu;
    QAction* act2_1 = menu2->addAction("风味介绍");
    QAction* act2_2 =  menu2->addAction("就餐环境");
    QAction* act2_3 = menu2->addAction("专属美食");
    QAction* act2_4 = menu2->addAction("就这么愉快地决定了");
    ui->student2Btn->setMenu(menu2);
    connect(act2_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("学二是清真食堂。清真菜：清真菜所用肉类原料以牛、羊、鸡、鸭为主，其烹调方法类似京菜，以熘、炒、爆、涮见长，喜欢用植物油、盐、醋、糖调味。口味多清鲜脆嫩、酥烂香浓。清真菜烹制羊肉最为擅长，其“全羊席”脍炙人口。");
    });
    connect(act2_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://xueer"));
        ui->label1->setScaledContents(true);
    });
    connect(act2_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://xueercai"));
        ui->label2->setScaledContents(true);
    });
    connect(act2_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：学生食堂二层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("学生食堂(校区二)");//将目的地存入
        currentSite = "学生食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu3 = new QMenu;
    QAction* act3_1 = menu3->addAction("风味介绍");
    QAction* act3_2 =  menu3->addAction("就餐环境");
    QAction* act3_3 = menu3->addAction("专属美食");
    QAction* act3_4 = menu3->addAction("就这么愉快地决定了");
    ui->student3Btn->setMenu(menu3);
    connect(act3_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("学三以基本伙为主。优势在于价格实惠，据说是学校补贴最多的一个食堂。营业时间比较傲娇，周六周日是不开门的。只有中餐和晚餐，没有早餐。味道一般，适合吃土少年，七块钱的鸭腿算是必吃菜。");
    });
    connect(act3_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://jiaosan"));
        ui->label1->setScaledContents(true);
    });
    connect(act3_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://xuesancai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act3_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：学生食堂三层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("学生食堂(校区二)");//将目的地存入
        currentSite = "学生食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu4 = new QMenu;
    QAction* act4_1 = menu4->addAction("风味介绍");
    QAction* act4_2 =  menu4->addAction("就餐环境");
    QAction* act4_3 = menu4->addAction("专属美食");
    QAction* act4_4 = menu4->addAction("就这么愉快地决定了");
    ui->student4Btn->setMenu(menu4);
    connect(act4_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("学四以时尚快餐为主。在这里你能找到麻辣烫，麻辣拌，麻辣香锅，螺蛳粉，牛腩面，水煮肉片，黄焖鸡等特色小吃。顺便一提，学四基本伙也不错，就是价格会有小贵。");
    });
    connect(act4_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://xuesi"));
        ui->label1->setScaledContents(true);
    });
    connect(act4_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://xuesicai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act4_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：学生食堂四层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("学生食堂(校区二)");//将目的地存入
        currentSite = "学生食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu5 = new QMenu;
    QAction* act5_1 = menu5->addAction("风味介绍");
    QAction* act5_2 =  menu5->addAction("就餐环境");
    QAction* act5_3 = menu5->addAction("专属美食");
    QAction* act5_4 = menu5->addAction("就这么愉快地决定了");
    ui->student5Btn->setMenu(menu5);
    connect(act5_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("学五以自助餐出名。学五的自助餐满足了同学们对于口味多元化的需求，值得尝试。学五的猪扒饭和烧腊叉烧窗口也是热门窗口。");
    });
    connect(act5_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://xuewu"));
        ui->label1->setScaledContents(true);
    });
    connect(act5_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://xuewucai"));
        ui->label2->setScaledContents(true);
    });
    connect(act5_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：学生食堂五层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("学生食堂(校区二)");//将目的地存入
        currentSite = "学生食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu6 = new QMenu;
    QAction* act6_1 = menu6->addAction("风味介绍");
    QAction* act6_2 =  menu6->addAction("就餐环境");
    QAction* act6_3 = menu6->addAction("专属美食");
    QAction* act6_4 = menu6->addAction("就这么愉快地决定了");
    ui->teacher1Btn->setMenu(menu6);
    connect(act6_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("教一以基本伙和早餐为主。作为一层，优点也是待机时间长。小面是一绝，值得品尝。基本伙价格稍高，但质量有保障");
    });
    connect(act6_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://jiaoyi"));
        ui->label1->setScaledContents(true);
    });
    connect(act6_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://jiaoyicai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act6_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：教工食堂一层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("教工食堂(校区二)");//将目的地存入
        currentSite = "教工食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu7 = new QMenu;
    QAction* act7_1 = menu7->addAction("风味介绍");
    QAction* act7_2 =  menu7->addAction("就餐环境");
    QAction* act7_3 = menu7->addAction("专属美食");
    QAction* act7_4 = menu7->addAction("就这么愉快地决定了");
    ui->teacher2Btn->setMenu(menu7);
    connect(act7_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("教二以川菜为主。川菜：其特点是麻、辣香、油重、味浓，注重调味，离不开三椒（即辣椒、胡椒、花椒)和鲜姜，以辣、酸、麻脍炙人口，烹饪方法集所有菜系之首，为其他地方菜所少有，形成川菜的独特风味，享有“一菜一味，百菜百味”的美誉。代表菜肴的品种有“大煮干丝”、“鱼香肉丝”、“怪味鸡块”、“麻婆豆腐”等，是中国在世界上最著名的菜系。");
    });
    connect(act7_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://jiaoer"));
        ui->label1->setScaledContents(true);
    });
    connect(act7_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://jiaoercai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act7_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：教工食堂二层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("教工食堂(校区二)");//将目的地存入
        currentSite = "教工食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu8 = new QMenu;
    QAction* act8_1 = menu8->addAction("风味介绍");
    QAction* act8_2 =  menu8->addAction("就餐环境");
    QAction* act8_3 = menu8->addAction("专属美食");
    QAction* act8_4 = menu8->addAction("就这么愉快地决定了");
    ui->teacher3Btn->setMenu(menu8);
    connect(act8_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("教三以湘菜口味为主。湘菜：其特点是用料广泛，油重色浓，多以辣椒、熏腊为原料，口味注重香鲜、酸辣、软嫩。烹调方法擅长腊、熏、煨、蒸、炖、炸、炒。湘菜多辣，干锅干炒为主。");
    });
    connect(act8_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://jiaosan"));
        ui->label1->setScaledContents(true);
    });
    connect(act8_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://jiaosancai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act8_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：教工食堂三层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("教工食堂(校区二)");//将目的地存入
        currentSite = "教工食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu9 = new QMenu;
    QAction* act9_1 = menu9->addAction("风味介绍");
    QAction* act9_2 =  menu9->addAction("就餐环境");
    QAction* act9_3 = menu9->addAction("专属美食");
    QAction* act9_4 = menu9->addAction("就这么愉快地决定了");
    ui->teacher4Btn->setMenu(menu9);
    connect(act9_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("教四以粤菜为主：粤菜：粤菜作为我国八大菜系之一，尤以选料之广博而闻名。粤菜讲究本味，以养为主,不破坏食物本身，对烹饪要求高明，用菜精致和宫殿菜不分高下，本人以为粤菜乃中国菜之首。");
    });
    connect(act9_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://jiaosi"));
        ui->label1->setScaledContents(true);
    });
    connect(act9_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://jiaosicai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act9_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：教工食堂四层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("教工食堂(校区二)");//将目的地存入
        currentSite = "教工食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });

    QMenu* menu10 = new QMenu;
    QAction* act10_1 = menu10->addAction("风味介绍");
    QAction* act10_2 =  menu10->addAction("就餐环境");
    QAction* act10_3 = menu10->addAction("专属美食");
    QAction* act10_4 = menu10->addAction("就这么愉快地决定了");
    ui->teacher5Btn->setMenu(menu10);
    connect(act10_1,&QAction::triggered,this,[=]
    {
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       ui->textBrowser->clear();
        ui->textBrowser->append("教五以鲁菜为主：鲁菜：其特点是清香、鲜嫩、味纯而著名，十分讲究清汤和奶汤的调制，清汤色清而鲜，奶汤色白而醇。济南菜擅长爆、烧、炸、炒，其著名品种有“糖醋黄河鲤鱼”、“清汤燕窝”等。");
    });
    connect(act10_2,&QAction::triggered,this,[=]
    {
        ui->label1->setPixmap(QPixmap("://jiaowu"));
        ui->label1->setScaledContents(true);
    });
    connect(act10_3,&QAction::triggered,this,[=]
    {
        ui->label2->setPixmap(QPixmap("://jiaowucai"));
        ui->label2->setScaledContents(true);
        //dialogdson = new dialogdinSon(this);
        //dialogdson->setModal(false);
        //dialogdson->show();
    });
    connect(act10_4,&QAction::triggered,this,[=]
    {
        //传字符串
        Log log;
        QString thisLog = "";
        thisLog += "食堂导航   目的地：教工食堂五层(校区二)\n";
        log.print(thisLog);
        navi.wayPoint.push_back(currentSite);//将当前位置存入
        navi.wayPoint.push_back("教工食堂(校区二)");//将目的地存入
        currentSite = "教工食堂(校区二)";
        navi.selectStrategy();
        currentPoint = navi.route.pop();
        nextPoint = navi.route.pop();
        startNavi = true; //可以开始导航
       qDebug()<<"欢迎你,这就是我们的食堂" ;
       this->close();
    });
}

void DialogDin::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //pix.load("E:/A_code/picture/bupt.jpeg");
    painter.drawPixmap(0,0,width(),height(),pix);
}

DialogDin::~DialogDin()
{
    delete ui;
}
