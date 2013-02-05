#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
struct node{
    double x;
    double y;
};
struct node pos[25];


const double DOUBLE_MAX = 10000000000.0;
struct Path
{
    char pass[25];/*标记是否已经过该城市*/
	double min_distance;/*当前已知的从i出发的最小距离*/
	int nextcity;/*下一个出发的城市*/
	struct Path *next;
};

double C[25][25];
int Getmin(struct Path *G[25][25],int i,int num_S,char S[25]);/*查找G[i][n]链表的结点*/
void Write(int i,int n,char S[25],struct Path *G[25][25],int num_S);/*计算G[i][num_S]*/
void Travel(int size,int i,int n,char S[25],struct Path *G[25][25],int num_S);/*标记V－S的顶点，然后调用Write函数来填表*/
void Trip(int n,char S[25],struct Path *G[25][25]);/*计算min_distance并输出*/
void Printpath(char S[],int path[],struct Path *G[][25],int n);/*打印输出路径*/
/*S[]表示用字符数组显示的城市集合*/
double dist(node & a ,node & b)
{
    return sqrt(  (a.x-b.x)*(a.x-b.x) + (a.y-b.y)* (a.y-b.y) ) ;
}
int main()
{
    freopen("tsp.txt","r",stdin);
    int n,i,j;
	int output[25];
	char S[25];
	struct Path *G[25][25];
	printf("Please enter the number of cities:\n");/*输入城市个数*/
	scanf("%d",&n);
    for(int i = 0 ; i < n ; ++i){
        double a,b;
        scanf("%lf%lf",&a,&b);
        pos[i].x = a;
        pos[i].y = b;
    }
    for(int i =0 ; i < n ; ++i){
        for(int j =0 ; j < n ; ++ j){
            if(i ==j ) C[i][j] = 0;
            else {
                C[i][j] = dist(pos[i],pos[j]);
            }
        }
    }
	//printf("Please enter the matrix:\n");/*输入矩阵*/

	printf("The number of cities is:%d\n",n);
	for(i=0;i<n;i++)
	{	for(j=0;j<n;j++)
			printf("%lf\t",C[i][j]);
		printf("\n");
	}
	for(i=0;i<n;i++)
		S[i]='0';
	S[i]='\0';
	for(i=0;i<n;i++)
	{	G[i][0]=(struct Path *)malloc(sizeof(struct Path));
		strcpy(G[i][0]->pass,S);
		G[i][0]->min_distance=C[i][0];
		G[i][0]->next=NULL;
	}
	for(i=0;i<n;i++)
		for(j=1;j<n;j++)
			G[i][j]=NULL;
	Trip(n,S,G);
	Printpath(S,output,G,n);

	//getch();
}

int Getmin(struct Path *G[25][25],int i,int num_S,char S[25])
{	struct Path *temp;
	for(temp=G[i][num_S];temp!=NULL;temp=temp->next)
		if(strcmp(S,temp->pass)==0)
			break;
	return temp->min_distance;
}

void Trip(int n,char S[],struct Path *G[][25])
{	int i,size_S;
	for(size_S=1;size_S<=n-2;size_S++)
	{	Travel(size_S,1,n,S,G,size_S);/*从1出发求|S|=size_S的min_distance*/
		for(i=0;i<n;i++)
			S[i]='0';
		S[i]='\0';
	}
	G[0][n-1]=(struct Path *)malloc(sizeof(struct Path));
	G[0][n-1]->min_distance=DOUBLE_MAX; /*G[0][n-1]->min_distance为无穷大*/
	for(i=1;i<n;i++)
	{	if(G[0][n-1]->min_distance>C[0][i]+G[i][n-2]->min_distance)
		{	G[0][n-1]->min_distance=C[0][i]+G[i][n-2]->min_distance;
			G[0][n-1]->nextcity=i;
		}
	}
	printf("The mini-distance is:%lf\n",G[0][n-1]->min_distance );
}

void Travel(int size,int i,int n,char S[25],struct Path *G[25][25],int num_S)
{	int k;
	if(size==0)
	{	for(k=n-1;k>0;k--)/*求顶点k通过集合S到终点的最短路径*/
			if(S[k]=='0')/*k不在集合S中*/
				Write(k,n,S,G,num_S);
	}
	else
	{	for(k=i;k<=n-size;k++)
		{	S[k]='1';
			Travel(size-1,k+1,n,S,G,num_S);
			S[k]='0';
		}
	}
}

void Write(int i,int n,char S[25],struct Path *G[25][25],int num_S)
{
	int k,pre_min;
	struct Path *temp_path;
	temp_path=(struct Path *)malloc(sizeof(struct Path));
	strcpy(temp_path->pass,S);
	temp_path->next=NULL;
	temp_path->min_distance=DOUBLE_MAX;
	for(k=1;k<=n-1;k++)/*对每个属于集合S的k,计算G(k,S)=min{C[i][k]+G(k,s-{k})}*/
	{	if(S[k]=='1') /*j在集合S*/
		{	S[k]='0';  /*S=S-{k}*/
			pre_min=Getmin(G,k,num_S-1,S); /*求G(k,s-{k})的值*/
			S[k]='1';	/*做循环，故要恢复集合s ，选择别的k值*/
			if(temp_path->min_distance>C[i][k]+pre_min)/*G(k,S)=min{C[i][k]+G(k,s-{k})}*/
			{	temp_path->min_distance=C[i][k]+pre_min;
				temp_path->nextcity=k;
			}
		}

	}
	temp_path->next=G[i][num_S];/*把temp_path插入到G[i][num_S]的队头*/
	G[i][num_S]=temp_path;
}

void Printpath(char S[],int output[],struct Path *G[][25],int n)
{	int i,j,k;
	struct Path *temp;
	for(i=1;i<n;i++)
		S[i]='1';
	S[0]='0';
	S[i]='\0';
	output[0]=0;
	for(k=n-1,i=1,j=G[0][k]->nextcity;k>0;i++,k--)
	{	output[i]=j;
		S[j]='0';
		for(temp=G[j][k-1];temp!=NULL;temp=temp->next)
			if(strcmp(temp->pass,S)==0)
				break;
		j=temp->nextcity;
	}
}





