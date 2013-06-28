
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"

//创建node数组
int create_keynode_arr()
{
    arr_pkeynode = (gikeynode **)malloc(MAX_KEYNODE * sizeof(gikeynode *));  //为动态数组分配空间
    
   	memset((void *)arr_pkeynode, 0, MAX_KEYNODE * sizeof(gikeynode *));    //对数组清零，初始化为NULL
	
	return 0;
}

//创建keynode节点，并挂接在keynode数组keynode_arr上面
int init_keynode(int *pn)  //pn为了传给主调函数记录条数
{
	gikeynode **arr_p = arr_pkeynode;
	FILE * fp = NULL;
	int i=0;                         //记录数初始为0，以后每读一条记录，i 增加 1，最后赋值给(*pn)
    int id;
	double x, y;
            
	fp = fopen(KEYNODE_FILE, "r");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", KEYNODE_FILE);
		exit(-1);
	}

	while(i < MAX_KEYNODE)                    //从文件中读取一行，创建一个节点，并给节点赋值
	{
		if(fscanf(fp, "%d%lf%lf", &id, &x, &y) != EOF)  //若读到文件结尾则跳出循环
		{
			i++;
			// id 不存在重复，因此用id作为下标不回出现覆盖的情况，但是这里要求 MAX_KNODE > id，否则会越界
		    arr_p[id] = (gikeynode *)malloc(sizeof(gikeynode));    //创建节点
		    arr_p[id]->id = id;                                    //为节点赋值
		    arr_p[id]->x = x;
		    arr_p[id]->y = y;
		    arr_p[id]->n_out = 0;
		    arr_p[id]->n_in = 0; 
			memset(arr_p[id]->road_out, 0, MAX_AROUND*sizeof(int));
			memset(arr_p[id]->road_in, 0, MAX_AROUND*sizeof(int));//对数组清零
		}
		else         //文件结束直接跳出循环即可，在创建动态数组时，已经初始化为NULL了，不存在出现野指针的情况
		{
		    break;
		}
	}

	(*pn) = i;   //必须将记录条数 i 存到(*pn)里才能传给主函数
	fclose(fp);
	printf("读取keynode记录条数及id：\n%d    %d\n", i, id);
	return 0;
}

//释放keynode节点，并置空keynode数组
int clear_keynode(int num)
{
    int i=0, n=0;
    gikeynode **arr_p = arr_pkeynode;

	while( n< num )
	{
		i++;                    //arr_p[i]为NULL时，也自增，以追赶id
		if(arr_p[i])           //先自增i，然后若arr_p[i]为NULL，直接进行下次循环，不为NULL说明i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
			n++;               //每释放一条记录，n+1
		}
	}

	printf("释放keynode记录%d条\n\n", n);//打印出记录条数和最大id
	return 0;
}

//释放keynode数组，一定要在释放gikeynode节点后释放，否则就丢了
int del_keynode(int num)
{
	clear_keynode(num);           //先清除挂在数组上的节点
	free(arr_pkeynode);
	arr_pkeynode = NULL;                      //传3级指针就是为了这句话
	return 0;
}

