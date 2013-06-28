
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"

//����roadnode����
int create_roadnode_arr( )
{
    arr_proadnode = (giroadnode **)malloc(MAX_ROADNODE * sizeof(giroadnode *));  //Ϊ��̬�������ռ�

   	memset((void *)arr_proadnode, 0, MAX_ROADNODE * sizeof(giroadnode *));    //���������㣬��ʼ��ΪNULL

	return 0;
}

//����keynode�ڵ㣬���ҽ���keynode����keynode_arr����
int init_roadnode(int *pn)  //pnΪ�˴�������������¼����
{
	FILE * fp = NULL;
	int i=0;                         //��¼����ʼΪ0���Ժ�ÿ��һ����¼��i ���� 1�����ֵ��(*pn)
    int rid, id, orid;               //rid��¼��ǰ������·��id��orid��¼��һ��·��roadid
	double x, y;
	double dist;
	giroadnode **arr_p = arr_proadnode;
	giroad **pproad = arr_proad;
            
	fp = fopen(ROADNODE_FILE, "r");
	if(NULL == fp)
	{
	    printf("���ļ�%sʧ��\n", ROADNODE_FILE);
		exit(-1);
	}

	orid = 1;   //orid��1��ʼ��Ҫ��road��1��ʼ��roadnode��һ��Ҳ��roadid=1�ĵط���ʼ������ѭ��������
	pproad[orid]->child[0] = 1;
	while(i < MAX_ROADNODE)                    //���ļ��ж�ȡһ�У�����һ���ڵ㣬�����ڵ㸳ֵ
	{
		if(fscanf(fp, "%d%lf%lf%lf%d", &rid, &x, &y, &dist, &id) != EOF)  //�������ļ���β������ѭ��
		{
			i++;
			// id=i ���������������ظ��������id��Ϊ�±겻�س��ָ��ǵ��������Ҫ�� MAX_ROADNODE > id�������Խ��
		    arr_p[id] = (giroadnode *)malloc(sizeof(giroadnode));    //�����ڵ�
		    arr_p[id]->roadid = rid;                               //Ϊ�ڵ㸳ֵ
		    arr_p[id]->x = x;
		    arr_p[id]->y = y;
			arr_p[id]->dist = dist;
		    arr_p[id]->id = id;

			//����
			if(rid != orid)
			{
			    pproad[orid]->child[1] = id-1;  //����Ҫ����id��������
				pproad[rid]->child[0] = id;
				orid = rid;
			}
		}
		else         //�ļ�����ֱ������ѭ�����ɣ��ڴ�����̬����ʱ���Ѿ���ʼ��ΪNULL�ˣ������ڳ���Ұָ������
		{
		    break;
		}
	}

    pproad[rid]->child[1] = id;
	(*pn) = i;   //���뽫��¼���� i �浽(*pn)����ܴ���������
	fclose(fp);
	printf("�����ͼ����ӵ�roadnode��¼%d��\n\n", i);
	return 0;
}

//�ͷ�roadnode�ڵ㣬���ÿ�roadnode����
int clear_roadnode(int num)
{
    int i=0, n=0;
	giroadnode **arr_p = arr_proadnode;

	while( n< num )
	{
		i++;                    //arr_p[i]ΪNULLʱ��Ҳ��������׷��id
		if(arr_p[i])            //������i��Ȼ����arr_p[i]ΪNULL��ֱ�ӽ����´�ѭ������ΪNULL˵��i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
			n++;                //ÿ�ͷ�һ����¼��n+1
		}
	}

	printf("�ͷ�roadnode��¼%d��\n\n", n);//��ӡ����¼���������id
	return 0;
}

//�ͷ�roadnode���飬һ��Ҫ���ͷ�giroadnode�ڵ���ͷţ�����Ͷ���
int del_roadnode(int num)
{
	clear_roadnode(num);           //��������������ϵĽڵ�
	free(arr_proadnode);
	arr_proadnode = NULL;                      //��3��ָ�����Ϊ����仰
	return 0;
}

