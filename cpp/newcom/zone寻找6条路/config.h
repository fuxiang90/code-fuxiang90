#ifndef CONFIG_H
#define CONFIG_H

//Ԥ����

//����ר��
#define MAX_AIMROAD  200           //�������·����һ��ҪС�� MAX_AIMROAD-1
#define MAX_STOP     100           //������aimroad�ϵ�վ��С��MAXSTOP-1

//��γ��ת���ɾ���Ĳ���
#define PRE_LON      102266.5      //���ȣ���Ӧx
#define PRE_LAN      111191.67     //γ�ȣ���Ӧy
//��ͼר��
#define MAX_ROAD     380000        //MAX_ROAD ���� road_id����id���������������˷ѣ��ڴ����ڵ��ʱ������Կ���
#define MAX_KEYNODE  165000        //�ؼ���
#define MAX_ROADNODE     2881000   //��ͨ�㣬�ܶ�ܶࡣ��

//zone����
#define MIN_X        112.90
#define MIN_Y        22.50
#define MAX_X        114.15
#define MAX_Y        24.00
#define ZONE_NEAR    6             //ÿ��zone���ҳ������4��·
#define ZONE_NUM     2500          //zone������
#define DX           0.025         //ÿ��zone���ݶȣ������ɷ�Ϊ50*50=2500������
#define DY           0.03

//������ļ�
#define ROAD_FILE          "D:\\work\\doc\\giroad.txt"        //����road�ڵ��ļ���λ�ã����ڳ�����ж�ȡgiroad����
#define KEYNODE_FILE       "D:\\work\\doc\\ginode.txt"        //����node�ڵ��ļ���λ�ã����ڳ�����ж�ȡginode����
#define ROADNODE_FILE      "D:\\work\\doc\\giroadnode.txt"    //����roadnode�ڵ��ļ���λ�ã����ڳ�����ж�ȡgiroadnode����

//������ļ�
#define AIM_FILE           "D:\\work\\doc\\gzroad.txt"
#define STOP_FILE          "D:\\work\\doc\\stop.txt"
#define RESULT_FILE        "D:\\work\\doc\\result.txt"

#define LINES_FILE         "D:\\work\\doc\\stops\\lines.txt"
#define PATH_FILE          "D:\\work\\doc\\stops\\path.txt"

#endif