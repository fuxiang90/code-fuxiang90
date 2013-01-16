/*
USER: fuxiang2
TASK: stamps
LANG: C++
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define BIGNUM 100000000
using namespace std;
int main()
{
    int f[2000001],a[50],i,j,m,n;
    freopen("stamps.in","r",stdin);
    freopen("stamps.out","w",stdout);
    cin>>n>>m;
    for (i=0;i<m;i++) cin>>a[i];
    f[0]=0;
    for (i=1;i<=2000000;i++)
    {
        f[i]=BIGNUM;
        for (j=0;j<m;j++)
            if (a[j]<=i) f[i]=min(f[i],f[i-a[j]]+1);
        if (f[i]>n) break;
    }
    cout<<i-1<<endl;
    return 0;
}
