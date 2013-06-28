#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 50010;
int n, k;
struct node
{
    int a;
    int b;
    int num;
}cow[MAX];
int cmpa(node p, node q)//先按a从大到小排序，若a相等则按b从大到小排序
{
    if(p.a == q.a && p.b == q.b) return 0;
    if (p.a == q.a) return p.b > q.b ?1:-1;;
    return p.a > q.a?1:-1;
}
//s 和e 表示能访问的最大 最小下标
int Partition(struct node * data ,int s ,int e )
{
    if(s == e) return  s;
    int p = s;
    int l = s + 1;
    int r = e;
    while(l  <= r){
        while(l <= e && cmpa(data[l] ,data[p]) < 0){
            l ++;
        }

        while(r > s && cmpa (data[r] , data[p] )>=0 ){
            r --;
        }
        if(l < r)
        swap(data[l] ,data[r]);
    }

    swap(data[r] ,data[p]);

    return r;

}

//int * getMaxK(int *data,int s ,int e,int k);
struct node * getMaxK(struct node  *data,int s ,int e,int k)
{
    if(e -s + 1 <= k ){
        return data;
    }

    int p = Partition(data,s,e);

    if(e - p + 1 > k  ){
        return getMaxK(data,p+1,e,k);
    }else if ( e- p + 1 == k){
        struct node *new_data = (struct node *)malloc(sizeof(struct node )*k);
        for(int i = 0 ; i < k  ; i ++ ){
            new_data[i] = data[p+i];
        }

        return new_data;
    }else {
        int k2 = e-p+1;
        struct node *new_data = (struct node *)malloc(sizeof(struct node )*k);
        for(int i = 0 ; i < k2  ; i ++ ){
            new_data[i] = data[p+i];
        }

        struct node * data2 = getMaxK(data,s,p-1, k-k2);

        for(int i = 0 ; i < k -k2 ; i ++){
            new_data[k2 + i] = data2[i];
        }
        free(data2);
        data2 = NULL;
        return new_data;

    }


}
int cmpb(node p, node q)//先按b从大到小排序，若b相等则按a从大到小排序
{
    if (p.b == q.b) return p.a > q.a;
    return p.b > q.b;
}
int main()
{
    //freopen("in","r",stdin);
    int i;
    while (scanf("%d%d", &n, &k) != EOF)
    {
        for (i = 0; i < n; ++i)
        {
            scanf("%d%d", &cow[i].a, &cow[i].b);
            cow[i].num = i + 1;//牛的标号
        }
        struct node * data = getMaxK(cow, 0,n-1 ,k);//前n个牛排序
        sort(data, data + k, cmpb);//前k个牛排序
        printf("%d\n", data[0].num);
    }

	return 0;
}
