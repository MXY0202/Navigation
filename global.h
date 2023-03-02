#ifndef GLOBAL_H
#define GLOBAL_H
#include "navi.h"
#define BUS 1
#define SHOOLBUS 0
extern Navi navi;//导航所需
extern bool mapID;//当前所在地图
extern bool wayID;//出行方式
extern int currentPoint;//当前用户逻辑位置
extern int nextPoint; //如果要进行移动，用户的下一个位置
extern bool startNavi;//是否可以开始导航
extern bool isToOtherMap;//正在去另一个校区
extern bool shoolBusOrBus;//去另一个校区的方式
extern bool alreadyChosen;//是否已经选择了去另一个校区的方式
extern QString currentSite;//用户当前所在物理位置
extern QStringList buildingList;//自动补全使用

#endif // GLOBAL_H
