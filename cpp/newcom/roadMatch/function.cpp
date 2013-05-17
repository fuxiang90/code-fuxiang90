
#include <stdio.h>    //printf
#include <string.h>   //memcpy
#include <stdlib.h>   //exit
#include <math.h>

#include "config.h"
#include "common.h"
#include "head.h"


//两点距离
double dis(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2;
	double dy = y1 - y2;
    return sqrt(dx*dx+dy*dy);
}
double dis2(const giroadnode *u, const giroadnode *v)
{
	double dx = u->x - v->x;
	double dy = u->y - v->y;
    return sqrt(dx*dx+dy*dy);
}
//点到线段最近点
int p2seg(double x, double y, const giroadnode *a, const giroadnode *b, double *out_x, double *out_y)
{
	double vx, vy;
	double dotpv, dotav, dotvv;
	double t;
	double disa, disb;

	vx = b->x - a->x;                              //  向量v = ob -oa = ab
	vy = b->y - a->y;
	dotpv = x*vx + y*vy;                           //  dotab = |oa|*|ob|*cos<oa,ob>
	dotav = (vx * a->x) + (vy * a->y);
	dotvv = vx*vx + vy*vy;
                                          //用@表示点乘，推导一下公式，解释t的含义(向量v=ab)
	t = (dotpv - dotav)/dotvv;            //  (dotpv - dotav)/dotvv = (op@v - oa@v)/(v@v) = (ap@v)/(v@v)
	                                      // =(|ap|*|v|*cos<ap, ab>)/(|v|*|v|*cos0) = (|ap|*cos<ap,ab>)/|ab|
	                                      //因此，t是a到(ap在ab上的映射点)的长度所占ab长度的比例
	//0<t<1，p映射点在ab内
	//t>=1，则p映射点在ab之外(b侧)，可直接取b为最近点
	//t<=0，则p映射点在ab之外(a侧)，可直接取a为最近点，经测试，不一定<0就为a，所以还要算距离
    if(t>0 && t<1)
	{
		(*out_x) = a->x + t*vx;
		(*out_y) = a->y + t*vy;
	}
    else  //在外面，返回距离最近的端点坐标
	{
		disa = dis(x, y, a->x, a->y);
		disb = dis(x, y, b->x, b->y);
		if( disa < disb )
		{
		    (*out_x) = a->x;
		    (*out_y) = a->y;
		}
		else
		{
		    (*out_x) = b->x;
		    (*out_y) = b->y;
		}
	}
    return 0;
}

//点到线段距离
double dis2seg(double x, double y, const giroadnode *u, const giroadnode *v ,int flag = 1)
{
	double out_x, out_y, h;
	p2seg(x, y, u, v, &out_x, &out_y);
	if(flag == 1)
        h = dis(x, y, out_x, out_y);
    else { //计算真实的距离
        double delta_x = out_x - x;
        double delta_y = out_y - y;
        h = sqrt( delta_x*delta_x*PRE_LON*PRE_LON  + delta_y * delta_y*PRE_LAN*PRE_LAN );
    }
	return h;
}
//点到直线距离，垂线距离
double dis2line(double x, double y, const giroadnode *u, const giroadnode *v)
{
	double upx, upy, uvx, uvy;
	double det, a, h;
	upx = x - u->x;
	upy = y - u->y;
	uvx = v->x - u->x;
	uvy = v->y - u->y;
	det = upx*uvy - upy*uvx;        //叉乘的膜 |a X b| = |a|*|b|*sin<a,b>
	a = dis2(u, v);
	h = det/a;
	return h;
}

//求点到一条路段的最短距离
double get_dis(int start, int end, double x, double y)
{
	double dis = 361.0;  //默认为很大，经纬度不可能超过360度，具体到广州，10度都不能超过
	double temp;
	giroadnode **arr_p = arr_proadnode;

	while(start<end)
	{
	    temp = dis2seg(x, y, arr_p[start], arr_p[start+1]);
		if(temp<dis)        //还未找到最近距离，继续找
		{
		    dis = temp;
		}
		else        //temp>=dis，在这段路上不可能再找到更近的距离了
		{
		    break;
		}

		start++;
	}
	return dis;
}

//返回最近的roadid
int get_nearest_road(double x, double y)
{
	int rid = 0;        //真正最近路段id
	int start, end;     //每条路的起始点
	int road, i=1;
	double dis=361.0, temp;

	while(arr_pzroad[i])  //每条路都得查找
	{
		road = arr_pzroad[i]->id;                  //找到roadid
		start = arr_proad[road]->child[0];         //通过roadid找到roadnode起始和终止点
		end = arr_proad[road]->child[1];
		temp = get_dis(start, end, x, y);

		if(temp<dis)     //dis记录最小的
		{
		    dis = temp;
			rid = road;
		}
		i++;
	}
	return rid;
}

