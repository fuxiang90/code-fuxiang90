
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"

//创建zroad数组
int create_zroad_arr( )
{
    arr_pzroad = (gzroad **)malloc(MAX_AIMROAD * sizeof(gzroad *));  //为动态数组分配空间

   	memset((void *)arr_pzroad, 0, MAX_AIMROAD * sizeof(gzroad *));    //对数组清零，初始化为NULL
	return 0;
}

//创建znode数组
int create_znode_arr( )
{
	//这里使用了MAX_KEYNODE，空间浪费比较严重，但是在查找时，可以随机查找
    arr_pznode = (gznode **)malloc(MAX_KEYNODE * sizeof(gznode *));      //为动态数组分配空间

   	memset((void *)arr_pznode, 0, MAX_KEYNODE * sizeof(gznode *));    //对数组清零，初始化为NULL
	return 0;
}

//创建道路节点，并挂接在道路数组aimroad_arr上面
int init_aimroad(int *pn, char *filename)    //pn为了传给主调函数记录条数
{
	gzroad **arr_r = arr_pzroad;
	gznode **arr_n = arr_pznode;
	FILE * fp = NULL;
	int i=0;                           //记录数初始为0，以后每读一条记录，i 增加 1，最后赋值给(*pn)
    int id, startid, endid;
	int count=0;

	fp = fopen(filename, "r");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", filename);
		exit(-1);
	}
	while(i < MAX_AIMROAD)                    //从文件中读取一行，创建一个节点，并给节点赋值
	{
		if(fscanf(fp, "%d%d%d", &id, &startid, &endid) != EOF)  //若读到文件结尾则跳出循环
		{
			//初始化zroad，i也是从1开始的
			i++;
		    arr_r[i] = (gzroad *)malloc(sizeof(gzroad));          //创建节点
		    arr_r[i]->id = id;                                    //为节点赋值
		    arr_r[i]->startid = startid;
		    arr_r[i]->endid = endid;

			//初始化znode
			if(NULL == arr_n[startid])
			{
			    arr_n[startid] = (gznode *)malloc(sizeof(gznode));
                arr_n[startid]->id = startid;
				arr_n[startid]->next_road = 0;
				arr_n[startid]->prev_road = 0;
			}
			if(NULL == arr_n[endid])
			{
			    arr_n[endid] = (gznode *)malloc(sizeof(gznode));
                arr_n[endid]->id = endid;
				arr_n[endid]->next_road = 0;
				arr_n[endid]->prev_road = 0;
			}
			if(0 == arr_n[startid]->next_road)                //起点记录下后面的路
			{
			    arr_n[startid]->next_road = id;
			}
			if(0 == arr_n[endid]->prev_road)                  //终点记录下前面的路
			{
			    arr_n[endid]->prev_road = id;
				count++;
			}
		}
		else         //文件结束直接跳出循环即可，在创建动态数组时，已经初始化为NULL了，不存在出现野指针的情况
		{
		    break;
		}
	}
	fclose(fp);
	(*pn) = i;     //必须将记录条数 i 存到(*pn)里才能传给主函数
	printf("目标路段初始化完成\n");
	return 0;
}

//释放道路节点，并置空道路数组
int clear_zroad(int num)
{
	gzroad **arr_p = arr_pzroad;
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

//	printf("释放zroad记录条数以及id：\n%d    %d\n", n, i);//打印出记录条数和最大id
	return 0;
}

//释放znode节点，并置空znode数组
int clear_znode()
{
	gznode **arr_p = arr_pznode;
    int i=1;

	while( i< MAX_KEYNODE )
	{
		if(arr_p[i])           //先自增i，然后若arr_p[i]为NULL，直接进行下次循环，不为NULL说明i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
		}
		i++;                    //arr_p[i]为NULL时，也自增，以追赶id
	}
	return 0;
}

//释放zroad数组，释放zroad数组一定要在释放gzroad节点后释放，否则就丢了
int del_zroad(int num)
{
	clear_zroad(num);            //先清除挂在数组上的节点
	free(arr_pzroad);
	arr_pzroad = NULL;                    //传3级指针就是为了这句话
	return 0;
}

//释放znode数组，一定要在释放gznode节点后释放，否则就丢了
int del_znode()
{
	clear_znode();           //先清除挂在数组上的节点
	free(arr_pznode);
	arr_pznode = NULL;                      //传3级指针就是为了这句话
	return 0;
}

int create_aimroad_arr()
{
    create_zroad_arr();
    create_znode_arr();
	return 0;
}
int del_aimroad(int num)
{
    del_zroad(num);
	del_znode();
	return 0;
}
//得到起始点
int get_road_start()
{
	gznode **ppznode = arr_pznode;
    int i=1;
	int count = 0;
	int id=0;
	while( i<MAX_KEYNODE )
	{
	    if(ppznode[i] && 0==ppznode[i]->prev_road)
		{
		    count++;
			id = i;
		}
		i++;
	}
	if(count < 1)
	{
	    printf("无入度为0的点，道路可能存在环路\n");
		exit(-1);
	}
	else if(count > 1)
	{
	    printf("有%d个入度为0的点，道路存在断路\n", count); //排序中显示的是最后一断路，但是sort函数里面就会出错了
		exit(-1);
	}
	return id;
}
//将无序路段排序
int sort_aimroad()
{
    int start;
	int roadid;
	int i=1;

	start = get_road_start();                 //得到起始点
	roadid = arr_pznode[start]->next_road;              //起始路

	while(roadid)
	{
		arr_pzroad[i]->id = roadid;            //id
        arr_pzroad[i]->startid = start;        //startid
		start = arr_proad[roadid]->endid;      //start已经改变
		arr_pzroad[i]->endid = start;          //endid
		roadid = arr_pznode[start]->next_road;    //后移
		i++;
	}
    printf("已对%d条路段完成排序\n\n", i-1);
	return 0;
}
//将排序好的路写入文件
int show_aimroad()
{
	gzroad **arr_p = arr_pzroad;
	FILE * fp = NULL;
    int i=1;

	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}
	while(arr_p[i])
	{
	    fprintf(fp, "%8d%8d%8d\n", arr_p[i]->id, arr_p[i]->startid, arr_p[i]->endid);
		i++;
	}
	fclose(fp);
	printf("排序结果已写入%s\n\n", RESULT_FILE);
	return 0;
}

//此方法是根据znode输出的排序
int show_aimroad2( )
{
	gzroad **arr_p = arr_pzroad;
	gznode **ppznode = arr_pznode;
	FILE * fp = NULL;
    int start;
	int roadid;

	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}
	//start = get_road_start(ppznode);
	start = get_road_start();

	roadid = ppznode[start]->next_road;
	while(roadid)
	{
	    fprintf(fp, "%8d%8d%8d\n", roadid, start, arr_p[roadid]->endid);
		start = arr_p[roadid]->endid;
		roadid = ppznode[start]->next_road;
	}
	fclose(fp);
	printf("排序结果已写入%s\n\n", RESULT_FILE);
	return 0;
}
