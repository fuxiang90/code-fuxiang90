
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "common.h"
#include "road.h"
#include "node.h"
#include "init.h"
#include "roadnode.h"
#include "function.h"
#include "aim.h"
#include "stop.h"
#include "bat_func.h"
#include "zone.h"

//�����ȫ�ֱ�����
	//��ͼ
    giroad **arr_proad = NULL;                        //��̬�����ָ�룬arr_proad[1]ָ��road_idΪ1��giroad
    gikeynode **arr_pkeynode = NULL;                  //��̬�����ָ�룬arr_pkeynode[1]ָ��keynode_idΪ1��gikeynode
    giroadnode **arr_proadnode = NULL;                //roadnode�����ָ��
	gizone *arr_pzone[ZONE_NUM];                      //��ͼ��������ʼ��Ǯ������

    //Ŀ��·��
    gzroad **arr_pzroad = NULL;
	gznode **arr_pznode = NULL; 
	//����վ��
	busstop **arr_pstop = NULL;

int main(void)
{
	//��ͼ
	int road_num;                              //��¼ʵ�ʴ��ļ��ж�ȡ�˼���road��¼
	int keynode_num;                           //��¼ʵ�ʴ��ļ��ж�ȡ�˼���node��¼
	int roadnode_num;                          //roadnode����


	//������ͼ
	create_road_arr();               //Ϊroad��̬�������ռ䣬������ֵNULL
	create_keynode_arr();            //Ϊroad��̬�������ռ䣬������ֵNULL
	init_road(&road_num);            //���ļ��ж�ȡ��·��Ϣ����ʼ�����飬ָ��giroad�ڵ�
	init_keynode(&keynode_num);      //���ļ��ж�ȡ��·��Ϣ����ʼ�����飬ָ��giroad�ڵ�

	init_map();                      //��ʼ����ͼ����roadnode
	printf("�������ͼ�����roadnode�ڵ�...\n");
    create_roadnode_arr();           //���ͼ�����roadnode�ڵ�
	init_roadnode(&roadnode_num);
    printf("���ڻ�������...\n");
    init_zone(road_num);    //�����Ϊroad������

	//show_zone_con();
    test_zone();

	//�ͷŵ�ͼ�ڴ�
	del_zone();
	del_road(road_num);
	del_keynode(keynode_num);
	del_roadnode(roadnode_num);

	return 0;
}

//��ǰ��������
int stopmain(void)
{
	//��ͼ
	int road_num;                              //��¼ʵ�ʴ��ļ��ж�ȡ�˼���road��¼
	int keynode_num;                           //��¼ʵ�ʴ��ļ��ж�ȡ�˼���node��¼
	int roadnode_num;                          //roadnode����


	//������ͼ
	create_road_arr();               //Ϊroad��̬�������ռ䣬������ֵNULL
	create_keynode_arr();            //Ϊroad��̬�������ռ䣬������ֵNULL
	init_road(&road_num);           //���ļ��ж�ȡ��·��Ϣ����ʼ�����飬ָ��giroad�ڵ�
	init_keynode(&keynode_num);     //���ļ��ж�ȡ��·��Ϣ����ʼ�����飬ָ��giroad�ڵ�

	//��ʼ����ͼ
	init_map();

	printf("�������ͼ�����roadnode�ڵ�...\n");
    //���ͼ�����roadnode�ڵ�
    create_roadnode_arr();
	init_roadnode(&roadnode_num);


	//Ŀ��·�κ�վ��
    create_aimroad_arr();
	create_stop_arr();
    
	//���еĶ���������
    save_lines();
    

	//�ͷ�Ŀ��·���ڴ�
    free(arr_pzroad);
    free(arr_pznode);
    free(arr_pstop);
	arr_pzroad = NULL;
	arr_pznode = NULL;
	arr_pstop = NULL;

	//�ͷŵ�ͼ�ڴ�
	del_road(road_num);
	del_keynode(keynode_num);
	//roadnode
	del_roadnode(roadnode_num);

	return 0;
}

//������֮ǰ��������
int xxxmain(void)
{
	//��ͼ
	int road_num;                              //��¼ʵ�ʴ��ļ��ж�ȡ�˼���road��¼
	int keynode_num;                           //��¼ʵ�ʴ��ļ��ж�ȡ�˼���node��¼
	int roadnode_num;                          //roadnode����

	//Ŀ��·��
	int zroad_num;
	int stop_num;

	//������ͼ
	create_road_arr();               //Ϊroad��̬�������ռ䣬������ֵNULL
	create_keynode_arr();            //Ϊroad��̬�������ռ䣬������ֵNULL
	init_road(&road_num);           //���ļ��ж�ȡ��·��Ϣ����ʼ�����飬ָ��giroad�ڵ�
	init_keynode(&keynode_num);     //���ļ��ж�ȡ��·��Ϣ����ʼ�����飬ָ��giroad�ڵ�

	//��ʼ����ͼ
	init_map();
//	check_map();  //��������������ļ���

	printf("�������ͼ�����roadnode�ڵ�...\n");
    //���ͼ�����roadnode�ڵ�
    create_roadnode_arr();
	init_roadnode(&roadnode_num);


	//Ŀ��·�κ�վ��
    create_aimroad_arr();
	create_stop_arr();
	//����save_lines()ʱ��ֻ�������飬����ʼ���ṹ����Ϊÿ����·����������
    init_aimroad(&zroad_num, AIM_FILE);
	init_stop(&stop_num, STOP_FILE); //վ���������

	//����
	sort_aimroad();
	//�źõĵ�·�ŵ��ļ���
	show_aimroad();
	//�������·�����룬������ӡ����
//	test_nearest();
	//����վ����Ϣ���������Ա�����busstop�ṹ��
	calc_stop();
    //��վ���������Ϣд���ļ�
//    show_stop();
    //��վ���������Ϣд���ļ�����Flen+Tlen��road�ĳ������Ա�
//    check_stop();

    //��ӡ������վ��֮���roadnode,д���ļ�,��ͨ��վ���idȷ�������
//	get_path(20001, 20018);

	//�ͷ�Ŀ��·���ڴ�
    del_aimroad(zroad_num);
	//�ͷŹ���վ
	del_stop(stop_num);

	//�ͷŵ�ͼ�ڴ�
	del_road(road_num);
	del_keynode(keynode_num);
	//roadnode
	del_roadnode(roadnode_num);

	return 0;
}