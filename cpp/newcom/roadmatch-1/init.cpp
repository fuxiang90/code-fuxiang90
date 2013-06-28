
#include <stdio.h>    //printf
#include <string.h>   //memcpy
#include <stdlib.h>   //exit

#include "config.h"
#include "common.h"
#include "head.h"


//初始化地图，该函数是根据road生成地图
int init_map()
{
	int i = 1;
	int startid, endid;
	int around;         //around与MAX_AROUND对应，值应等于gikeynode.n
	int count = 0;

	//兼顾roadid不连续的情况
	while(i<MAX_ROAD)   
	{
		if(arr_proad[i]) //若不为空
		{
			count++;
            //处理起点 out
		    startid = arr_proad[i]->startid;
			(arr_pkeynode[startid]->n_out)++;                 //该路的起点，出度数加1
	    	around = (arr_pkeynode[startid]->n_out);
			arr_pkeynode[startid]->road_out[around] = arr_proad[i]->id;   //将此路id添加到该点
		
		    //处理终点 in
    		endid = arr_proad[i]->endid;
	    	(arr_pkeynode[endid]->n_in)++;                   //该路的终点，入度数加1
	        around = (arr_pkeynode[endid]->n_in);
		    arr_pkeynode[endid]->road_in[around] = arr_proad[i]->id;    //将此路id添加到该点
		}
		//是否为空都查找下一条路
        i++;
	}

	printf("\n构图完成，一共%d条路\n\n", count);
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
	    printf("打开文件%s失败\n", RESULT_FILE);
		exit(-1);
	}
	while(i<MAX_KEYNODE)   
	{
		if(arr_pkeynode[i])  //非空行打印内容
		{
			memcpy(road_out, arr_pkeynode[i]->road_out, MAX_AROUND * sizeof(int));
			memcpy(road_in, arr_pkeynode[i]->road_in, MAX_AROUND * sizeof(int));
			fprintf( fp, "%-8d", arr_pkeynode[i]->id );//打印keynode的id

			n = arr_pkeynode[i]->n_out;
			if(n)//若有出度，则打印out
			{
		        fprintf( fp, "%-4s", "out:");
		        for(j=1; j<=n; j++)
		        {
		    	    fprintf(fp, "%-8d", road_out[j]);
		        }
			}

			n = arr_pkeynode[i]->n_in;
			if(n)//若有入度，则打印in
			{
				fprintf( fp, "%-4s", "in:");
		        for(j=1; j<=n; j++)
		        {
		    	    fprintf(fp, "%-8d", road_in[j]);
		        }
			}
		}
		//是否为空都需要换行
		fprintf( fp, "\n");
        i++;
	}
	fclose(fp);
    printf("构图结果已写入%s\n\n", RESULT_FILE);
	return 0;
}