
#include <stdio.h>    //printf
#include <string.h>   //memcpy
#include <stdlib.h>   //exit

#include "config.h"
#include "common.h"
#include "head.h"


//��ʼ����ͼ���ú����Ǹ���road���ɵ�ͼ
int init_map()
{
	int i = 1;
	int startid, endid;
	int around;         //around��MAX_AROUND��Ӧ��ֵӦ����gikeynode.n
	int count = 0;

	//���roadid�����������
	while(i<MAX_ROAD)   
	{
		if(arr_proad[i]) //����Ϊ��
		{
			count++;
            //������� out
		    startid = arr_proad[i]->startid;
			(arr_pkeynode[startid]->n_out)++;                 //��·����㣬��������1
	    	around = (arr_pkeynode[startid]->n_out);
			arr_pkeynode[startid]->road_out[around] = arr_proad[i]->id;   //����·id��ӵ��õ�
		
		    //�����յ� in
    		endid = arr_proad[i]->endid;
	    	(arr_pkeynode[endid]->n_in)++;                   //��·���յ㣬�������1
	        around = (arr_pkeynode[endid]->n_in);
		    arr_pkeynode[endid]->road_in[around] = arr_proad[i]->id;    //����·id��ӵ��õ�
		}
		//�Ƿ�Ϊ�ն�������һ��·
        i++;
	}

	printf("\n��ͼ��ɣ�һ��%d��·\n\n", count);
	return 0;
}

int check_map( )
{
	FILE * fp = NULL;
	int n;
	int i=1;
	int j = 1;
    int road_out[MAX_AROUND];
	int road_in[MAX_AROUND];
            
	fp = fopen(RESULT_FILE, "w");
	if(!fp)
	{
	    printf("���ļ�%sʧ��\n", RESULT_FILE);
		exit(-1);
	}
	while(i<MAX_KEYNODE)   
	{
		if(arr_pkeynode[i])  //�ǿ��д�ӡ����
		{
			memcpy(road_out, arr_pkeynode[i]->road_out, MAX_AROUND * sizeof(int));
			memcpy(road_in, arr_pkeynode[i]->road_in, MAX_AROUND * sizeof(int));
			fprintf( fp, "%-8d", arr_pkeynode[i]->id );//��ӡkeynode��id

			n = arr_pkeynode[i]->n_out;
			if(n)//���г��ȣ����ӡout
			{
		        fprintf( fp, "%-4s", "out:");
		        for(j=1; j<=n; j++)
		        {
		    	    fprintf(fp, "%-8d", road_out[j]);
		        }
			}

			n = arr_pkeynode[i]->n_in;
			if(n)//������ȣ����ӡin
			{
				fprintf( fp, "%-4s", "in:");
		        for(j=1; j<=n; j++)
		        {
		    	    fprintf(fp, "%-8d", road_in[j]);
		        }
			}
		}
		//�Ƿ�Ϊ�ն���Ҫ����
		fprintf( fp, "\n");
        i++;
	}
	fclose(fp);
    printf("��ͼ�����д��%s\n\n", RESULT_FILE);
	return 0;
}