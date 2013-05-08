#ifndef COMMON_H
#define COMMON_H

#include "config.h"

//#define CHOICE
#define MAX_AROUND 10              //一个路口有几条路，双向路算2条
#define ZONE_CON     10000          //zone的容量

/***********************************整个地图的相关结构定义************************************/
//普通节点
typedef struct roadnode
{
    int id;                     //node_id 唯一，0不使用，id与下标一致且必须连续
	double x;                    //节点坐标
	double y;
	double dist;              //距离前一个节点的距离
	int roadid;               //记录所属道路的id
}giroadnode;

//关键节点
typedef struct keynode
{
    int id;                     //keynode_id 唯一，0不使用，id与下标一致，但id不连续
	double x;                    //节点坐标
	double y;

    int n_out;                  //节点的出度数，双向的路有一个出度一个入度
	int n_in;
    int road_out[MAX_AROUND]; //记录每条路的id
    int road_in[MAX_AROUND]; //记录每条路的id
}gikeynode;

//道路
typedef struct road
{
    int id;                     //road_id 唯一，0不使用，id与下标一致，且id连续
    double length;               //道路长度

	int startid;                //起始节点id
	int endid;                  //终止节点id
	int child[2];               //起始的roadnode的id，0为开头1为结束
#ifdef CHOICE
	int roadid ;                //合并道路的逻辑id 交换格式特有
#endif
}giroad;

//分区
typedef struct zone
{
    int road[ZONE_CON];             //用于记录本zone中全部的road，下标0里记录road的数目，main中的数组从0开始
}gizone;
/***********************************一条路的结构定义************************************/

//目标节点
typedef struct znode
{
    int id;
    int next_road;                 //该节点接下来的一段路的roadid
    int prev_road;                 //该节点前一段路的roadid
}gznode;

//目标道路
typedef struct zroad
{
    int id;                     //road_id 唯一
	int startid;                //起始节点id，是keynode
	int endid;                  //终止节点id
}gzroad;
/***********************************公交车站结构定义************************************/
typedef struct stop
{
	int id;
	int roadid;
	int roadnodeid;
	double x;
	double y;
	double vx;    //垂直映射点坐标
	double vy;
	double Flen;     //距前面keynode的距离
	double Tlen;
	double Flittle;  //距离前面roadnode的距离
	double Tlittle;
	double high;     //距垂点的距离
}busstop;

/***********************************定义结束************************************/
#endif
