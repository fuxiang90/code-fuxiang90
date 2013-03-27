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
bool cmp(const struct node & m ,const struct node & n){
    return m.a>n.a;
}
struct node data[N];
int used[N];
int main()
{
    freopen("in","r",stdin);
    int t;
    cin>>t;
    for(int i = 1 ; i <= t ; i ++){
        cin>>n>>m;
        for(int j = 1 ; j <= n ; j ++){
            cin>>data[j].a >>data[j].b;
            used[j] = 0;
        }
        sort(data+2,data+n+1,cmp);
        int ans = 0;
        //int pos = 2;
        int total = m;
        int need = data[1].b;
       // int pos = 2;
        while( total < need && ans+ 1 <= n  ){
            int max_pos = -1;
            //int max_a = 0;
            for(int i = 2 ; i <= n ; i ++){
                if(total >= data[i].b && used[i] == 0){

                   // max_a = data[i].a;
                    max_pos = i;
                    break;

                }

            }
            if(max_pos == -1){
                break;
            }
            used[max_pos] =1 ;
            total += data[max_pos].a;
            ans ++;

        }
        if(total < need){
            cout << -1<<endl;
        }else{
            cout << ans <<endl;
        }
    }
    return 0;
}
