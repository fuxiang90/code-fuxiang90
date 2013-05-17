
#include <stdio.h>    //printf
#include <string.h>   //memcpy
#include <stdlib.h>   //exit
#include <math.h>

#include "config.h"
#include "common.h"
#include "head.h"


//�������
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
//�㵽�߶������
int p2seg(double x, double y, const giroadnode *a, const giroadnode *b, double *out_x, double *out_y)
{
	double vx, vy;
	double dotpv, dotav, dotvv;
	double t;
	double disa, disb;

	vx = b->x - a->x;                              //  ����v = ob -oa = ab
	vy = b->y - a->y;
	dotpv = x*vx + y*vy;                           //  dotab = |oa|*|ob|*cos<oa,ob>
	dotav = (vx * a->x) + (vy * a->y);
	dotvv = vx*vx + vy*vy;
                                          //��@��ʾ��ˣ��Ƶ�һ�¹�ʽ������t�ĺ���(����v=ab)
	t = (dotpv - dotav)/dotvv;            //  (dotpv - dotav)/dotvv = (op@v - oa@v)/(v@v) = (ap@v)/(v@v)
	                                      // =(|ap|*|v|*cos<ap, ab>)/(|v|*|v|*cos0) = (|ap|*cos<ap,ab>)/|ab|
	                                      //��ˣ�t��a��(ap��ab�ϵ�ӳ���)�ĳ�����ռab���ȵı���
	//0<t<1��pӳ�����ab��
	//t>=1����pӳ�����ab֮��(b��)����ֱ��ȡbΪ�����
	//t<=0����pӳ�����ab֮��(a��)����ֱ��ȡaΪ����㣬�����ԣ���һ��<0��Ϊa�����Ի�Ҫ�����
    if(t>0 && t<1)
	{
		(*out_x) = a->x + t*vx;
		(*out_y) = a->y + t*vy;
	}
    else  //�����棬���ؾ�������Ķ˵�����
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

//�㵽�߶ξ���
double dis2seg(double x, double y, const giroadnode *u, const giroadnode *v ,int flag = 1)
{
	double out_x, out_y, h;
	p2seg(x, y, u, v, &out_x, &out_y);
	if(flag == 1)
        h = dis(x, y, out_x, out_y);
    else { //������ʵ�ľ���
        double delta_x = out_x - x;
        double delta_y = out_y - y;
        h = sqrt( delta_x*delta_x*PRE_LON*PRE_LON  + delta_y * delta_y*PRE_LAN*PRE_LAN );
    }
	return h;
}
//�㵽ֱ�߾��룬���߾���
double dis2line(double x, double y, const giroadnode *u, const giroadnode *v)
{
	double upx, upy, uvx, uvy;
	double det, a, h;
	upx = x - u->x;
	upy = y - u->y;
	uvx = v->x - u->x;
	uvy = v->y - u->y;
	det = upx*uvy - upy*uvx;        //��˵�Ĥ |a X b| = |a|*|b|*sin<a,b>
	a = dis2(u, v);
	h = det/a;
	return h;
}

//��㵽һ��·�ε���̾���
double get_dis(int start, int end, double x, double y)
{
	double dis = 361.0;  //Ĭ��Ϊ�ܴ󣬾�γ�Ȳ����ܳ���360�ȣ����嵽���ݣ�10�ȶ����ܳ���
	double temp;
	giroadnode **arr_p = arr_proadnode;

	while(start<end)
	{
	    temp = dis2seg(x, y, arr_p[start], arr_p[start+1]);
		if(temp<dis)        //��δ�ҵ�������룬������
		{
		    dis = temp;
		}
		else        //temp>=dis�������·�ϲ��������ҵ������ľ�����
		{
		    break;
		}

		start++;
	}
	return dis;
}

//���������roadid
int get_nearest_road(double x, double y)
{
	int rid = 0;        //�������·��id
	int start, end;     //ÿ��·����ʼ��
	int road, i=1;
	double dis=361.0, temp;

	while(arr_pzroad[i])  //ÿ��·���ò���
	{
		road = arr_pzroad[i]->id;                  //�ҵ�roadid
		start = arr_proad[road]->child[0];         //ͨ��roadid�ҵ�roadnode��ʼ����ֹ��
		end = arr_proad[road]->child[1];
		temp = get_dis(start, end, x, y);

		if(temp<dis)     //dis��¼��С��
		{
		    dis = temp;
			rid = road;
		}
		i++;
	}
	return rid;
}

//���������roadnodeid
int get_nearest_roadnode(int id, double x, double y)//����roadid������
{
	int start, end;
	double dis = 361.0;  //Ĭ��Ϊ�ܴ󣬾�γ�Ȳ����ܳ���360�ȣ����嵽���ݣ�10�ȶ����ܳ���
	double temp;
	int rnid;
	giroadnode **arr_p = arr_proadnode;

	start = arr_proad[id]->child[0];         //ͨ��roadid�ҵ�roadnode��ʼ����ֹ��
	end = arr_proad[id]->child[1];

	while(start<end)
	{
	    temp = dis2seg(x, y, arr_p[start], arr_p[start+1]);
		if(temp<dis)        //��δ�ҵ�������룬������
		{
		    dis = temp;
			rnid = start;
		}
		else if(temp == dis)//���������start��Ϊ�����
		{
			dis = temp;
			rnid = start;
		    break;
		}
		else //temp>dis���������һ���ڴ�·�ϣ������������һ�����ҹ��ˣ��������и�������
		{
			break;
		}
		start++;
	}
   //arr_p[start]��arr_p[start+1]֮�������߶�һ��Ϊ����������߶�
	return rnid;
}
//����������룬����Ϊroadid�����꣬�ú�������ȫ����roadnode
double get_nearest_dis(int id, double x, double y)
{
	int start, end;
	double dis = 361.0;  //Ĭ��Ϊ�ܴ󣬾�γ�Ȳ����ܳ���360�ȣ����嵽���ݣ�10�ȶ����ܳ���
	double temp;
	giroadnode **arr_p = arr_proadnode;

	start = arr_proad[id]->child[0];         //ͨ��roadid�ҵ�roadnode��ʼ����ֹ��
	end = arr_proad[id]->child[1];

	while(start<end)
	{
	    temp = dis2seg(x, y, arr_p[start], arr_p[start+1]);
		if(temp<dis)        //��δ�ҵ�������룬������
		{
		    dis = temp;
		}
		start++;
	}
	return dis;//��ʵ��������Ƕ���
}
//����������룬������¼�����������
double get_nearest_disp(int id, double x, double y, double *out_x, double *out_y)
{
	int start;
	double dis = 361.0;  //Ĭ��Ϊ�ܴ󣬾�γ�Ȳ����ܳ���360�ȣ����嵽���ݣ�10�ȶ����ܳ���
    giroadnode **arr_p = arr_proadnode;
	//�õ������roadnodeid���ڵ���һ��
	start = get_nearest_roadnode(id, x, y);
	//�õ�����
    dis = dis2seg(x, y, arr_p[start], arr_p[start+1]);
	//arr_p[start]��arr_p[start+1]֮�������߶�һ��Ϊ����������߶�
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
//������ľ���ת��Ϊʵ�ʾ���
double coordnate2dist(double x1, double y1, double x2, double y2)
{
    return sqrt( (y1-y2)*(y1-y2)*PRE_LAN*PRE_LAN + (x1-x2)*(x1-x2)*PRE_LON*PRE_LON );
}
//�ۼӾ���
double sum_dist(int start, int end)
{
	double sum = 0.0;
	giroadnode **arr_p = arr_proadnode;

	while(end>start)  //��Ҫ��start
	{
        sum += arr_p[end]->dist;
	    end--;
	}
	return sum;
}

//�������stop�������Ϣд��ṹ
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

		sum = sum_dist(arr_proad[roadid]->child[0], roadnodeid); //ǰ���
		little = coordnate2dist(arr_pstop[i]->vx, arr_pstop[i]->vy, arr_proadnode[roadnodeid]->x, arr_proadnode[roadnodeid]->y);
		arr_pstop[i]->Flen = sum + little;
		arr_pstop[i]->Flittle = little;

		sum = sum_dist(roadnodeid+1, arr_proad[roadid]->child[1]); //����
		little = coordnate2dist(arr_pstop[i]->vx, arr_pstop[i]->vy, arr_proadnode[roadnodeid+1]->x, arr_proadnode[roadnodeid+1]->y);
		arr_pstop[i]->Tlen = sum + little;
		arr_pstop[i]->Tlittle = little;

		i++;
	}

	return 0;
}


