#ifndef NAVIWINDOW_H
#define NAVIWINDOW_H

#include <QWidget>
#include <QPaintEvent>
namespace Ui {
class NaviWindow;
}

class NaviWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NaviWindow(QWidget *parent = nullptr);
    ~NaviWindow();

    void initialShoolBus();
    void initialClassTimeTable();
    void paintEvent(QPaintEvent *);
    void initialMap();
    void timerEvent(QTimerEvent *);
    void calArriveTime(const int currentHour, const int currentMinute);
    void showTime();
    void beautify();
private slots:
    void on_singlePointBtn_clicked();//单点路径导航

    void on_multiPointBtn_clicked();//途径多点导航

    void on_searchByScope_editingFinished();//按范围查询建筑物并展示在TextEdit内


    void on_goToClass_editingFinished();

    void on_bikeCheck_stateChanged(int arg1);

    void on_walkCheck_stateChanged(int arg1);

    void on_minDisCheck_stateChanged(int arg1);

    void on_minTimeCheck_stateChanged(int arg1);

    void on_dinBtn_clicked();

    void on_libBtn_clicked();

    void on_searchByName_clicked();

    void on_newStudents_clicked();

private:
    Ui::NaviWindow *ui;
    //图片
    QPixmap pixmap[2];
    QPixmap pixWay[2];
    QPixmap map1;
    QPixmap map2;
    QPixmap person;
    QPixmap bike;
    //时间
    int hour = 6;
    int minute = 0;
    bool alreadyCal;//是否已经计算到达另一个校区时间
    int arriveHour;
    int arriveMinute;
    int x;//当前坐标
    int y;
    QVector<QPair<int,int> *> shoolBusTable;//校车时刻表
    int shoolBusTime;//校车所需时间
    int busInterval;//公交车到站间隔
    int busTime;//公交车所需时间

    QStringList classTimeTable;
    QMap<QString, QString> classSite;
};

#endif // NAVIWINDOW_H
