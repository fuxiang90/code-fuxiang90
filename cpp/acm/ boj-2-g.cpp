#include<cstdio>
#include<cstring>

const int N=1000010;
int ans[N+10]={0};

int main()
{
	int i,j;
	memset(ans,0,sizeof(ans));
	for(i=1;i<=N/2;i++)
		for(j=1;i*j<=N;j++)
			ans[i*j]++;
	for(i=2;i<=N;i++)
		ans[i]+=ans[i-1];
	int n;
	while(scanf("%d",&n)&&n)
		printf("%d\n",ans[n]);
}
