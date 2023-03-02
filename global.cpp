#include "global.h"
#include "navi.h"

Navi navi;//导航所需
bool mapID;//当前所在地图
bool wayID = 0;//出行方式
int currentPoint = 0;//当前用户逻辑位置
int nextPoint = 0;//如果要进行移动，用户的下一个位置
bool startNavi = 0;//是否开始导航
bool isToOtherMap = 0;//正在去另一个校区
bool shoolBusOrBus;//去另一个校区的方式
bool alreadyChosen = 0;//是否已经选择了去另一个校区的方式
QString currentSite;//用户当前所在物理位置
QStringList buildingList;//自动补全使用
