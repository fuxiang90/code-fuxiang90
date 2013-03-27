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
const int N = 30000 + 10;
int n,m;
int dist[N];
int supply[N];
struct node{
    int val;
    int pos;
    bool operator < (const struct node & m)const {
        return val < m.val ;
    }
};
struct node extra[N];
int ans ;
int flag ;



int main()
{
    freopen("i-in","r",stdin);
    int t;
    scanf("%d",&t);
    for(int casei = 1; casei <= t ; casei ++){
        scanf("%d%d",&n,&m);

        for(int i = 0 ; i< n ; i ++){
            scanf("%d",&dist[i]);
        }
        for(int i = 0 ; i< n ; i ++){
            scanf("%d",&supply[i]);
        }
        for(int i = 0 ; i< n ; i ++){
            scanf("%d",&(extra[i].val));
        }
        flag = 0;
        priority_queue<struct node> q;
        int sum = 0;
        int time_sum = 0;
        for(int i = 0 ;i < n ; i ++){

            q.push(extra[i]);
            sum += supply[i];
            while(!q.empty() && sum  < dist[i] ){
                sum += q.top().val;
                q.pop();
                time_sum += m;
            }
            if( sum < dist[i] ){
                flag = -1;
                break;
            }
            time_sum += dist[i];
            sum  -= dist[i];

        }

        printf("Case %d: ", casei);
        if(flag == -1){
            printf("impossible\n");
        }else{
            printf("%d\n",time_sum);
////            flag = 0;
////            ans = 0;
////            time = 0;
////            dfs(0,0,0);
////            //printf("time :%d\n",time);
////            if(flag == 0){
////                printf("impossible\n");
////            }else{
//                printf("%d\n",ans);
//            }
        }


    }
    return 0;
}
