#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 100000 + 10;
int n,m;
struct node
{
    int a;
    int b;
};
bool cmp(const struct node & a ,const struct node & b){
    return a.a>b.a;
}
struct node data[N];
int main()
{
    freopen("in","r",stdin);
    int t;
    cin>>t;
    for(int i = 1 ; i <= t ; i ++){
        cin>>n>>m;
        for(int j = 1 ; j <= n ; j ++){
            cin>>data[j].a >>data[j].b;
        }
        sort(data+2,data+n+1,cmp);
        int ans = 0;
        int pos = 2;
        int re = data[1].b - m;
        while(re > 0 ){
            re-= data[pos].a;
            ans ++;
            pos ++;
        }
        if(re > 0){
            cout << -1<<endl;
        }else{
            cout << ans <<endl;
        }
    }
    return 0;
}