//返回最近的roadnodeid
int get_nearest_roadnode(int id, double x, double y)//输入roadid和坐标
{
	int start, end;
	double dis = 361.0;  //默认为很大，经纬度不可能超过360度，具体到广州，10度都不能超过
	double temp;
	int rnid;
	giroadnode **arr_p = arr_proadnode;

	start = arr_proad[id]->child[0];         //通过roadid找到roadnode起始和终止点
	end = arr_proad[id]->child[1];

	while(start<end)
	{
	    temp = dis2seg(x, y, arr_p[start], arr_p[start+1]);
		if(temp<dis)        //还未找到最近距离，继续找
		{
		    dis = temp;
			rnid = start;
		}
		else if(temp == dis)//特殊情况，start即为最近点
		{
			dis = temp;
			rnid = start;
		    break;
		}
		else //temp>dis由于最近点一定在此路上，所以这种情况一定是找过了，不会再有更近的了
		{
			break;
		}
		start++;
	}
   //arr_p[start]与arr_p[start+1]之间这条线段一定为最近点所在线段
	return rnid;
}
//返回最近距离，输入为roadid和坐标，该函数搜索全部的roadnode
double get_nearest_dis(int id, double x, double y)
{
	int start, end;
	double dis = 361.0;  //默认为很大，经纬度不可能超过360度，具体到广州，10度都不能超过
	double temp;
	giroadnode **arr_p = arr_proadnode;

	start = arr_proad[id]->child[0];         //通过roadid找到roadnode起始和终止点
	end = arr_proad[id]->child[1];

	while(start<end)
	{
	    temp = dis2seg(x, y, arr_p[start], arr_p[start+1]);
		if(temp<dis)        //还未找到最近距离，继续找
		{
		    dis = temp;
		}
		start++;
	}
	return dis;//其实这个距离是度数
}
//返回最近距离，最近点记录在输出参数中
double get_nearest_disp(int id, double x, double y, double *out_x, double *out_y)
{
	int start;
	double dis = 361.0;  //默认为很大，经纬度不可能超过360度，具体到广州，10度都不能超过
    giroadnode **arr_p = arr_proadnode;
	//得到最近的roadnodeid所在的那一段
	start = get_nearest_roadnode(id, x, y);
	//得到距离
    dis = dis2seg(x, y, arr_p[start], arr_p[start+1]);
	//arr_p[start]与arr_p[start+1]之间这条线段一定为最近点所在线段
    p2seg(x, y, arr_p[start], arr_p[start+1], out_x, out_y);
	return dis;
}


int test_nearest()
{
	double x[25] = {113.227693, 113.234002, 113.230949, 113.227019, 113.228430, 113.231181, 113.235514, 113.236328, 113.239500, 113.245320, 113.252683, 113.258463, 113.262370, 113.271151, 113.269449, 113.271397, 113.274796, 113.281278, 113.285652, 113.290680, 113.293741};
	double y[25] = {23.0753691, 23.0797583, 23.0830731, 23.0842873, 23.0882516, 23.0906670, 23.0977056, 23.0998087, 23.1084315, 23.1086726, 23.1075816, 23.1099606, 23.1116601, 23.1178795, 23.1200035, 23.1244151, 23.1265725, 23.1270391, 23.1267054, 23.1250276, 23.1237798};
	int i=0;
	double dis;
	int id;
	double out_x, out_y;

	for(i=0; i<21; i++)
	{
    	id = get_nearest_road(x[i], y[i]);
    	dis = get_nearest_disp(id, x[i], y[i], &out_x, &out_y);

    	printf("%-8d%-15lf   (%lf, %lf)\n", id, dis, out_x, out_y);
	}
	return 0;
}
//将坐标的距离转化为实际距离
double coordnate2dist(double x1, double y1, double x2, double y2)
{
    return sqrt( (y1-y2)*(y1-y2)*PRE_LAN*PRE_LAN + (x1-x2)*(x1-x2)*PRE_LON*PRE_LON );
}
//累加距离
double sum_dist(int start, int end)
{
	double sum = 0.0;
	giroadnode **arr_p = arr_proadnode;

	while(end>start)  //不要用start
	{
        sum += arr_p[end]->dist;
	    end--;
	}
	return sum;
}

//将距离等stop的相关信息写入结构
int calc_stop( )
{
    int i=1;
	double x, y;
	int roadid;
	int roadnodeid;
	double sum, little;
	while( arr_pstop[i] )
	{
		x = arr_pstop[i]->x;
		y = arr_pstop[i]->y;
		roadid = arr_pstop[i]->roadid = get_nearest_road(x, y);
		roadnodeid  = arr_pstop[i]->roadnodeid = get_nearest_roadnode(arr_pstop[i]->roadid, x, y);
		arr_pstop[i]->high = get_nearest_disp(arr_pstop[i]->roadid, x, y, &(arr_pstop[i]->vx), &(arr_pstop[i]->vy));

		sum = sum_dist(arr_proad[roadid]->child[0], roadnodeid); //前半段
		little = coordnate2dist(arr_pstop[i]->vx, arr_pstop[i]->vy, arr_proadnode[roadnodeid]->x, arr_proadnode[roadnodeid]->y);
		arr_pstop[i]->Flen = sum + little;
		arr_pstop[i]->Flittle = little;

		sum = sum_dist(roadnodeid+1, arr_proad[roadid]->child[1]); //后半段
		little = coordnate2dist(arr_pstop[i]->vx, arr_pstop[i]->vy, arr_proadnode[roadnodeid+1]->x, arr_proadnode[roadnodeid+1]->y);
		arr_pstop[i]->Tlen = sum + little;
		arr_pstop[i]->Tlittle = little;

		i++;
	}

	return 0;
}


