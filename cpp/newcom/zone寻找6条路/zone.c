
#include <string.h>   //memset
#include <malloc.h>   //malloc
#include <stdio.h>    //printf
#include <stdlib.h>   //exit

#include "common.h"
#include "config.h"
#include "head.h"     //导入全局变量
#include "function.h" //使用了里面的函数 get_nearest_dis(int id, double x, double y)

/*
(112.880062, 22.496958)---(114.130185, 23.997482)
(112.90, 22.50)---(114.15, 24.00)
梯度分别为0.025 * 0.03，大概是,50*50
*/

typedef struct near_road            //本结构用于记录点到roadid的距离，事实上，dis为角度计算结果
{                   
    int roadid;
	double dis;
}road_dis;

static double rootx = MIN_X;
static double rooty = MIN_Y;
static double dx = DX;
static double dy = DY;
static road_dis arr_near_road[ZONE_NEAR+1];    //存放最近的4条路,0用作哨兵，不能使用

//初始化最近的4条路
static int init_near_road()
{
	int i=0;
	while(i<ZONE_NEAR+1)
	{
        arr_near_road[i].roadid = 0;
        arr_near_road[i].dis = 999.0;
		i++;
	}
	return 0;
}

//根据road来初始化zone
int init_zone(int num)//传入的是road的数目
{
    int i=0, n=0;     //都用于road
    int start, end;   //用于roadnode
	int index;            //用于zone
	double x, y;

	memset((void *)arr_pzone, 0, ZONE_NUM * sizeof(gizone *));    //对数组清零，初始化为NULL

	while( n< num )   //保证计算完所有路
	{
		i++;
		if(arr_proad[i])   //即使roadid不连续，也不怕
		{
			int old_index = -1;
			start = arr_proad[i]->child[0];
			end = arr_proad[i]->child[1];
			while(start <= end) //在此初始化zone
			{
				x = arr_proadnode[start]->x - rootx;
				y = arr_proadnode[start]->y - rooty;
				index = 50 * (int)(x/dx) + (int)(y/dy);        //计算属于哪个区域

				if(NULL == arr_pzone[index])               //若还未分配空间，则分配空间
				{
				    arr_pzone[index] = (gizone *)malloc(sizeof(gizone));
					memset((void *)arr_pzone[index]->road, 0, ZONE_NUM * sizeof(int));
                    arr_pzone[index]->road[0] = 0;         //初始时有0条路
				}
                //若接下来的点仍然属于这个区域，则不再添加，这样减少了重复，但并未消除，拐弯的情况仍可能有重复
				if(index != old_index)
				{
					arr_pzone[index]->road[arr_pzone[index]->road[0]+1] = arr_proadnode[start]->roadid;
				    arr_pzone[index]->road[0]++;
				    old_index = index;
				}

				start++;
			}
			n++;           //road计数加一
		}
	}
	return 0;
}

//释放zone相关节点
int del_zone()
{
    int i=0;
	while( i< ZONE_NUM )
	{
		if(arr_pzone[i])           //先自增i，然后若arr_p[i]为NULL，直接进行下次循环，不为NULL说明i=id
		{
			free(arr_pzone[i]);
		    arr_pzone[i] = NULL;
		}
		i++;
	}
	return 0;
}

//将每个zone内的road数目写入文件
int show_zone_con()
{
	FILE * fp = NULL;
    int i=0;
 
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}
	while( i<ZONE_NUM )
	{
		if(arr_pzone[i])
		{
	        fprintf(fp, "%d\t%d\n", i, arr_pzone[i]->road[0]);
		}
		i++;
	}
	fclose(fp);
	printf("zone内容统计已写入%s\n\n", RESULT_FILE);
	return 0;
}


//得到区域内最近的n条路的id
int get_zone_road(double x, double y)
{
	int i=1;
	int si;           //用于sort的i
	double temp;      //临时存放距离
	int zone_roadid;  //临时存放roadid
	int index = 50 * (int)((x-rootx)/dx) + (int)((y-rooty)/dy);

	if(index >= ZONE_NUM)
	{
	    printf("该点不在本地图范围内\n");
		exit(-1);
	}

    init_near_road();   //将最近的ZONE_NEAR条路初始化

    while(i<=arr_pzone[index]->road[0])
	{
		zone_roadid = arr_pzone[index]->road[i];
	    temp = get_nearest_dis(zone_roadid, x, y);

		//伪插入排序，将比temp大的road往后移动
		if(temp<arr_near_road[ZONE_NEAR].dis)
		{
		    arr_near_road[0].roadid = zone_roadid;                  //哨兵
		    arr_near_road[0].dis = temp;
	        for(si=ZONE_NEAR-1; temp<arr_near_road[si].dis; si--)   //si=0时，肯定会跳出循环
		    {
		    	arr_near_road[si+1].roadid = arr_near_road[si].roadid;
		    	arr_near_road[si+1].dis = arr_near_road[si].dis;
		    }
		    arr_near_road[si+1].roadid = arr_near_road[0].roadid;
		    arr_near_road[si+1].dis = arr_near_road[0].dis;
		}

		i++;
	}
	return 0;
}

//打印最近的road
static int print_near_road()
{
    int i;
	for(i=1; i<=ZONE_NEAR+1 && arr_near_road[i].roadid !=0; i++)
	{
	    printf("%8d, %lf\n", arr_near_road[i].roadid, arr_near_road[i].dis);
	}
	return 0;
}
int test_zone()
{
	double x, y;

    printf("请输入坐标（xy用空格隔开,x=0.0退出）：");
    scanf("%lf %lf", &x, &y);
	while(x!=0.0)
	{
		get_zone_road(x, y);
		print_near_road();

	    printf("请输入坐标（xy用空格隔开,x=0.0退出）：");
        scanf("%lf %lf", &x, &y);
	}

	return 0;
}