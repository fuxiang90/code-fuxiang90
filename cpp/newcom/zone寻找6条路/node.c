
#include <stdio.h>    //printf
#include <stdlib.h>   //exit
#include <string.h>   //memset
#include <malloc.h>   //malloc

#include "config.h"
#include "common.h"
#include "head.h"

//����node����
int create_keynode_arr()
{
    arr_pkeynode = (gikeynode **)malloc(MAX_KEYNODE * sizeof(gikeynode *));  //Ϊ��̬�������ռ�
    
   	memset((void *)arr_pkeynode, 0, MAX_KEYNODE * sizeof(gikeynode *));    //���������㣬��ʼ��ΪNULL
	
	return 0;
}

//����keynode�ڵ㣬���ҽ���keynode����keynode_arr����
int init_keynode(int *pn)  //pnΪ�˴�������������¼����
{
	gikeynode **arr_p = arr_pkeynode;
	FILE * fp = NULL;
	int i=0;                         //��¼����ʼΪ0���Ժ�ÿ��һ����¼��i ���� 1�����ֵ��(*pn)
    int id;
	double x, y;
            
	fp = fopen(KEYNODE_FILE, "r");
	if(NULL == fp)
	{
	    printf("���ļ�%sʧ��\n", KEYNODE_FILE);
		exit(-1);
	}

	while(i < MAX_KEYNODE)                    //���ļ��ж�ȡһ�У�����һ���ڵ㣬�����ڵ㸳ֵ
	{
		if(fscanf(fp, "%d%lf%lf", &id, &x, &y) != EOF)  //�������ļ���β������ѭ��
		{
			i++;
			// id �������ظ��������id��Ϊ�±겻�س��ָ��ǵ��������������Ҫ�� MAX_KNODE > id�������Խ��
		    arr_p[id] = (gikeynode *)malloc(sizeof(gikeynode));    //�����ڵ�
		    arr_p[id]->id = id;                                    //Ϊ�ڵ㸳ֵ
		    arr_p[id]->x = x;
		    arr_p[id]->y = y;
		    arr_p[id]->n_out = 0;
		    arr_p[id]->n_in = 0; 
			memset(arr_p[id]->road_out, 0, MAX_AROUND*sizeof(int));
			memset(arr_p[id]->road_in, 0, MAX_AROUND*sizeof(int));//����������
		}
		else         //�ļ�����ֱ������ѭ�����ɣ��ڴ�����̬����ʱ���Ѿ���ʼ��ΪNULL�ˣ������ڳ���Ұָ������
		{
		    break;
		}
	}

	(*pn) = i;   //���뽫��¼���� i �浽(*pn)����ܴ���������
	fclose(fp);
	printf("��ȡkeynode��¼������id��\n%d    %d\n", i, id);
	return 0;
}

//�ͷ�keynode�ڵ㣬���ÿ�keynode����
int clear_keynode(int num)
{
    int i=0, n=0;
    gikeynode **arr_p = arr_pkeynode;

	while( n< num )
	{
		i++;                    //arr_p[i]ΪNULLʱ��Ҳ��������׷��id
		if(arr_p[i])           //������i��Ȼ����arr_p[i]ΪNULL��ֱ�ӽ����´�ѭ������ΪNULL˵��i=id
		{
			free(arr_p[i]);
		    arr_p[i] = NULL;
			n++;               //ÿ�ͷ�һ����¼��n+1
		}
	}

	printf("�ͷ�keynode��¼%d��\n\n", n);//��ӡ����¼���������id
	return 0;
}

//�ͷ�keynode���飬һ��Ҫ���ͷ�gikeynode�ڵ���ͷţ�����Ͷ���
int del_keynode(int num)
{
	clear_keynode(num);           //��������������ϵĽڵ�
	free(arr_pkeynode);
	arr_pkeynode = NULL;                      //��3��ָ�����Ϊ����仰
	return 0;
}