//通过bus的序号返回下标
int get_bus_index(int seq)
{
	int i = 1;
    while(arr_pstop[i])
	{
		if(seq == arr_pstop[i]->id)
		{
		    break;
		}
		i++;
	}

	return i;
}
//输出start和end中间的roadnode，包括两头
int put_roadnode(FILE *fp, int start, int end)
{
	while(start <= end)
	{
		fprintf(fp, "%-8d%-8d(%lf, %lf)\n",arr_proadnode[start]->roadid, arr_proadnode[start]->id, arr_proadnode[start]->x, arr_proadnode[start]->y);
	    start++;
	}
	return 0;
}
//输出到下一站点之间的roadnode，调用此函数必须保证index有下一站，即index+1不是null
int get_path2next(int index)
{
	FILE * fp = NULL;
	int i = 1;
	int start, end;
    int road1, road2;
	int roadnode1, roadnode2;
	int temp;

	fp = fopen(RESULT_FILE, "a+");  //以追加方式打开，这样就可以写入不相邻的站点之间路径
	if(!fp)
	{
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}

	road1 = arr_pstop[index]->roadid;
	road2 = arr_pstop[index+1]->roadid;
	roadnode1 = arr_pstop[index]->roadnodeid;
	roadnode2 = arr_pstop[index+1]->roadnodeid;

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
	//输出站点，0表示站点而不是roadnode
	fprintf(fp, "%-8d%-8d(%lf, %lf)\n",road1, 0, arr_pstop[index]->vx, arr_pstop[index]->vy);
	//顺序输出中间的roadnode
	if(start == end)    //车站在同一条路上
	{   //roadnode+1顶多等于roadnode2，busstop中的roadnode后面肯定至少还有一个roadnode
		put_roadnode(fp, roadnode1+1, roadnode2);
	}
	else if(start+1 == end)//下一站在下一条路上
	{
		//输出前半段
		temp = arr_proad[road1]->child[1];//roadnode+1顶多等于temp，busstop中的roadnode后面肯定至少还有一个roadnode
		put_roadnode(fp, roadnode1+1, temp);
		//输出后半段
		temp = arr_proad[road2]->child[0];
		put_roadnode(fp, temp+1, roadnode2);//temp+1是因为前半段已经输出过一次temp了
	}
	else    //两站之间隔着至少一条路
	{
		//输出前半段
		temp = arr_proad[road1]->child[1];//roadnode+1顶多等于temp，busstop中的roadnode后面肯定至少还有一个roadnode
		put_roadnode(fp, roadnode1+1, temp);
		//输出中间的
		start++;
		end--;
		while(start <= end)
		{
			int node1, node2;
			temp = arr_pzroad[start]->id;      //temp记录道路的id
			node1 = arr_proad[temp]->child[0];
			node2 = arr_proad[temp]->child[1];
		    put_roadnode(fp, node1+1, node2);
			start++;
		}
		//输出后半段
		temp = arr_proad[road2]->child[0];
		put_roadnode(fp, temp+1, roadnode2);
	}
	//输出后面的站点
    fprintf(fp, "%-8d%-8d(%lf, %lf)\n",road2, 0, arr_pstop[index+1]->vx, arr_pstop[index+1]->vy);
	fclose(fp);
	return 0;
}
//将存放结果的文件置空，以便于以追加方式打开文件的函数调用
int calear_result_file(char *filename)
{
	FILE * fp = NULL;
	fp = fopen(filename, "w");
	if(NULL == fp)
	{
	    printf("打开文件%s失败\n", filename);
		exit(-1);
	}
    fclose(fp);
	return 0;
}
//得到任意两个站点间的路径，通过站点的id来的
int get_path(int stop1, int stop2)
{
	int index1, index2;
    index1 = get_bus_index(stop1);
    index2 = get_bus_index(stop2);
//这里要求index1和2必须按顺序来

	//要将不同线路的信息输出在一个文件里，这里就不能清理了
	calear_result_file(RESULT_FILE);
	while(index1 < index2)
	{
	    get_path2next(index1);
		index1++;
	}

	printf("站点之间的路径已写入%s\n", RESULT_FILE);
	return 0;
}

void itoa(int temp ,char * str ,int jinzhi)
{
    sprintf(str,"%d",temp);
}