//ͨ��bus����ŷ����±�
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
//���start��end�м��roadnode��������ͷ
int put_roadnode(FILE *fp, int start, int end)
{
	while(start <= end)
	{
		fprintf(fp, "%-8d%-8d(%lf, %lf)\n",arr_proadnode[start]->roadid, arr_proadnode[start]->id, arr_proadnode[start]->x, arr_proadnode[start]->y);
	    start++;
	}
	return 0;
}
//�������һվ��֮���roadnode�����ô˺������뱣֤index����һվ����index+1����null
int get_path2next(int index)
{
	FILE * fp = NULL;
	int i = 1;
	int start, end;
    int road1, road2;
	int roadnode1, roadnode2;
	int temp;

	fp = fopen(RESULT_FILE, "a+");  //��׷�ӷ�ʽ�򿪣������Ϳ���д�벻���ڵ�վ��֮��·��
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
		exit(-1);
	}

	road1 = arr_pstop[index]->roadid;
	road2 = arr_pstop[index+1]->roadid;
	roadnode1 = arr_pstop[index]->roadnodeid;
	roadnode2 = arr_pstop[index+1]->roadnodeid;

	//����վ�����ڵĵ�·����¼�±꣨��֪id�������±꣩
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
	//���վ�㣬0��ʾվ�������roadnode
	fprintf(fp, "%-8d%-8d(%lf, %lf)\n",road1, 0, arr_pstop[index]->vx, arr_pstop[index]->vy);
	//˳������м��roadnode
	if(start == end)    //��վ��ͬһ��·��
	{   //roadnode+1�������roadnode2��busstop�е�roadnode����϶����ٻ���һ��roadnode
		put_roadnode(fp, roadnode1+1, roadnode2);
	}
	else if(start+1 == end)//��һվ����һ��·��
	{
		//���ǰ���
		temp = arr_proad[road1]->child[1];//roadnode+1�������temp��busstop�е�roadnode����϶����ٻ���һ��roadnode
		put_roadnode(fp, roadnode1+1, temp);
		//�������
		temp = arr_proad[road2]->child[0];
		put_roadnode(fp, temp+1, roadnode2);//temp+1����Ϊǰ����Ѿ������һ��temp��
	}
	else    //��վ֮���������һ��·
	{
		//���ǰ���
		temp = arr_proad[road1]->child[1];//roadnode+1�������temp��busstop�е�roadnode����϶����ٻ���һ��roadnode
		put_roadnode(fp, roadnode1+1, temp);
		//����м��
		start++;
		end--;
		while(start <= end)
		{
			int node1, node2;
			temp = arr_pzroad[start]->id;      //temp��¼��·��id
			node1 = arr_proad[temp]->child[0];
			node2 = arr_proad[temp]->child[1];
		    put_roadnode(fp, node1+1, node2);
			start++;
		}
		//�������
		temp = arr_proad[road2]->child[0];
		put_roadnode(fp, temp+1, roadnode2);
	}
	//��������վ��
    fprintf(fp, "%-8d%-8d(%lf, %lf)\n",road2, 0, arr_pstop[index+1]->vx, arr_pstop[index+1]->vy);
	fclose(fp);
	return 0;
}
//����Ž�����ļ��ÿգ��Ա�����׷�ӷ�ʽ���ļ��ĺ�������
int calear_result_file(char *filename)
{
	FILE * fp = NULL;
	fp = fopen(filename, "w");
	if(NULL == fp)
	{
	    printf("���ļ�%sʧ��\n", filename);
		exit(-1);
	}
    fclose(fp);
	return 0;
}
//�õ���������վ����·����ͨ��վ���id����
int get_path(int stop1, int stop2)
{
	int index1, index2;
    index1 = get_bus_index(stop1);
    index2 = get_bus_index(stop2);
//����Ҫ��index1��2���밴˳����

	//Ҫ����ͬ��·����Ϣ�����һ���ļ������Ͳ���������
	calear_result_file(RESULT_FILE);
	while(index1 < index2)
	{
	    get_path2next(index1);
		index1++;
	}

	printf("վ��֮���·����д��%s\n", RESULT_FILE);
	return 0;
}

void itoa(int temp ,char * str ,int jinzhi)
{
    sprintf(str,"%d",temp);
}
