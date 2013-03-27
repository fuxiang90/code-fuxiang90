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
    return m.b<n.b;
}
struct node data[N];
int used[N];
int used2[N];
struct p
{
    int a;
    int pos;
     bool operator < (const struct p & m)const {
        return a < m.a ;
    }
};

struct p mat[N];
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
            used2[j] = 0;
        }
        queue<struct node> qqq;
        for(int j = 1 ; j <= n ; j ++){
            cin>>data[j].a >>data[j].b;
            used[j] = 0;
            used2[j] = 0;
            qqq.push(data[j]);
        }
        //sort(data+2,data+n+1,cmp);
        priority_queue<struct p> q;
//        for(int i = 2; i <= n ; i ++){
//            struct p t;
//            t.a = data[i].a;
//            t.pos = i;
//            //q.push(q)
//        }
        int ans = 0;
        //int pos = 2;
        int total = m;
        int need = data[1].b;
       // int pos = 2;
        //int pos = 2;
        while( total < need && ans+ 1 <= n  ){
            int max_pos = -1;
            //int max_a = 0;
            for(int i = 2 ; i <= n ; i ++){
                if(used2[i] == 0&&total >= data[i].b && used[i] == 0){
                    struct p t;
                    t.a = data[i].a;
                    t.pos = i;
                    q.push(t);
                    used2[i] = 1;
                   // max_a = data[i].a;
                }

            }


            if(!q.empty()){
                total += q.top().a;
                max_pos = q.top().pos;
                q.pop();
                ans ++;
                used[max_pos] =1 ;

            }else{
                break;
            }





        }
        if(total < need){
            cout << -1<<endl;
        }else{
            cout << ans <<endl;
        }
    }
    return 0;
}
