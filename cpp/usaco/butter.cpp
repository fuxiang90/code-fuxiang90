/*
ID:fuxiang2
PROG: butter
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <algorithm>
#include <set>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;
ofstream fout ("butter.out");
ifstream fin ("butter.in");


const int N = 802;
int maxN = 0x0fffffff;
//int graph[N][N];

//pair 第一个是点 ，第二个是边的权值
vector< vector < pair<int ,int > > > graph;
int d[N];
int cow[N];
int flag[N] ;
int n,p,c;


void spfa(int start)
{
    queue<int > q;
    q.push(start);

    //初始化距离
    for(int i = 1 ; i <= p ; i ++)
        d[i] = maxN;
    d[start] = 0;

   //memset(flag,N*sizeof(int),0); //这个在usaco编译错误
   for(int i = 1 ; i<=n ; i ++) flag[i] = 0;

    flag[start] = 1;
    while(!q.empty()){

        int u = q.front();
        q.pop();

        flag[u] = 0;

        for(vector<pair<int ,int > >::iterator iter = graph[u].begin() ; iter != graph[u].end() ; iter ++ ){
            int v = iter->first;
                if( d[v]  > iter->second + d[u] ){
                    d[v] = iter->second+ d[u];

                    if( flag[v] == 0){
                        q.push(v);
                        flag[v] = 1;
                    }
                }

           // }// end if
        }//end for
    }//end while



}
int main()
{
    fin>>n>>p>>c;
    for(int i = 1; i <= n ; i ++){
        int a;
        fin>>a;
        cow[a] ++;
    }
//    for(int i =1 ; i < N ; i ++){
//        for(int j = 1 ; j < N ; j ++)
//            graph[i][j] = maxN;
//    }

    graph.resize(N);
    for(int i = 1 ; i <= c ; i ++){
        int x,y,w;
        fin>> x>>y >>w;
        graph[x].push_back(make_pair(y,w));
        graph[y].push_back(make_pair(x,w));
    }

    long minN = maxN;

    for(int i = 1 ; i <= p ; i ++){
        spfa(i);
        long t = 0;
        for(int j = 1 ; j <= p ; j ++){
            if (d[j] == maxN) {
                t = maxN;
                break;
            }
            t += cow[j]*d[j];
        }

        if (t < minN) minN = t;


    }

    fout<< minN <<endl;
    return 0;
}
