
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"


//创建busstop数组
int create_stop_arr()
{
    arr_pstop = (busstop **)malloc(MAX_STOP * sizeof(busstop *));  //为动态数组分配空间

   	memset((void *)arr_pstop, 0, MAX_STOP * sizeof(busstop *));    //对数组清零，初始化为NULL

	return 0;
}

//创建道路节点，并挂接在道路数组road_arr上面
int init_stop(int *pn, char *filename)  //pn为了传给主调函数记录条数
{
	busstop **arr_p = arr_pstop;
	FILE * fp = NULL;
	int i=0;                         //记录数初始为0，以后每读一条记录，i 增加 1，最后赋值给(*pn)
    int id;
	double x, y;
            
	fp = fopen(filename, "r");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", filename);
		exit(-1);
	}
	while(i < MAX_STOP)                    //从文件中读取一行，创建一个节点，并给节点赋值
	{
		if(fscanf(fp, "%d%lf%lf", &id, &x, &y) != EOF)  //若读到文件结尾则跳出循环
		{
			i++;         //0没有使用
		    arr_p[i] = (busstop *)malloc(sizeof(busstop));           //创建节点
		    arr_p[i]->id = id;                                       //为节点赋值
			arr_p[i]->x = x;
		    arr_p[i]->y = y;
		}
		else         //文件结束直接跳出循环即可，在创建动态数组时，已经初始化为NULL了，不存在出现野指针的情况
		{
		    break;
		}
	}

	(*pn) = i;   //必须将记录条数 i 存到(*pn)里才能传给主函数
	fclose(fp);
//	printf("读取 %d 条busstop记录\n", i);
	return 0;
}

//释放道路节点，并置空道路数组
int clear_stop(int num)
{
	busstop **arr_p = arr_pstop;
    int i=0, n=0;
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
	return 0;
}

int del_stop(int num)
{
	clear_stop(num);            //先清除挂在数组上的节点
	free(arr_pstop);
	arr_pstop = NULL;                    //传3级指针就是为了这句话
	return 0;
}

//将站点计算后的信息写入文件
int show_stop()
{
	busstop **arr_p = arr_pstop;
	FILE * fp = NULL;
    int i=1;        //站点是从1开始的
 
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}
	while(arr_p[i])
	{
		fprintf(fp, "%-4d%-8d%-8d (%lf,%lf)(%lf,%lf)(%lf,%lf,%lf)\n", arr_p[i]->id, arr_p[i]->roadid, arr_p[i]->roadnodeid, arr_p[i]->x, arr_p[i]->y, arr_p[i]->vx, arr_p[i]->vy, arr_p[i]->Flen, arr_p[i]->Tlen, arr_p[i]->high);
		i++;
	}
	fclose(fp);
	printf("站点已写入%s\n\n", RESULT_FILE);
	return 0;
}

//将站点计算后的信息写入文件，将Flen+Tlen与road的长度作对比
int check_stop()
{
	FILE * fp = NULL;
    int i=1;        //站点是从1开始的
 
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}
	while(arr_pstop[i])
	{
		fprintf(fp, "%-4d%-8d%-8d (%lf,%lf)\n", arr_pstop[i]->id, arr_pstop[i]->roadid, arr_pstop[i]->roadnodeid, arr_pstop[i]->Flen+arr_pstop[i]->Tlen, arr_proad[arr_pstop[i]->roadid]->length);
		i++;
	}
	fclose(fp);
	printf("站点检查数据已写入%s\n\n", RESULT_FILE);
	return 0;
}
