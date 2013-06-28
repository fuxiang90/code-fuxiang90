
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

//定义成全局变量吧
	//地图
    giroad **arr_proad = NULL;                        //动态数组的指针，arr_proad[1]指向road_id为1的giroad
    gikeynode **arr_pkeynode = NULL;                  //动态数组的指针，arr_pkeynode[1]指向keynode_id为1的gikeynode
    giroadnode **arr_proadnode = NULL;                //roadnode数组的指针
	gizone *arr_pzone[ZONE_NUM];                      //地图分区，初始化钱先清零

    //目标路段
    gzroad **arr_pzroad = NULL;
	gznode **arr_pznode = NULL; 
	//公交站点
	busstop **arr_pstop = NULL;

int main(void)
{
	//地图
	int road_num;                              //记录实际从文件中读取了几条road记录
	int keynode_num;                           //记录实际从文件中读取了几条node记录
	int roadnode_num;                          //roadnode数量


	//创建地图
	create_road_arr();               //为road动态数组分配空间，并赋初值NULL
	create_keynode_arr();            //为road动态数组分配空间，并赋初值NULL
	init_road(&road_num);            //从文件中读取道路信息，初始化数组，指向giroad节点
	init_keynode(&keynode_num);      //从文件中读取道路信息，初始化数组，指向giroad节点

	init_map();                      //初始化地图，无roadnode
	printf("正在向地图中添加roadnode节点...\n");
    create_roadnode_arr();           //向地图中添加roadnode节点
	init_roadnode(&roadnode_num);
    printf("正在划分区域...\n");
    init_zone(road_num);    //传入的为road的数量

	//show_zone_con();
    test_zone();

	//释放地图内存
	del_zone();
	del_road(road_num);
	del_keynode(keynode_num);
	del_roadnode(roadnode_num);

	return 0;
}

//先前的主函数
int stopmain(void)
{
	//地图
	int road_num;                              //记录实际从文件中读取了几条road记录
	int keynode_num;                           //记录实际从文件中读取了几条node记录
	int roadnode_num;                          //roadnode数量


	//创建地图
	create_road_arr();               //为road动态数组分配空间，并赋初值NULL
	create_keynode_arr();            //为road动态数组分配空间，并赋初值NULL
	init_road(&road_num);           //从文件中读取道路信息，初始化数组，指向giroad节点
	init_keynode(&keynode_num);     //从文件中读取道路信息，初始化数组，指向giroad节点

	//初始化地图
	init_map();

	printf("正在向地图中添加roadnode节点...\n");
    //向地图中添加roadnode节点
    create_roadnode_arr();
	init_roadnode(&roadnode_num);


	//目标路段和站点
    create_aimroad_arr();
	create_stop_arr();
    
	//所有的都在这里了
    save_lines();
    

	//释放目标路段内存
    free(arr_pzroad);
    free(arr_pznode);
    free(arr_pstop);
	arr_pzroad = NULL;
	arr_pznode = NULL;
	arr_pstop = NULL;

	//释放地图内存
	del_road(road_num);
	del_keynode(keynode_num);
	//roadnode
	del_roadnode(roadnode_num);

	return 0;
}

//批处理之前的主函数
int xxxmain(void)
{
	//地图
	int road_num;                              //记录实际从文件中读取了几条road记录
	int keynode_num;                           //记录实际从文件中读取了几条node记录
	int roadnode_num;                          //roadnode数量

	//目标路段
	int zroad_num;
	int stop_num;

	//创建地图
	create_road_arr();               //为road动态数组分配空间，并赋初值NULL
	create_keynode_arr();            //为road动态数组分配空间，并赋初值NULL
	init_road(&road_num);           //从文件中读取道路信息，初始化数组，指向giroad节点
	init_keynode(&keynode_num);     //从文件中读取道路信息，初始化数组，指向giroad节点

	//初始化地图
	init_map();
//	check_map();  //将结果保存在了文件中

	printf("正在向地图中添加roadnode节点...\n");
    //向地图中添加roadnode节点
    create_roadnode_arr();
	init_roadnode(&roadnode_num);


	//目标路段和站点
    create_aimroad_arr();
	create_stop_arr();
	//调用save_lines()时，只创建数组，不初始化结构，因为每条线路单独处理了
    init_aimroad(&zroad_num, AIM_FILE);
	init_stop(&stop_num, STOP_FILE); //站点坐标读入

	//排序
	sort_aimroad();
	//排好的道路放到文件中
	show_aimroad();
	//将最近道路，距离，最近点打印出来
//	test_nearest();
	//计算站点信息，所有属性保存在busstop结构中
	calc_stop();
    //将站点计算后的信息写入文件
//    show_stop();
    //将站点计算后的信息写入文件，将Flen+Tlen与road的长度作对比
//    check_stop();

    //打印出两个站点之间的roadnode,写入文件,是通过站点的id确定区间的
//	get_path(20001, 20018);

	//释放目标路段内存
    del_aimroad(zroad_num);
	//释放公交站
	del_stop(stop_num);

	//释放地图内存
	del_road(road_num);
	del_keynode(keynode_num);
	//roadnode
	del_roadnode(roadnode_num);

	return 0;
}