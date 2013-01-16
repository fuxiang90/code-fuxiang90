#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
//#include <limits.h>
using namespace std;

const int INT_MAX = 0x3fffffff;

 ifstream fin("g2.txt");

 const int N = 1000 + 2;
 int num_edges;
 int num_v;
 int graph[N][N];
 int dp[N][N];

// void bellmanFord()
// {
//
// }

void apsp()
{
    for(int i = 1 ; i <= num_v ; ++ i ){
        for(int j = 1 ; j <= num_v ; ++j){
                dp[i][j] = graph[i][j];
        }
    }

    for(int k = 1 ; k <= num_v ; ++ k){
        for(int i = 1 ; i <= num_v ; ++ i ){
            for(int j = 1 ; j <= num_v ; ++j){
                if( dp[i][j]  < dp[i][k] + dp[k][j])
                    dp[i][j] = dp[i][k] + dp[k][j];
            }
        }
    }
}

// return
// length of the short path of s to d
int dijkstra(int s ,int d)
{
    int dist[N];
    int used[N] = {0};
    int p[N];
    for(int i = 1 ; i <= num_v ; ++i){
        dist[i] = graph[s][i];
        p[i] = s;
    }
    dist[s] = 0;
    used[s] = 1;
    for(int i = 1 ; i < num_v ; ++ i ){
        int min_v = 0;
        int min_dist = INT_MAX;
        for(int j = 1 ; j < num_v ; ++j ){
            if(used[j] == 0 && min_dist > dist[j]){
                min_v = j;
                min_dist = dist[j];
            }
        }
        used[min_v] = 1;
        for(int j = 1 ; j <= num_v ; j ++){
            if(dist[j]  > dist[min_v] + graph[min_v][j] ){
               dist[j]  = dist[min_v] + graph[min_v][j] ;
               p[j] = min_v;
            }
        }
    }
    int v = d;
    int length = 1;
    while(p[v] != s){
        length ++ ;
        v = p[v];
    }
    return length;
}
int main()
{

    fin>>num_v >> num_edges;

    for(int i = 1 ; i <= num_v ; ++i ){
        for(int j = 1 ; j <= num_v ; ++ j  ){
            graph[i][j] = INT_MAX;
        }
    }
    for(int i = 0 ; i < num_edges ; ++ i){
        int a,b,cost;
        fin>>a>>b>>cost;
        graph[a][b] = cost ;
    }
    apsp();
    int min_cost = INT_MAX;
    for(int i = 1 ; i <= num_v ; ++ i ){
        for(int j = 1 ; j <= num_v ; ++j){
                if(min_cost > dp[i][j]){
                    min_cost = dp[i][j];
                }
        }
    }
    int min_length = INT_MAX;
    for(int i = 1 ; i <= num_v ; ++ i ){
        for(int j =  1 ; j <= num_v ; ++j){
            if(dp[i][j] == min_cost){
                int length = dijkstra(i,j);
                if(min_length > length) min_length = length ;
            }
        }
    }
    cout <<min_cost << endl;
    cout <<min_length<< endl;

    return 0;
}
