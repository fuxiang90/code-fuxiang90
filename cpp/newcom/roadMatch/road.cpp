
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"


//#define CHOICE
//����road����
int create_road_arr()
{
    arr_proad = (giroad **)malloc(MAX_ROAD * sizeof(giroad *));  //Ϊ��̬�������ռ�

   	memset((void *)arr_proad, 0, MAX_ROAD * sizeof(giroad *));    //���������㣬��ʼ��ΪNULL

	return 0;
}

//������·�ڵ㣬���ҽ��ڵ�·����road_arr����
int init_road(int *pn)  //pnΪ�˴�������������¼����
{
	giroad **arr_p = arr_proad;
	FILE * fp = NULL;
	int i=0;                         //��¼����ʼΪ0���Ժ�ÿ��һ����¼��i ���� 1�����ֵ��(*pn)
    int id, startid, endid;
	double length;
	#ifdef CHOICE
	int roadid;
	#endif
    arr_p = arr_proad;

	fp = fopen(ROAD_FILE, "r");
	if(NULL == fp)
	{
	    printf("���ļ�%sʧ��\n", ROAD_FILE);
		exit(-1);
	}

	while(i < MAX_ROAD)                    //���ļ��ж�ȡһ�У�����һ���ڵ㣬�����ڵ㸳ֵ
	{
        // ��ε����ļ�û�� ��·�ȼ�����ֶ� ������ fscanfҪ����

        #ifndef CHOICE
		if(fscanf(fp, "%d%d%d%lf", &id, &startid, &endid, &length) != EOF)//if(fscanf(fp, "%d%d%d%lf%*d", &id, &startid, &endid, &length) != EOF)  //�������ļ���β������ѭ��
		#else
        if(fscanf(fp, "%d%d%d%lf%d", &id, &startid, &endid, &length,&roadid) != EOF)
		#endif
		{
			i++;
			// id �������ظ��������id��Ϊ�±겻�س��ָ��ǵ��������������Ҫ�� MAX_ROAD > id�������Խ��
		    arr_p[id] = (giroad *)malloc(sizeof(giroad));          //�����ڵ�
		    arr_p[id]->id = id;                                    //Ϊ�ڵ㸳ֵ
		    arr_p[id]->length = length;
		    arr_p[id]->startid = startid;
		    arr_p[id]->endid = endid;
			arr_p[id]->child[0] = 0;
			arr_p[id]->child[1] = 0;

			#ifdef CHOICE
			arr_p[id]->roadid = roadid;
			#endif
		}
		else         //�ļ�����ֱ������ѭ�����ɣ��ڴ�����̬����ʱ���Ѿ���ʼ��ΪNULL�ˣ������ڳ���Ұָ������
		{
		    break;
		}
	}

	(*pn) = i;   //���뽫��¼���� i �浽(*pn)����ܴ���������
	fclose(fp);
	printf("��ȡroad��¼������id��\n%d    %d\n", i, id);
	return 0;
}

//�ͷŵ�·�ڵ㣬���ÿյ�·����
int clear_road(int num)
{
    int i=0, n=0;
	giroad **arr_p = arr_proad;
	while( n< num )
	{
		i++;                   //arr_p[i]ΪNULLʱ��Ҳ��������׷��id
		if(arr_p[i])           //������i��Ȼ����arr_p[i]ΪNULL��ֱ�ӽ����´�ѭ������ΪNULL˵��i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
			n++;               //ÿ�ͷ�һ����¼��n+1
		}
	}

	printf("�ͷ�road��¼%d��\n\n", n);//��ӡ����¼���������id
	return 0;
}

//�ͷ�road���飬�ͷ�road����һ��Ҫ���ͷ�giroad�ڵ���ͷţ�����Ͷ���
int del_road(int num)
{
	clear_road(num);            //��������������ϵĽڵ�
	free(arr_proad);
	arr_proad = NULL;                    //��3��ָ�����Ϊ����仰
	return 0;
}
