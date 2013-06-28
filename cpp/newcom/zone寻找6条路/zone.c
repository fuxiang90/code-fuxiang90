
#include <string.h>   //memset
#include <malloc.h>   //malloc
#include <stdio.h>    //printf
#include <stdlib.h>   //exit

#include "common.h"
#include "config.h"
#include "head.h"     //����ȫ�ֱ���
#include "function.h" //ʹ��������ĺ��� get_nearest_dis(int id, double x, double y)

/*
(112.880062, 22.496958)---(114.130185, 23.997482)
(112.90, 22.50)---(114.15, 24.00)
�ݶȷֱ�Ϊ0.025 * 0.03�������,50*50
*/

typedef struct near_road            //���ṹ���ڼ�¼�㵽roadid�ľ��룬��ʵ�ϣ�disΪ�Ƕȼ�����
{                   
    int roadid;
	double dis;
}road_dis;

static double rootx = MIN_X;
static double rooty = MIN_Y;
static double dx = DX;
static double dy = DY;
static road_dis arr_near_road[ZONE_NEAR+1];    //��������4��·,0�����ڱ�������ʹ��

//��ʼ�������4��·
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

//����road����ʼ��zone
int init_zone(int num)//�������road����Ŀ
{
    int i=0, n=0;     //������road
    int start, end;   //����roadnode
	int index;            //����zone
	double x, y;

	memset((void *)arr_pzone, 0, ZONE_NUM * sizeof(gizone *));    //���������㣬��ʼ��ΪNULL

	while( n< num )   //��֤����������·
	{
		i++;
		if(arr_proad[i])   //��ʹroadid��������Ҳ����
		{
			int old_index = -1;
			start = arr_proad[i]->child[0];
			end = arr_proad[i]->child[1];
			while(start <= end) //�ڴ˳�ʼ��zone
			{
				x = arr_proadnode[start]->x - rootx;
				y = arr_proadnode[start]->y - rooty;
				index = 50 * (int)(x/dx) + (int)(y/dy);        //���������ĸ�����

				if(NULL == arr_pzone[index])               //����δ����ռ䣬�����ռ�
				{
				    arr_pzone[index] = (gizone *)malloc(sizeof(gizone));
					memset((void *)arr_pzone[index]->road, 0, ZONE_NUM * sizeof(int));
                    arr_pzone[index]->road[0] = 0;         //��ʼʱ��0��·
				}
                //���������ĵ���Ȼ�����������������ӣ������������ظ�������δ���������������Կ������ظ�
				if(index != old_index)
				{
					arr_pzone[index]->road[arr_pzone[index]->road[0]+1] = arr_proadnode[start]->roadid;
				    arr_pzone[index]->road[0]++;
				    old_index = index;
				}

				start++;
			}
			n++;           //road������һ
		}
	}
	return 0;
}

//�ͷ�zone��ؽڵ�
int del_zone()
{
    int i=0;
	while( i< ZONE_NUM )
	{
		if(arr_pzone[i])           //������i��Ȼ����arr_p[i]ΪNULL��ֱ�ӽ����´�ѭ������ΪNULL˵��i=id
		{
			free(arr_pzone[i]);
		    arr_pzone[i] = NULL;
		}
		i++;
	}
	return 0;
}

//��ÿ��zone�ڵ�road��Ŀд���ļ�
int show_zone_con()
{
	FILE * fp = NULL;
    int i=0;
 
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
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
	printf("zone����ͳ����д��%s\n\n", RESULT_FILE);
	return 0;
}


//�õ������������n��·��id
int get_zone_road(double x, double y)
{
	int i=1;
	int si;           //����sort��i
	double temp;      //��ʱ��ž���
	int zone_roadid;  //��ʱ���roadid
	int index = 50 * (int)((x-rootx)/dx) + (int)((y-rooty)/dy);

	if(index >= ZONE_NUM)
	{
	    printf("�õ㲻�ڱ���ͼ��Χ��\n");
		exit(-1);
	}

    init_near_road();   //�������ZONE_NEAR��·��ʼ��

    while(i<=arr_pzone[index]->road[0])
	{
		zone_roadid = arr_pzone[index]->road[i];
	    temp = get_nearest_dis(zone_roadid, x, y);

		//α�������򣬽���temp���road�����ƶ�
		if(temp<arr_near_road[ZONE_NEAR].dis)
		{
		    arr_near_road[0].roadid = zone_roadid;                  //�ڱ�
		    arr_near_road[0].dis = temp;
	        for(si=ZONE_NEAR-1; temp<arr_near_road[si].dis; si--)   //si=0ʱ���϶�������ѭ��
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

//��ӡ�����road
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

    printf("���������꣨xy�ÿո����,x=0.0�˳�����");
    scanf("%lf %lf", &x, &y);
	while(x!=0.0)
	{
		get_zone_road(x, y);
		print_near_road();

	    printf("���������꣨xy�ÿո����,x=0.0�˳�����");
        scanf("%lf %lf", &x, &y);
	}

	return 0;
}