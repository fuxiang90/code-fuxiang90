
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"


//����busstop����
int create_stop_arr()
{
    arr_pstop = (busstop **)malloc(MAX_STOP * sizeof(busstop *));  //Ϊ��̬�������ռ�

   	memset((void *)arr_pstop, 0, MAX_STOP * sizeof(busstop *));    //���������㣬��ʼ��ΪNULL

	return 0;
}

//������·�ڵ㣬���ҽ��ڵ�·����road_arr����
int init_stop(int *pn, char *filename)  //pnΪ�˴�������������¼����
{
	busstop **arr_p = arr_pstop;
	FILE * fp = NULL;
	int i=0;                         //��¼����ʼΪ0���Ժ�ÿ��һ����¼��i ���� 1�����ֵ��(*pn)
    int id;
	double x, y;
            
	fp = fopen(filename, "r");
	if(NULL == fp)
	{
	    printf("���ļ�%sʧ��\n", filename);
		exit(-1);
	}
	while(i < MAX_STOP)                    //���ļ��ж�ȡһ�У�����һ���ڵ㣬�����ڵ㸳ֵ
	{
		if(fscanf(fp, "%d%lf%lf", &id, &x, &y) != EOF)  //�������ļ���β������ѭ��
		{
			i++;         //0û��ʹ��
		    arr_p[i] = (busstop *)malloc(sizeof(busstop));           //�����ڵ�
		    arr_p[i]->id = id;                                       //Ϊ�ڵ㸳ֵ
			arr_p[i]->x = x;
		    arr_p[i]->y = y;
		}
		else         //�ļ�����ֱ������ѭ�����ɣ��ڴ�����̬����ʱ���Ѿ���ʼ��ΪNULL�ˣ������ڳ���Ұָ������
		{
		    break;
		}
	}

	(*pn) = i;   //���뽫��¼���� i �浽(*pn)����ܴ���������
	fclose(fp);
//	printf("��ȡ %d ��busstop��¼\n", i);
	return 0;
}

//�ͷŵ�·�ڵ㣬���ÿյ�·����
int clear_stop(int num)
{
	busstop **arr_p = arr_pstop;
    int i=0, n=0;
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
	return 0;
}

int del_stop(int num)
{
	clear_stop(num);            //��������������ϵĽڵ�
	free(arr_pstop);
	arr_pstop = NULL;                    //��3��ָ�����Ϊ����仰
	return 0;
}

//��վ���������Ϣд���ļ�
int show_stop()
{
	busstop **arr_p = arr_pstop;
	FILE * fp = NULL;
    int i=1;        //վ���Ǵ�1��ʼ��
 
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
		exit(-1);
	}
	while(arr_p[i])
	{
		fprintf(fp, "%-4d%-8d%-8d (%lf,%lf)(%lf,%lf)(%lf,%lf,%lf)\n", arr_p[i]->id, arr_p[i]->roadid, arr_p[i]->roadnodeid, arr_p[i]->x, arr_p[i]->y, arr_p[i]->vx, arr_p[i]->vy, arr_p[i]->Flen, arr_p[i]->Tlen, arr_p[i]->high);
		i++;
	}
	fclose(fp);
	printf("վ����д��%s\n\n", RESULT_FILE);
	return 0;
}

//��վ���������Ϣд���ļ�����Flen+Tlen��road�ĳ������Ա�
int check_stop()
{
	FILE * fp = NULL;
    int i=1;        //վ���Ǵ�1��ʼ��
 
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
		exit(-1);
	}
	while(arr_pstop[i])
	{
		fprintf(fp, "%-4d%-8d%-8d (%lf,%lf)\n", arr_pstop[i]->id, arr_pstop[i]->roadid, arr_pstop[i]->roadnodeid, arr_pstop[i]->Flen+arr_pstop[i]->Tlen, arr_proad[arr_pstop[i]->roadid]->length);
		i++;
	}
	fclose(fp);
	printf("վ����������д��%s\n\n", RESULT_FILE);
	return 0;
}
