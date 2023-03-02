#include "dialogbui.h"
#include "ui_dialogbui.h"
#include "global.h"
#include "log.h"
#include <QCompleter>
dialogBui::dialogBui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogBui)
{
    ui->setupUi(this);
}

dialogBui::~dialogBui()
{
    delete ui;
}

void dialogBui::on_searchBtn_clicked()
{
    Log log;
    QString thisLog = "";
    QString buildName = ui->lineEdit_3->text();     //读取建筑物名称
    thisLog += "按名称查询建筑物   查询名称：" + buildName + "\n";
    log.print(thisLog);
    ui->textBrowser->clear();
    if(buildName=="图书馆")
        {
            ui->textBrowser->append("学习的地方");
            ui->label->setPixmap(QPixmap("://library"));
            ui->label->setScaledContents(true);
        }
    else if(buildName=="学生食堂")
        {
        ui->textBrowser->append("学生吃饭的地方");
        ui->label->setPixmap(QPixmap("://library"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="西土城校区南门")
        {
        ui->textBrowser->append("北京邮电大学西土城校区南门");
        ui->label->setPixmap(QPixmap("://benbunanmen"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="西土城校区足球场")
        {
        ui->textBrowser->append("北京邮电大学西土城校区足球场");
        ui->label->setPixmap(QPixmap("://benbuzuqiuchang"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="西土城校区学生食堂")
        {
        ui->textBrowser->append("北京邮电大学西土城校区学生食堂");
        ui->label->setPixmap(QPixmap("://benbuxueshengshitang"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="西土城校区图书馆")
        {
        ui->textBrowser->append("北京邮电大学图书馆建于1955年。现有馆舍面积1.4万平方米，职工64人；全馆共设办公室、信息资源建设部、流通部、阅览部、信息咨询部、技术部等6个部门。现有总馆藏近344万册（件），其中纸质藏书146万余册，电子资源（折合）197万余册。除印刷型书刊文献外，还有IEL、EIvillage、ISTP、PQDD、中国学术期刊全文数据库、书生电子图书等26个电子文献数据库；自建了“邮电通信专题文献数据库”、“高等教育教学成果相关文献数据库”、“北邮记忆数据库”等5个数据库");
        ui->label->setPixmap(QPixmap("://benbutushuguan"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="西土城校区主楼")
        {
        ui->textBrowser->append("北京邮电大学是教育部直属、工业和信息化部共建、首批进行“211工程”建设的全国重点大学，是“985优势学科创新平台”项目重点建设高校，是一所以信息科技为特色、工学门类为主体、工管文理协调发展的多科性大学，是我国信息科技人才的重要培养基地。");
        ui->label->setPixmap(QPixmap("://benbuzhulou"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区教学实验综合楼N楼")
        {
        ui->textBrowser->append("教学实验综合楼主要分为N和S两楼，总共分为五层，楼体的中间建设了报告厅，楼层地下设置有用于实验课的专项实验室。沙河校区教学实验综合楼体量由东向西跌落，形成丰富的屋顶绿化平台，平台之间以大楼梯相连，既为师生提供景观优美的室外休闲、交流场所，又适合课间等瞬时高峰人流的疏散。");
        ui->label->setPixmap(QPixmap("://shahejiaoxuelou"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区教学实验综合楼S楼")
        {
        ui->textBrowser->append("教学实验综合楼主要分为N和S两楼，总共分为五层，楼体的中间建设了报告厅，楼层地下设置有用于实验课的专项实验室。沙河校区教学实验综合楼体量由东向西跌落，形成丰富的屋顶绿化平台，平台之间以大楼梯相连，既为师生提供景观优美的室外休闲、交流场所，又适合课间等瞬时高峰人流的疏散。");
        ui->label->setPixmap(QPixmap("://shahejiaoxuelou"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区学生食堂")
        {
        ui->textBrowser->append("沙河校区食堂共有两楼，分别为位于北面的教工食堂和位于南面的学生食堂，每楼分为五层，包括的菜系丰富，菜品种类繁多。");
        ui->label->setPixmap(QPixmap("://shaheshitang"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区教工食堂")
        {
        ui->textBrowser->append("沙河校区食堂共有两楼，分别为位于北面的教工食堂和位于南面的学生食堂，每楼分为五层，包括的菜系丰富，菜品种类繁多。");
        ui->label->setPixmap(QPixmap("://shaheshitang"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区学生活动中心")
        {
        ui->textBrowser->append("内设各社团的活动场地，有羽毛球场、健身房、多媒教室以及舞蹈室等。校团委/学生处/招就处联合办公楼、活动中心、学生食堂四栋单体建筑之间利用室外平台或连桥加以连通，平台和连桥穿梭于高大的树木之间，不同的空间在不同的高度和位置连接，徜徉在平台、连桥和街道的上空，有一种立体城市的体验。");
        ui->label->setPixmap(QPixmap("://shahexuehuo"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区雁北楼")
        {
        ui->textBrowser->append("北京邮电大学沙河校区雁北楼");
        ui->label->setPixmap(QPixmap("://shaheyanbei"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区西门")
        {
        ui->textBrowser->append("北京邮电大学沙河校区的西门由许多镂空的立体二维码构成，体现了信息黄埔的特色。");
        ui->label->setPixmap(QPixmap("://shaheximen"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区图书馆")
        {
        ui->textBrowser->append("北邮沙河校区图书馆建筑总面积为3.67万平方米，图书馆平面布局呈C型。在建筑东南角围合形成一个较大的室外庭院，现状树阵穿过庭院，使庭院成为学生课余学习交流的良好场所。一条贯穿东西的内街穿过建筑，连接起宿舍区、食堂和学生活动中心以及东面的教学建筑。东侧开口处设置空中连廊，保持南北两翼的连通。图书馆礼仪入口设在南部，沿弧形大楼梯盘桓而上至二层。在内街庭院的南北两侧分别设置南、北两翼的首层主入口，满足不同功能区的需要。");
        ui->label->setPixmap(QPixmap("://library"));
        ui->label->setScaledContents(true);
        }
    else if(buildName=="沙河校区足球场")
        {
        ui->textBrowser->append("北京邮电大学沙河校区足球场");
        ui->label->setPixmap(QPixmap("://shahezuqiuchang"));
        ui->label->setScaledContents(true);
        }

    else if(buildName=="沙河校区篮球场")
        {
        ui->textBrowser->append("北京邮电大学沙河校区篮球场");
        ui->label->setPixmap(QPixmap("://shahelanqiuchang"));
        ui->label->setScaledContents(true);
        }
    else
        {
             ui->textBrowser->append("未找到目标建筑物，请重新检查输入");
        }

}

void dialogBui::on_goBtn_clicked()
{
    //传出来 ui->lineEdit->text() 文本框中输入内容
    this->close();
}

