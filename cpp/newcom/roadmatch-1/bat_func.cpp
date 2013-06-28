
#include <stdlib.h>  //itoa(int value, char *string, int radix)，第三个参数为进制
#include <string.h>  //char *strcat(char *dest,char *src) 覆盖dest的结尾"\0"; memset
#include <malloc.h>   //malloc
#include <stdio.h>

#include "config.h"
#include "common.h"
#include "head.h"
#include "aim.h"
#include "stop.h"
#include "function.h"

//获得存放线路的文件名
char * get_roadfile_name(int line, int direction) //参数为线路和方向
{
    char *s = NULL;  //用于存放文件名
	char temp[10];

	s = (char *)malloc(128 * sizeof(char));  //一般文件名不会超过128个字符
	memset((void *)s, 0, 128 * sizeof(char));

	//拼接开始
	strcat(s, "./data/");//拼接前面的
    itoa(line, temp, 10);
	strcat(s, temp);//拼接线路
	strcat(s, "_");
	itoa(direction, temp, 10);
	strcat(s, temp);//拼接方向
	strcat(s, "_road.txt");

	return s;
}
//获得存放站点的文件名
char * get_stopfile_name(int line, int direction) //参数为线路和方向
{
    char *s = NULL;  //用于存放文件名
	char temp[10];

	s = (char *)malloc(128 * sizeof(char));  //一般文件名不会超过128个字符
	memset((void *)s, 0, 128 * sizeof(char));

	//拼接开始
	strcat(s, "./data/");//拼接前面的
    itoa(line, temp, 10);
	strcat(s, temp);//拼接线路
	strcat(s, "_");
	itoa(direction, temp, 10);
	strcat(s, temp);//拼接方向
	strcat(s, "_stop.txt");

	return s;
}
//输出start和end中间的roadnode，包括两头
int put_roadnode_path(FILE *fp,int line, int direction, int index, int *count, int start, int end)
{
	while(start <= end)
	{
		fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_proadnode[start]->x, arr_proadnode[start]->y, arr_proadnode[start]->dist, (*count));
	    start++;
		(*count)++;
	}
	return 0;
}
//输出到下一站点之间的roadnode，调用此函数必须保证index有下一站，即index+1不是null
int put_stop_path(int line, int direction, int count_stop)
{
	int index = count_stop;  //第几站，可以用做下表索引
	FILE * fp = NULL;
	int i = 1;
	int start, end;    //用于记录road1和road2的下表
    int road1, road2;
	int roadnode1, roadnode2;
	int temp;
	int count;  //用于记录输出了多少个roandode

	fp = fopen(PATH_FILE, "a+");  //以追加方式打开，这样就可以写入不相邻的站点之间路径
	if(!fp)
	{
	    printf("打开文件%s失败\n", PATH_FILE);
		exit(-1);
	}

	road1 = arr_pstop[index]->roadid;
	road2 = arr_pstop[index+1]->roadid;
	roadnode1 = arr_pstop[index]->roadnodeid;
	roadnode2 = arr_pstop[index+1]->roadnodeid;
	roadnode1++;  //得到的是站点之前的roadnode，因此先要+1

	//查找站点所在的道路，记录下标（已知id，查找下标）
	while(arr_pzroad[i])
	{
	    if(arr_pzroad[i]->id == road1)
		{
		    start = i;
		}
		if(arr_pzroad[i]->id == road2)
		{
		    end = i;
		}
		i++;
	}
	count = 0;
	//输出站点，0表示站点而不是roadnode
	fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_pstop[index]->vx, arr_pstop[index]->vy, 0.0, count);
	count++;
	//第一个roadnode于站点之间的距离，要单独打印
	fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_proadnode[roadnode1]->x, arr_proadnode[roadnode1]->y, arr_pstop[index]->Tlittle, count);
	count++;
	//顺序输出中间的roadnode
	if(start == end)    //车站在同一条路上，这种情况在实际中几乎不可能啊
	{//roadnode顶多等于roadnode2，busstop中的roadnode后面肯定至少还有一个roadnode，不会跑到另一条路的roadnode上
        //如果roadnode1 = roadnode2，则说明两站之间只有一个roadnode
		//仔细想想，在逻辑上，两个roadnode1>roadnode2也是有可能的，即两个站点间没有roadnode，但是现实中不太可能
		//若两站间只有1个roadnode，下面函数里就不会再打印了
		put_roadnode_path(fp, line, direction, count_stop, &count, roadnode1+1, roadnode2);
	}
	else if(start+1 == end)//下一站在下一条路上
	{
		//输出前半段
		temp = arr_proad[road1]->child[1];//roadnode+1顶多等于temp，busstop中的roadnode后面肯定至少还有一个roadnode
		put_roadnode_path(fp, line, direction, count_stop, &count, roadnode1+1, temp);
		//输出后半段
		temp = arr_proad[road2]->child[0];
		put_roadnode_path(fp, line, direction, count_stop, &count, temp+1, roadnode2);//temp+1是因为前半段已经输出过一次temp了
	}
	else    //两站之间隔着至少一条路
	{
		//输出前半段
		temp = arr_proad[road1]->child[1];//roadnode+1顶多等于temp，busstop中的roadnode后面肯定至少还有一个roadnode
		put_roadnode_path(fp, line, direction, count_stop, &count, roadnode1+1, temp);
		//输出中间的
		start++;
		end--;
		while(start <= end)
		{
			int node1, node2;
			temp = arr_pzroad[start]->id;      //temp记录道路的id
			node1 = arr_proad[temp]->child[0];
			node2 = arr_proad[temp]->child[1];
		    put_roadnode_path(fp, line, direction, count_stop, &count, node1+1, node2);
			start++;
		}
		//输出后半段
		temp = arr_proad[road2]->child[0];
		put_roadnode_path(fp, line, direction, count_stop, &count, temp+1, roadnode2);
	}
	//输出后面的站点
    fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_pstop[index]->vx, arr_pstop[index]->vy, arr_pstop[index]->Flittle, count);
	fclose(fp);
	return 0;
}
//保存单条指定的路线
int save_one_line(int line, int direction, int stop_num)
{
	int count_stop = 1;
    while(count_stop < stop_num)//从第一个站点到最后一个站点
	{
	    put_stop_path(line, direction, count_stop);//自动保存该站点到下一站点的路径
		count_stop++;
	}
    return 0;
}
//将lines里面的所有线路都记录下来
int save_lines()
{
    int line, direction;
	char *roadfile = NULL;
	char *stopfile = NULL;
	FILE * fp = NULL;
	int zroad_num, stop_num;

	fp = fopen(LINES_FILE, "r");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", LINES_FILE);
		exit(-1);
	}

	calear_result_file(PATH_FILE);

	while(fscanf(fp, "%d%d", &line, &direction) != EOF)
	{
		roadfile = get_roadfile_name(line, direction);
		stopfile = get_stopfile_name(line, direction);

        init_aimroad(&zroad_num, roadfile);
	    init_stop(&stop_num, stopfile);    //站点坐标读入
	    //排序
	    sort_aimroad();

        //把stop的信息计算出来
	    calc_stop();

        //记录单个线路
		save_one_line(line, direction, stop_num);

		//本次循环的善后处理
	    free(roadfile);//每次，文件名都重新分配空间，因此每次都要释放
		roadfile = NULL;
	    free(stopfile);
		stopfile = NULL;
		//释放挂接的节点，但数组没释放
	    clear_zroad(zroad_num);//这两个合起来算是aimroad
	    clear_znode();
		clear_stop(stop_num);
	}
	return 0;
}
