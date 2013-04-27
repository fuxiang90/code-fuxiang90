
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"

//����zroad����
int create_zroad_arr( )
{
    arr_pzroad = (gzroad **)malloc(MAX_AIMROAD * sizeof(gzroad *));  //Ϊ��̬�������ռ�

   	memset((void *)arr_pzroad, 0, MAX_AIMROAD * sizeof(gzroad *));    //���������㣬��ʼ��ΪNULL
	return 0;
}

//����znode����
int create_znode_arr( )
{
	//����ʹ����MAX_KEYNODE���ռ��˷ѱȽ����أ������ڲ���ʱ�������������
    arr_pznode = (gznode **)malloc(MAX_KEYNODE * sizeof(gznode *));      //Ϊ��̬�������ռ�

   	memset((void *)arr_pznode, 0, MAX_KEYNODE * sizeof(gznode *));    //���������㣬��ʼ��ΪNULL
	return 0;
}

//������·�ڵ㣬���ҽ��ڵ�·����aimroad_arr����
int init_aimroad(int *pn, char *filename)    //pnΪ�˴�������������¼����
{
	gzroad **arr_r = arr_pzroad;
	gznode **arr_n = arr_pznode;
	FILE * fp = NULL;
	int i=0;                           //��¼����ʼΪ0���Ժ�ÿ��һ����¼��i ���� 1�����ֵ��(*pn)
    int id, startid, endid;
	int count=0;

	fp = fopen(filename, "r");
	if(NULL == fp)
	{
	    printf("���ļ�%sʧ��\n", filename);
		exit(-1);
	}
	while(i < MAX_AIMROAD)                    //���ļ��ж�ȡһ�У�����һ���ڵ㣬�����ڵ㸳ֵ
	{
		if(fscanf(fp, "%d%d%d", &id, &startid, &endid) != EOF)  //�������ļ���β������ѭ��
		{
			//��ʼ��zroad��iҲ�Ǵ�1��ʼ��
			i++;
		    arr_r[i] = (gzroad *)malloc(sizeof(gzroad));          //�����ڵ�
		    arr_r[i]->id = id;                                    //Ϊ�ڵ㸳ֵ
		    arr_r[i]->startid = startid;
		    arr_r[i]->endid = endid;

			//��ʼ��znode
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
			if(0 == arr_n[startid]->next_road)                //����¼�º����·
			{
			    arr_n[startid]->next_road = id;
			}
			if(0 == arr_n[endid]->prev_road)                  //�յ��¼��ǰ���·
			{
			    arr_n[endid]->prev_road = id;
				count++;
			}
		}
		else         //�ļ�����ֱ������ѭ�����ɣ��ڴ�����̬����ʱ���Ѿ���ʼ��ΪNULL�ˣ������ڳ���Ұָ������
		{
		    break;
		}
	}
	fclose(fp);
	(*pn) = i;     //���뽫��¼���� i �浽(*pn)����ܴ���������
	printf("Ŀ��·�γ�ʼ�����\n");
	return 0;
}

//�ͷŵ�·�ڵ㣬���ÿյ�·����
int clear_zroad(int num)
{
	gzroad **arr_p = arr_pzroad;
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

//	printf("�ͷ�zroad��¼�����Լ�id��\n%d    %d\n", n, i);//��ӡ����¼���������id
	return 0;
}

//�ͷ�znode�ڵ㣬���ÿ�znode����
int clear_znode()
{
	gznode **arr_p = arr_pznode;
    int i=1;

	while( i< MAX_KEYNODE )
	{
		if(arr_p[i])           //������i��Ȼ����arr_p[i]ΪNULL��ֱ�ӽ����´�ѭ������ΪNULL˵��i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
		}
		i++;                    //arr_p[i]ΪNULLʱ��Ҳ��������׷��id
	}
	return 0;
}

//�ͷ�zroad���飬�ͷ�zroad����һ��Ҫ���ͷ�gzroad�ڵ���ͷţ�����Ͷ���
int del_zroad(int num)
{
	clear_zroad(num);            //��������������ϵĽڵ�
	free(arr_pzroad);
	arr_pzroad = NULL;                    //��3��ָ�����Ϊ����仰
	return 0;
}

//�ͷ�znode���飬һ��Ҫ���ͷ�gznode�ڵ���ͷţ�����Ͷ���
int del_znode()
{
	clear_znode();           //��������������ϵĽڵ�
	free(arr_pznode);
	arr_pznode = NULL;                      //��3��ָ�����Ϊ����仰
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
//�õ���ʼ��
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
	    printf("�����Ϊ0�ĵ㣬��·���ܴ��ڻ�·\n");
		exit(-1);
	}
	else if(count > 1)
	{
	    printf("��%d�����Ϊ0�ĵ㣬��·���ڶ�·\n", count); //��������ʾ�������һ��·������sort��������ͻ������
		exit(-1);
	}
	return id;
}
//������·������
int sort_aimroad()
{
    int start;
	int roadid;
	int i=1;

	start = get_road_start();                 //�õ���ʼ��
	roadid = arr_pznode[start]->next_road;              //��ʼ·

	while(roadid)
	{
		arr_pzroad[i]->id = roadid;            //id
        arr_pzroad[i]->startid = start;        //startid
		start = arr_proad[roadid]->endid;      //start�Ѿ��ı�
		arr_pzroad[i]->endid = start;          //endid
		roadid = arr_pznode[start]->next_road;    //����
		i++;
	}
    printf("�Ѷ�%d��·���������\n\n", i-1);
	return 0;
}
//������õ�·д���ļ�
int show_aimroad()
{
	gzroad **arr_p = arr_pzroad;
	FILE * fp = NULL;
    int i=1;

	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
		exit(-1);
	}
	while(arr_p[i])
	{
	    fprintf(fp, "%8d%8d%8d\n", arr_p[i]->id, arr_p[i]->startid, arr_p[i]->endid);
		i++;
	}
	fclose(fp);
	printf("��������д��%s\n\n", RESULT_FILE);
	return 0;
}

//�˷����Ǹ���znode���������
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
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
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
	printf("��������д��%s\n\n", RESULT_FILE);
	return 0;
}
