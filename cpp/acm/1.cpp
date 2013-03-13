#include <stdio.h>
int contrast(int m)
{
    int a[1000];
    int p=0;
    int q=0;
//	printf("请输入数据\n");
    for(int j=0; j<m; j++)
    {
        while(scanf("%d",&a[j])!=EOF)
        {
            if(a[j]%2==0)
                p++;//偶数
            else
                q++;
            break;
        }
    }
//	printf("%d",q);
    if(p>q)
        return 0;
    else
        return 1;
}

int main()
{
    int n;
    //printf("请输入数据个数\n");

    while(scanf("%d",&n)!=EOF)
    {
        int k=contrast(n);
        if(k==1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;

}
