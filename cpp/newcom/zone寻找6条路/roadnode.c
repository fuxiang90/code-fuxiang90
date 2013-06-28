
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"

//创建roadnode数组
int create_roadnode_arr( )
{
    arr_proadnode = (giroadnode **)malloc(MAX_ROADNODE * sizeof(giroadnode *));  //为动态数组分配空间

   	memset((void *)arr_proadnode, 0, MAX_ROADNODE * sizeof(giroadnode *));    //对数组清零，初始化为NULL

	return 0;
}

//创建keynode节点，并挂接在keynode数组keynode_arr上面
int init_roadnode(int *pn)  //pn为了传给主调函数记录条数
{
	FILE * fp = NULL;
	int i=0;                         //记录数初始为0，以后每读一条记录，i 增加 1，最后赋值给(*pn)
    int rid, id, orid;               //rid记录当前点所属路的id，orid记录上一条路的roadid
	double x, y;
	double dist;
	giroadnode **arr_p = arr_proadnode;
	giroad **pproad = arr_proad;
            
	fp = fopen(ROADNODE_FILE, "r");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", ROADNODE_FILE);
		exit(-1);
	}

	orid = 1;   //orid从1开始，要求road从1开始，roadnode第一行也从roadid=1的地方开始，这样循环处理方便
	pproad[orid]->child[0] = 1;
	while(i < MAX_ROADNODE)                    //从文件中读取一行，创建一个节点，并给节点赋值
	{
		if(fscanf(fp, "%d%lf%lf%lf%d", &rid, &x, &y, &dist, &id) != EOF)  //若读到文件结尾则跳出循环
		{
			i++;
			// id=i 且连续，不存在重复，因此用id作为下标不回出现覆盖的情况，但要求 MAX_ROADNODE > id，否则会越界
		    arr_p[id] = (giroadnode *)malloc(sizeof(giroadnode));    //创建节点
		    arr_p[id]->roadid = rid;                               //为节点赋值
		    arr_p[id]->x = x;
		    arr_p[id]->y = y;
			arr_p[id]->dist = dist;
		    arr_p[id]->id = id;

			//处理
			if(rid != orid)
			{
			    pproad[orid]->child[1] = id-1;  //这里要求了id必须连续
				pproad[rid]->child[0] = id;
				orid = rid;
			}
		}
		else         //文件结束直接跳出循环即可，在创建动态数组时，已经初始化为NULL了，不存在出现野指针的情况
		{
		    break;
		}
	}

    pproad[rid]->child[1] = id;
	(*pn) = i;   //必须将记录条数 i 存到(*pn)里才能传给主函数
	fclose(fp);
	printf("已向地图中添加的roadnode记录%d条\n\n", i);
	return 0;
}

//释放roadnode节点，并置空roadnode数组
int clear_roadnode(int num)
{
    int i=0, n=0;
	giroadnode **arr_p = arr_proadnode;

	while( n< num )
	{
		i++;                    //arr_p[i]为NULL时，也自增，以追赶id
		if(arr_p[i])            //先自增i，然后若arr_p[i]为NULL，直接进行下次循环，不为NULL说明i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
			n++;                //每释放一条记录，n+1
		}
	}

	printf("释放roadnode记录%d条\n\n", n);//打印出记录条数和最大id
	return 0;
}

//释放roadnode数组，一定要在释放giroadnode节点后释放，否则就丢了
int del_roadnode(int num)
{
	clear_roadnode(num);           //先清除挂在数组上的节点
	free(arr_proadnode);
	arr_proadnode = NULL;                      //传3级指针就是为了这句话
	return 0;
}

