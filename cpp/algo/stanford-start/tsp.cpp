#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;


const int INT_MAX = 0x1fffffff;

ifstream fin("tsp.txt");

const int N  = 100;
int n = 0;
double graph[N][N];
struct node{
    double x;
    double y;
};
struct node pos[N];
double min_dist =  INT_MAX*1.0;
int used[N];
/*
暴力 tsp n! 的复杂度
*/
void tsp(int deep ,double dist,int s ,int p)
{
    if(deep == n){
        if(dist + graph[p][s] < min_dist)
            min_dist = dist + graph[p][s];
        return ;
    }

    for(int i = 1 ; i <= n ; i ++){
        if(used[i] == 0){
            used[i] = 1;
            dist = dist +graph[p][i];
            tsp(deep +1 ,dist,s ,i);
            dist = dist -graph[p][i];
            used[i]= 0;
        }
    }
}

double A[N][N];
void tsp2()
{
    for(int i = 1 ; i <= n ; ++i){
        if(i == 1) A[1][i] = 0;
        else A[1][i] = INT_MAX *1.0;
    }

    for(int i = 2 ; i <= n ; ++i ){
        for(int j = 1 ; j <= n ; ++ j ){

            double temp_min_dist = INT_MAX*1.0;
            for(int k = 1 ; k <= n ; ++k){
                if(temp_min_dist < A[i-1][k] + graph[k][j])
                    temp_min_dist= A[i-1][k] + graph[k][j];
            }
            A[i][j] = temp_min_dist;
        }
    }
}

double B[N][N];
void pailie(int deep  ,int & deep_limit ,int d )
{
    if(deep == deep_limit){

        for(int i = 1 ; i<= n ; ++i){
           if(used[i] == 0 && B[deep][d]  > A[deep-1][i] + graph[i][d])
                B[deep][d]  = A[deep-1][i] + graph[i][d];
        }
    }

    for(int  i= 1 ; i <= n ; i ++){
        if(used[i] == 0){
            used[i] = 1;
            pailie(deep + 1,deep_limit,i);
            used[i] = 0;
        }
    }
}

void tsp3()
{
    for(int i = 1 ; i <= n ; ++i){
        if(i == 1) A[1][i] = 0;
        else A[1][i] = INT_MAX *1.0;
    }

    for(int i =1 ; i <= n ; ++i){
        for(int j = 1 ; j <= n ; ++j){
            B[i][j] = INT_MAX*1.0;
        }
    }
    for(int i = 2 ; i <= n; ++i){
        fill(used+0,used+N,0);
        used[1] = 1;
        pailie(1,i,0);
        for(int j = 1 ; j <= n ; j ++){
            A[i][j]= B[i][j];
        }
    }

    min_dist = INT_MAX*1.0;
    for( int i = 1 ; i <= n ; i ++){
        if(min_dist < A[n][i] + graph[i][1])
            min_dist = A[n][i] + graph[i][1];
    }

    cout << min_dist <<endl;
}
double dist(node & a ,node & b)
{
    return sqrt(  (a.x-b.x)*(a.x-b.x) + (a.y-b.y)* (a.y-b.y) ) ;
}
int main()
{
    fin>>n;
    for(int i = 1 ; i <= n ; ++i){
        double a,b;
        fin>>a>>b;
        pos[i].x = a;
        pos[i].y = b;
    }
    for(int i =1 ; i <= n ; ++i){
        for(int j = 1 ; j <= n ; ++ j){
            if(i ==j ) graph[i][j] = 0;
            else {
                graph[i][j] = dist(pos[i],pos[j]);
            }
        }
    }
    tsp3();
//    for(int i = 1 ; i <= n ; ++i){
//        //memset(used,0,sizeof(used));
//        fill(used + 0 ,used+ N ,0);
//        tsp(0,0,1,1);
//    }

    cout << min_dist <<endl;
    return 0;
}
