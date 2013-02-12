#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
//#include <limits.h>
using namespace std;

const int INT_MAX = 0x1fffffff;

 ifstream fin("g3.txt");

 const int N = 1000 + 2;
 int num_edges;
 int num_v;
 int graph[N][N];
 int dp[N][N];

 int dist[N];
 int p[N];
// void bellmanFord()
// {
//
// }
//bool bellmanFord(int s )
//{
//
//}
bool bellmanFord(int s )
{
    int used[N] = {0};

    for(int i = 1 ; i <= num_v ; ++i){
        dist[i] = INT_MAX;
        p[i] = s;
    }

    dist[s] = 0;
    queue<int> q;
    q.push(s);
    used[s] = 1;
    while( !q.empty() ){
        int u = q.front();
        q.pop();
        used[u] = 0;
        for(int i = 1 ; i <= num_v ; ++i){
            if(dist[i] > dist[u] + graph[u][i]   && graph[u][i] != INT_MAX){
                dist[i] = dist[u] + graph[u][i] ;
                if(used[i] == 0){
                    q.push(i);
                    used[i] = 1;
                }
            }
        }//end for
    }

    for(int i = 1 ; i <= num_v ; ++i ){

        for(int j = 1 ; j <= num_v ; ++j){
            if(dist[i] + graph[i][j] < dist[j])
                return false;//有负环
        }
    }
    return true;
}


void floyd()
{
    for(int i = 1 ; i <= num_v ; ++ i ){
        for(int j = 1 ; j <= num_v ; ++j){
                dp[i][j] = graph[i][j];
                if(i ==j) dp[i][j] = 0;
        }
    }

    //要考虑这样的情况，INT_MAX 表示无穷大，但是由于int 表示的范围有限
    //而无穷大+ 任意一个 非无穷小的数  都是 无穷大
    for(int k = 1 ; k <= num_v ; ++ k){
        for(int i = 1 ; i <= num_v ; ++ i ){
            for(int j = 1 ; j <= num_v ; ++j){
                if( dp[i][j]  > dp[i][k] + dp[k][j]  && dp[i][k] != INT_MAX &&dp[k][j] != INT_MAX)
                    dp[i][j] = dp[i][k] + dp[k][j];

                    //debug
                    if(dp[i][j] < -1000000 ){
                        dp[i][j] ++;
                    }
            }
        }
    }
}

// return
int dijkstra(int s )
{

    int used[N] = {0};

    for(int i = 1 ; i <= num_v ; ++i){
        dist[i] = graph[s][i];
        p[i] = s;
    }
    dist[s] = 0;
    used[s] = 1;
    for(int i = 1 ; i <= num_v ; ++ i ){
        int min_v = 0;
        int min_dist = INT_MAX;
        for(int j = 1 ; j <= num_v ; ++ j ){
            if(used[j] == 0 && min_dist > dist[j]){
           //if( min_dist > dist[j]){
                min_v = j;
                min_dist = dist[j];
            }
        }
        if(min_v == 0 ) continue;
        used[min_v] = 1;
        //relax
        for(int j = 1 ; j <= num_v ; ++ j ){
            if(dist[j]  > dist[min_v] + graph[min_v][j]  &&
                     graph[min_v][j] != INT_MAX ){
               dist[j]  = dist[min_v] + graph[min_v][j] ;
               p[j] = min_v;
            }
        }
    }

    return 0;
}


void work()
{
    for(int i = 1 ; i <= num_v ; ++i ){
       bool flag =  bellmanFord(i);

       //dijkstra(i);
       if(flag == false) {
            cout << "has negative cycle" <<endl;
       }
    }
    ////

    int min_cost = INT_MAX;

    for(int i = 1 ; i <= num_v ; ++ i ){
        for(int j = 1 ; j <= num_v ; ++j){
                if(min_cost > dp[i][j]  && i != j){
                    min_cost = dp[i][j];
                }
        }
    }
    cout <<min_cost << endl;


    int min_length = INT_MAX;
    for(int i =1 ; i <= num_v ; ++i){
        dijkstra(i);
        for(int j = 1 ; j<=num_v ; ++j){

            if(dist[j] == min_cost){
                    int v = j;
                    int length  = 1;
                    while(p[v] != i){
                        length ++ ;
                        v = p[v];
                    }
                    if(length < min_length ) min_length = length;
            }//end if
        }// end for
    }
//    for(int i = 1 ; i <= num_v ; ++ i ){
//        for(int j =  1 ; j <= num_v ; ++j){
//            if(dp[i][j] == min_cost){
//                int cost = 0;
//                int length = dijkstra(i,j,cost);
//                if(cost != dp[i][j]){
//                    cout << "negative cycle" <<endl
//                }
//                if(min_length > length) min_length = length ;
//            }
//        }
//    }

    cout <<min_length<< endl;
}
int main()
{

    fin>>num_v >> num_edges;

    //init
   for(int i = 1 ; i <= num_v ; ++i ){
        for(int j = 1 ; j <= num_v ; ++ j  ){
            graph[i][j] = INT_MAX;
            if(i == j ) graph[i][j] = 0;
            //dp[i][j] = INT_MAX;
        }
    }


    for(int i = 0 ; i < num_edges ; ++ i){
        int a,b,cost;
        fin>>a>>b>>cost;
        graph[a][b] = cost ;
    }


    work();
   // return 0;

    floyd();

    int min_cost = INT_MAX;

    for(int i = 1 ; i <= num_v ; ++ i ){
        for(int j = 1 ; j <= num_v ; ++j){
                if(min_cost > dp[i][j]  && i != j){
                    min_cost = dp[i][j];
                }
        }
    }
    cout <<min_cost << endl;


    int min_length = INT_MAX;
    for(int i =1 ; i <= num_v ; ++i){
        dijkstra(i);
        for(int j = 1 ; j<=num_v ; ++j){
            if(dist[j] != dp[i][j]){
                cout << "has negative cycle" <<endl;
                dijkstra(i);
                return 0 ;
            }else if(dist[j] == min_cost){
                    int v = j;
                    int length  = 1;
                    while(p[v] != i){
                        length ++ ;
                        v = p[v];
                    }
                    if(length < min_length ) min_length = length;
            }//end if
        }// end for
    }
//    for(int i = 1 ; i <= num_v ; ++ i ){
//        for(int j =  1 ; j <= num_v ; ++j){
//            if(dp[i][j] == min_cost){
//                int cost = 0;
//                int length = dijkstra(i,j,cost);
//                if(cost != dp[i][j]){
//                    cout << "negative cycle" <<endl
//                }
//                if(min_length > length) min_length = length ;
//            }
//        }
//    }

    cout <<min_length<< endl;

    return 0;
}
