#ifndef CONFIG_H
#define CONFIG_H

//����һ������ ������ʽ�ĵ�·��roadsegment ��Ҫ�󣬾͵���һЩroadsegment û���ڽ�����ʽ���ҵ���Ӧ
// ��ôһ����������� ����������roadsegment ȥ�ҽ�����ʽ��roadseq
//#define CHOICE 1 //ʹ�ý�����ʽ��Ϊԭͼ

//Ԥ����

//����ר��
#define MAX_AIMROAD  200           //�������·����һ��ҪС�� MAX_AIMROAD-1
#define MAX_STOP     100           //������aimroad�ϵ�վ��С��MAXSTOP-1

//��γ��ת���ɾ���Ĳ���
#define PRE_LON      102266.5      //���ȣ���Ӧx
#define PRE_LAN      111191.67     //γ�ȣ���Ӧy
//��ͼר��
#define MAX_ROAD     730000        //MAX_ROAD ���� road_id����id���������������˷ѣ��ڴ����ڵ��ʱ������Կ���
#define MAX_KEYNODE  14000000//320000//165000        //�ؼ���
#define MAX_ROADNODE 4800000    //2881000   //��ͨ�㣬�ܶ�ܶࡣ��

//zone����
// ��������Ҫд�� ����Ȼ������������Ľű�
//��Ȼ����Ĳ����ܶ඼�ø�
#define MIN_X        112.30//112.90
#define MIN_Y        22.50 //
#define MAX_X        114.25 //
#define MAX_Y        24.00  //
#define ZONE_NEAR    6             //ÿ��zone���ҳ������4��·
#define ZONE_NUM     2500          //zone������
//#define DX           0.025         //ÿ��zone���ݶȣ������ɷ�Ϊ50*50=2500������
//#define DY           0.03
extern double DX ;
extern double DY ;

//������ļ�
#ifndef CHOICE
#define ROAD_FILE          "../giroad.txt"        //����road�ڵ��ļ���λ�ã����ڳ�����ж�ȡgiroad����
#define KEYNODE_FILE       "../ginode.txt"        //����node�ڵ��ļ���λ�ã����ڳ�����ж�ȡginode����
#define ROADNODE_FILE      "../giroadnode.txt"    //����roadnode�ڵ��ļ���λ�ã����ڳ�����ж�ȡgiroadnode����

#else
#define ROAD_FILE          "../giroad.txt"        //����road�ڵ��ļ���λ�ã����ڳ�����ж�ȡgiroad����
#define KEYNODE_FILE       "../ginode.txt"        //����node�ڵ��ļ���λ�ã����ڳ�����ж�ȡginode����
#define ROADNODE_FILE      "../giroadnode.txt"    //����roadnode�ڵ��ļ���λ�ã����ڳ�����ж�ȡgiroadnode����
#endif

//������ļ�
#define AIM_FILE           "../gzroad.txt"
#define STOP_FILE          "../stop.txt"
#define RESULT_FILE        "../result.txt"

#define LINES_FILE         "../lines.txt"
#define PATH_FILE          "../path.txt"

#endif
