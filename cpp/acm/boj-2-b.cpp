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
const int N = 500 + 200;
int graph[N][N];
int dist[N] ;
int used[N];
const int max_num = 9999999;
int n,h;

int dijstra(int s ,int e)
{

    for(int i = 1 ; i <= n ; i++){
        dist[i] = max_num;
        used[i] = 0;
    }
    dist[s] = 0;
    used[s] = 1;
    for(int i = 1 ; i < n ; i ++){

        int pos = s;
        int min_dist = max_num;
        for(int j = 1 ; j <= n ; j ++){
            if(used[j] == 0 && dist[j] < min_dist){
                min_dist = dist[j];
                pos = j;
            }
        }
        used[pos] = 1;
        for(int j = 1 ; j<= n ; j ++){
            if(used[j] == 0 &&dist[j] > dist[pos] + graph[pos][j]){
                dist[j] = dist[pos] + graph[pos][j];
            }
        }

    }
    return dist[e];

}


int bellFord(int s ,int e)
{

   //int used
    for(int i =1 ; i <= n ; i ++){
        dist[i] = max_num;
    }
    dist[s] = 0;
    for(int k = 1 ; k< n ; k++){
        for(int i = 1 ; i<= n ; i ++){
            for(int j = 1 ; j <= n ; j ++){
                if(dist[i] + graph[i][j] < dist[j]){
                    dist[j] = dist[i] + graph[i][j];
                }
            }
        }
    }

    return dist[e];
}
int main()
{
    freopen("in","r",stdin);
    while(cin>> n >> h){
        for(int i = 1 ; i <= n ; i ++){
            for(int j = 1 ; j <= n ; j ++){
                cin>>graph[i][j];
                if(graph[i][j] == 0 ){
                    graph[i][j] = max_num;
                }
            }
        }

        int ans = dijstra(1,n) ;
        ans += dijstra(n,1);
//        int ans = bellFord(1,n);
//        ans += bellFord(n,1);
        if( ans > h ){
            cout << "-1" << endl;
        }else {
            cout << ans << endl;
        }


    }
    return 0;
}
