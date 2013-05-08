
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"


//#define CHOICE
//创建road数组
int create_road_arr()
{
    arr_proad = (giroad **)malloc(MAX_ROAD * sizeof(giroad *));  //为动态数组分配空间

   	memset((void *)arr_proad, 0, MAX_ROAD * sizeof(giroad *));    //对数组清零，初始化为NULL

	return 0;
}

//创建道路节点，并挂接在道路数组road_arr上面
int init_road(int *pn)  //pn为了传给主调函数记录条数
{
	giroad **arr_p = arr_proad;
	FILE * fp = NULL;
	int i=0;                         //记录数初始为0，以后每读一条记录，i 增加 1，最后赋值给(*pn)
    int id, startid, endid;
	double length;
	#ifdef CHOICE
	int roadid;
	#endif
    arr_p = arr_proad;

	fp = fopen(ROAD_FILE, "r");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", ROAD_FILE);
		exit(-1);
	}

	while(i < MAX_ROAD)                    //从文件中读取一行，创建一个节点，并给节点赋值
	{
        // 这次的新文件没有 道路等级这个字段 ，所以 fscanf要改下

        #ifndef CHOICE
		if(fscanf(fp, "%d%d%d%lf", &id, &startid, &endid, &length) != EOF)//if(fscanf(fp, "%d%d%d%lf%*d", &id, &startid, &endid, &length) != EOF)  //若读到文件结尾则跳出循环
		#else
        if(fscanf(fp, "%d%d%d%lf%d", &id, &startid, &endid, &length,&roadid) != EOF)
		#endif
		{
			i++;
			// id 不存在重复，因此用id作为下标不回出现覆盖的情况，但是这里要求 MAX_ROAD > id，否则会越界
		    arr_p[id] = (giroad *)malloc(sizeof(giroad));          //创建节点
		    arr_p[id]->id = id;                                    //为节点赋值
		    arr_p[id]->length = length;
		    arr_p[id]->startid = startid;
		    arr_p[id]->endid = endid;
			arr_p[id]->child[0] = 0;
			arr_p[id]->child[1] = 0;

			#ifdef CHOICE
			arr_p[id]->roadid = roadid;
			#endif
		}
		else         //文件结束直接跳出循环即可，在创建动态数组时，已经初始化为NULL了，不存在出现野指针的情况
		{
		    break;
		}
	}

	(*pn) = i;   //必须将记录条数 i 存到(*pn)里才能传给主函数
	fclose(fp);
	printf("读取road记录条数及id：\n%d    %d\n", i, id);
	return 0;
}

//释放道路节点，并置空道路数组
int clear_road(int num)
{
    int i=0, n=0;
	giroad **arr_p = arr_proad;
	while( n< num )
	{
		i++;                   //arr_p[i]为NULL时，也自增，以追赶id
		if(arr_p[i])           //先自增i，然后若arr_p[i]为NULL，直接进行下次循环，不为NULL说明i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
			n++;               //每释放一条记录，n+1
		}
	}

	printf("释放road记录%d条\n\n", n);//打印出记录条数和最大id
	return 0;
}

//释放road数组，释放road数组一定要在释放giroad节点后释放，否则就丢了
int del_road(int num)
{
	clear_road(num);            //先清除挂在数组上的节点
	free(arr_proad);
	arr_proad = NULL;                    //传3级指针就是为了这句话
	return 0;
}
