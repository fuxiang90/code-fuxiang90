
#include <stdlib.h>  //itoa(int value, char *string, int radix)������������Ϊ����
#include <string.h>  //char *strcat(char *dest,char *src) ����dest�Ľ�β"\0"; memset
#include <malloc.h>   //malloc
#include <stdio.h>

#include "config.h"
#include "common.h"
#include "head.h"
#include "aim.h"
#include "stop.h"
#include "function.h"

//��ô����·���ļ���
char * get_roadfile_name(int line, int direction) //����Ϊ��·�ͷ���
{
    char *s = NULL;  //���ڴ���ļ���
	char temp[10];

	s = (char *)malloc(128 * sizeof(char));  //һ���ļ������ᳬ��128���ַ�
	memset((void *)s, 0, 128 * sizeof(char));

	//ƴ�ӿ�ʼ
	strcat(s, "./data/");//ƴ��ǰ���
    itoa(line, temp, 10);
	strcat(s, temp);//ƴ����·
	strcat(s, "_");
	itoa(direction, temp, 10);
	strcat(s, temp);//ƴ�ӷ���
	strcat(s, "_road.txt");

	return s;
}
//��ô��վ����ļ���
char * get_stopfile_name(int line, int direction) //����Ϊ��·�ͷ���
{
    char *s = NULL;  //���ڴ���ļ���
	char temp[10];

	s = (char *)malloc(128 * sizeof(char));  //һ���ļ������ᳬ��128���ַ�
	memset((void *)s, 0, 128 * sizeof(char));

	//ƴ�ӿ�ʼ
	strcat(s, "./data/");//ƴ��ǰ���
    itoa(line, temp, 10);
	strcat(s, temp);//ƴ����·
	strcat(s, "_");
	itoa(direction, temp, 10);
	strcat(s, temp);//ƴ�ӷ���
	strcat(s, "_stop.txt");

	return s;
}
//���start��end�м��roadnode��������ͷ
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
//�������һվ��֮���roadnode�����ô˺������뱣֤index����һվ����index+1����null
int put_stop_path(int line, int direction, int count_stop)
{
	int index = count_stop;  //�ڼ�վ�����������±�����
	FILE * fp = NULL;
	int i = 1;
	int start, end;    //���ڼ�¼road1��road2���±�
    int road1, road2;
	int roadnode1, roadnode2;
	int temp;
	int count;  //���ڼ�¼����˶��ٸ�roandode

	fp = fopen(PATH_FILE, "a+");  //��׷�ӷ�ʽ�򿪣������Ϳ���д�벻���ڵ�վ��֮��·��
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", PATH_FILE);
		exit(-1);
	}

	road1 = arr_pstop[index]->roadid;
	road2 = arr_pstop[index+1]->roadid;
	roadnode1 = arr_pstop[index]->roadnodeid;
	roadnode2 = arr_pstop[index+1]->roadnodeid;
	roadnode1++;  //�õ�����վ��֮ǰ��roadnode�������Ҫ+1

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
	count = 0;
	//���վ�㣬0��ʾվ�������roadnode
	fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_pstop[index]->vx, arr_pstop[index]->vy, 0.0, count);
	count++;
	//��һ��roadnode��վ��֮��ľ��룬Ҫ������ӡ
	fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_proadnode[roadnode1]->x, arr_proadnode[roadnode1]->y, arr_pstop[index]->Tlittle, count);
	count++;
	//˳������м��roadnode
	if(start == end)    //��վ��ͬһ��·�ϣ����������ʵ���м��������ܰ�
	{//roadnode�������roadnode2��busstop�е�roadnode����϶����ٻ���һ��roadnode�������ܵ���һ��·��roadnode��
        //���roadnode1 = roadnode2����˵����վ֮��ֻ��һ��roadnode
		//��ϸ���룬���߼��ϣ�����roadnode1>roadnode2Ҳ���п��ܵģ�������վ���û��roadnode��������ʵ�в�̫����
		//����վ��ֻ��1��roadnode�����溯����Ͳ����ٴ�ӡ��
		put_roadnode_path(fp, line, direction, count_stop, &count, roadnode1+1, roadnode2);
	}
	else if(start+1 == end)//��һվ����һ��·��
	{
		//���ǰ���
		temp = arr_proad[road1]->child[1];//roadnode+1�������temp��busstop�е�roadnode����϶����ٻ���һ��roadnode
		put_roadnode_path(fp, line, direction, count_stop, &count, roadnode1+1, temp);
		//�������
		temp = arr_proad[road2]->child[0];
		put_roadnode_path(fp, line, direction, count_stop, &count, temp+1, roadnode2);//temp+1����Ϊǰ����Ѿ������һ��temp��
	}
	else    //��վ֮���������һ��·
	{
		//���ǰ���
		temp = arr_proad[road1]->child[1];//roadnode+1�������temp��busstop�е�roadnode����϶����ٻ���һ��roadnode
		put_roadnode_path(fp, line, direction, count_stop, &count, roadnode1+1, temp);
		//����м��
		start++;
		end--;
		while(start <= end)
		{
			int node1, node2;
			temp = arr_pzroad[start]->id;      //temp��¼��·��id
			node1 = arr_proad[temp]->child[0];
			node2 = arr_proad[temp]->child[1];
		    put_roadnode_path(fp, line, direction, count_stop, &count, node1+1, node2);
			start++;
		}
		//�������
		temp = arr_proad[road2]->child[0];
		put_roadnode_path(fp, line, direction, count_stop, &count, temp+1, roadnode2);
	}
	//��������վ��
    fprintf(fp, "%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\n",line, direction, index, arr_pstop[index]->vx, arr_pstop[index]->vy, arr_pstop[index]->Flittle, count);
	fclose(fp);
	return 0;
}
//���浥��ָ����·��
int save_one_line(int line, int direction, int stop_num)
{
	int count_stop = 1;
    while(count_stop < stop_num)//�ӵ�һ��վ�㵽���һ��վ��
	{
	    put_stop_path(line, direction, count_stop);//�Զ������վ�㵽��һվ���·��
		count_stop++;
	}
    return 0;
}
//��lines�����������·����¼����
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
	    printf("���ļ�%sʧ��\n", LINES_FILE);
		exit(-1);
	}

	calear_result_file(PATH_FILE);

	while(fscanf(fp, "%d%d", &line, &direction) != EOF)
	{
		roadfile = get_roadfile_name(line, direction);
		stopfile = get_stopfile_name(line, direction);

        init_aimroad(&zroad_num, roadfile);
	    init_stop(&stop_num, stopfile);    //վ���������
	    //����
	    sort_aimroad();

        //��stop����Ϣ�������
	    calc_stop();

        //��¼������·
		save_one_line(line, direction, stop_num);

		//����ѭ�����ƺ���
	    free(roadfile);//ÿ�Σ��ļ��������·���ռ䣬���ÿ�ζ�Ҫ�ͷ�
		roadfile = NULL;
	    free(stopfile);
		stopfile = NULL;
		//�ͷŹҽӵĽڵ㣬������û�ͷ�
	    clear_zroad(zroad_num);//����������������aimroad
	    clear_znode();
		clear_stop(stop_num);
	}
	return 0;
}
