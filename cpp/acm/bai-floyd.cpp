#include<iostream>
using namespace std;
int MAX_DIS=999;
int graph[50][50];
int dis[50][50];
int path[50][50];
int n;
void flody()
{
	int i,j,k;
	for(k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(dis[i][k]+dis[k][j]<dis[i][j])
				{
					dis[i][j]=dis[i][k]+dis[k][j];
					path[i][j]=k;
				}
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cout<<dis[i][j]<<' ';
		}
		cout<<endl;
	}
}
void init()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			path[i][j]=0;
			graph[i][j]=(i==j)?0:MAX_DIS;
			dis[i][j]=MAX_DIS;
		}
	}
	graph[1][2]=2;
	graph[1][4]=20;
	graph[2][5]=1;
	graph[3][1]=3;
	graph[4][3]=8;
	graph[4][6]=6;
	graph[4][7]=4;
	graph[5][3]=7;
	graph[5][8]=3;
	graph[6][3]=1;
	graph[7][8]=1;
	graph[8][6]=2;
	graph[8][10]=2;
	graph[9][7]=2;
	graph[10][9]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dis[i][j]=graph[i][j];
		}
	}
}
void print(int i,int j)
{
	if(i==j)
		return ;
	else if(path[i][j]==0)
		cout<<j<<' ';
	else
	{
		print(i,path[i][j]);
		print(path[i][j],j);
	}
}
int main()
{
	int i,j;
	n=10;
	init();
	flody();
	cin>>i>>j;
	cout<<i<<' ';
	print(i,j);
	return 0;
}
