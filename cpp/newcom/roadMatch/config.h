#ifndef CONFIG_H
#define CONFIG_H


//#define CHOICE


//预定义

//查找专用
#define MAX_AIMROAD  200           //待排序的路段数一定要小于 MAX_AIMROAD-1
#define MAX_STOP     100           //给出的aimroad上的站点小于MAXSTOP-1

//经纬度转换成距离的参数
#define PRE_LON      102266.5      //经度，对应x
#define PRE_LAN      111191.67     //纬度，对应y
//地图专用
#define MAX_ROAD     730000//730000        //MAX_ROAD 大于 road_id，若id不连续，则会产生浪费，在创建节点的时候会明显看出
#define MAX_KEYNODE  320000//320000//165000        //关键点
#define MAX_ROADNODE 4800000  //4800000    //2881000   //普通点，很多很多。。

//zone参数
// 最后这个不要写死 ，不然还得先运行你的脚本
//不然下面的参数很多都得该
#define MIN_X        112.30//112.90
#define MIN_Y        22.50 //
#define MAX_X        114.4 //
#define MAX_Y        23.95  //
#define ZONE_NEAR    6             //每个zone里找出最近的4条路
#define ZONE_NUM     2500          //zone的数量
//#define DX           0.025         //每个zone的梯度，这样可分为50*50=2500个区域
//#define DY           0.03
extern double DX ;
extern double DY ;

//输入的文件
#ifndef CHOICE
#define ROAD_FILE          "../giroad.txt"        //定义road节点文件的位置，用于程序从中读取giroad数据
#define KEYNODE_FILE       "../ginode.txt"        //定义node节点文件的位置，用于程序从中读取ginode数据
#define ROADNODE_FILE      "../giroadnode.txt"    //定义roadnode节点文件的位置，用于程序从中读取giroadnode数据

#else
#define ROAD_FILE          "../roadid_GIROAD.txt"        //定义road节点文件的位置，用于程序从中读取giroad数据
#define KEYNODE_FILE       "../roadid_GINODE.txt"        //定义node节点文件的位置，用于程序从中读取ginode数据
#define ROADNODE_FILE      "../roadid_GIROADNODE.txt"    //定义roadnode节点文件的位置，用于程序从中读取giroadnode数据
#endif

//处理的文件
#define AIM_FILE           "../gzroad.txt"
#define STOP_FILE          "../stop.txt"
#define RESULT_FILE        "../result.txt"

#define LINES_FILE         "../lines.txt"
#define PATH_FILE          "../path.txt"

#endif
