#ifndef BUSROADMATCH_H_INCLUDED
#define BUSROADMATCH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "common.h"
#include "road.h"
#include "node.h"
#include "init.h"
#include "roadnode.h"
#include "function.h"
#include "aim.h"
#include "stop.h"
#include "bat_func.h"
#include "zone.h"

#include "CSlist.h"
#include <vector>


// This file  write by fuxiang
// Thanks Shi Song


typedef struct BusRoad_t BusRoad;
struct BusRoad_t
{
    int roadseq ;
    int roadid;
    //std::vector<int > road_node_vec;
    CSlist * road_node_slist;

};


struct list_t{
    int roadnode_id;
};




//初始化
void bus_road_mathch_init();
//输入
void bus_road_match_input();

void bus_road_match_show();


void bus_road_match_work();

void bus_road_match_free();



static  void Print(CSlist * l) ;

//偏移下 Cslist 里面第一个 和最后一个点的坐标
static void get_delta_x_y(CSlistNode * first_node , CSlistNode * end_node ,double * dx ,double *dy ,int flag  );
//得到一个数组中出现次数最多的数字
static int get_max_times(int * arr ,int len,int * times);

int  int_cmp(const void * a ,const void * b);

void bus_road_match_testmain();

#endif // BUSROADMATCH_H_INCLUDED
