#ifndef COMMON_H
#define COMMON_H

#include "config.h"

//#define CHOICE
#define MAX_AROUND 10              //һ��·���м���·��˫��·��2��
#define ZONE_CON     10000          //zone������

/***********************************������ͼ����ؽṹ����************************************/
//��ͨ�ڵ�
typedef struct roadnode
{
    int id;                     //node_id Ψһ��0��ʹ�ã�id���±�һ���ұ�������
	double x;                    //�ڵ�����
	double y;
	double dist;              //����ǰһ���ڵ�ľ���
	int roadid;               //��¼������·��id
}giroadnode;

//�ؼ��ڵ�
typedef struct keynode
{
    int id;                     //keynode_id Ψһ��0��ʹ�ã�id���±�һ�£���id������
	double x;                    //�ڵ�����
	double y;

    int n_out;                  //�ڵ�ĳ�������˫���·��һ������һ�����
	int n_in;
    int road_out[MAX_AROUND]; //��¼ÿ��·��id
    int road_in[MAX_AROUND]; //��¼ÿ��·��id
}gikeynode;

//��·
typedef struct road
{
    int id;                     //road_id Ψһ��0��ʹ�ã�id���±�һ�£���id����
    double length;               //��·����

	int startid;                //��ʼ�ڵ�id
	int endid;                  //��ֹ�ڵ�id
	int child[2];               //��ʼ��roadnode��id��0Ϊ��ͷ1Ϊ����
#ifdef CHOICE
	int roadid ;                //�ϲ���·���߼�id ������ʽ����
#endif
}giroad;

//����
typedef struct zone
{
    int road[ZONE_CON];             //���ڼ�¼��zone��ȫ����road���±�0���¼road����Ŀ��main�е������0��ʼ
}gizone;
/***********************************һ��·�Ľṹ����************************************/

//Ŀ��ڵ�
typedef struct znode
{
    int id;
    int next_road;                 //�ýڵ��������һ��·��roadid
    int prev_road;                 //�ýڵ�ǰһ��·��roadid
}gznode;

//Ŀ���·
typedef struct zroad
{
    int id;                     //road_id Ψһ
	int startid;                //��ʼ�ڵ�id����keynode
	int endid;                  //��ֹ�ڵ�id
}gzroad;
/***********************************������վ�ṹ����************************************/
typedef struct stop
{
	int id;
	int roadid;
	int roadnodeid;
	double x;
	double y;
	double vx;    //��ֱӳ�������
	double vy;
	double Flen;     //��ǰ��keynode�ľ���
	double Tlen;
	double Flittle;  //����ǰ��roadnode�ľ���
	double Tlittle;
	double high;     //�ഹ��ľ���
}busstop;

/***********************************�������************************************/
#endif
