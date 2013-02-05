#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>

//因为想使用 sleep 函数 带上windows 下的头文件
#include <windows.h>
const int N = 200;
int graph[N][N];
int tgraph[N][N];
int wight[N];
int count ;
int minCutCount ;
int vcount;


void merge(int s,int e)
{
	int i ;
	for(i = 1 ; i <= count ; i ++)
	{
		if(graph[e][i] > 0)
		{
			graph[s][i] += graph[e][i];
			graph[e][i] = 0;

			
			graph[i][s] += graph[i][e];
			graph[i][e] =0;
/*			wight[s] += wight[e];
			wight[e] = 0*/;
		}

	}
	//消除环边
	for(i = 1 ; i <= count ; i ++)
		graph[i][i] = 0;

}

int min_cut()
{
	int cutCount = 0;
	vcount = count;
	int i = 1;
	int s,e;
	for(i = 1 ; i <= count ; i ++)
		wight[i] = 1;
	//srand(time(NULL));
	while(1)
	{
		srand((unsigned)time(NULL));
		if(vcount == 2)
		{
			for(int j = 1 ;  j <= count ; j++)
			{
				if(wight[j] >0 )
				{
					for(int k = 1 ; k <=count ; k++)
						if(graph[j][k] >0)
							return  graph[j][k];

				}
			}

			//return cutCount;
		}
		s = rand()%count + 1;
		e = rand()%count + 1;
		while(s == e || graph[s][e] == 0)
		{
			s = rand()%count + 1;
			e = rand()%count + 1; 
		}
		
		merge(s,e);
		vcount --;
	}
}

int main()
{
	//FILE *fp  = fopen("kargerAdj.txt","r");
	
	freopen("kargerAdj.txt","r",stdin);
	char str[1000];
	int i = 0;
	int s = 0;
	int e = 0;
	count = 0;
	while(scanf("%s",str)!= EOF)
	{
		if(strcmp (str ,"-1") == 0)
		{
			i = 0;
			count ++;
			continue;;
		}
		
		if( i == 0)
		{
			s = atoi(str);
			i ++;
		}
		else
		{
			e = atoi(str);
			tgraph[s][e] = 1;
			tgraph[e][s] = 1;
			i ++;
		}
	}
	//srand(time(NULL));
	
	//count = 40;
	minCutCount = 9999;
	for (i = 0; i <= 100 ; i ++)
	{
		//srand(time(NULL));
		for(int k = 1 ; k <= 40 ; k ++)
			for(int m = 1 ; m <= 40 ; m ++)
				graph[k][m] = tgraph[k][m];
		int te = min_cut();
		if(minCutCount > te)
			minCutCount = te;
		printf("%d\n",te);
		Sleep(2000);
	}

	printf("%d : %d",count ,minCutCount);
	


	

	return 0;
}