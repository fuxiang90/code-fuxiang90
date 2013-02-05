#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <bitset>
using namespace std;


const int INT_MAX = 0x1fffffff;

ifstream fin("tsp.txt");

const int N  = 26;
int n = 0;
double graph[N][N];
struct node{
    double x;
    double y;
};
struct node pos[N];
double min_dist =  INT_MAX*1.0;
int used[N];


class TspNode{
public:
    bitset<25> mbit;
    double mdist;
    TspNode(){}
    //TspNode(TspNode & m){
        //mbit = m.mbit;
       // mdist = m.mdist;
   // }
};

vector <vector < TspNode > > A;

const int M = (1<<25)+10;

//vector < vector< TspNode > > B;
double dist(node & a ,node & b)
{
    return sqrt(  (a.x-b.x)*(a.x-b.x) + (a.y-b.y)* (a.y-b.y) ) ;
}
void pailie(int deep  ,int & deep_limit ,int d )
{
    if(deep == deep_limit){

        for(int i = 2 ; i<= n ; ++i){
            for(vector < TspNode >::iterator it = A[deep-1].begin()  ;
                    it != A[deep-1].end() ; it ++  ){

            }
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

double ** L;
void tsp()
{

    L = (double **) malloc(M*sizeof(double *));
    for(int i = 0 ; i < M ; i ++){
        L[i] = (double *)malloc(sizeof(double )*N);
        if(L[i] == NULL){
            cout << "error" <<endl;
            return ;
        }
    }

    A.resize(N+1);
    for(int i = 1 ; i <= n ; i ++){
        A[i].resize(n+1);
    }

    for(int i = 1 ; i <= n ; ++i){
        A[0][1].mbit[i] = 1;
        if(i == 1) {
            A[0][1].mdist = 0;
        }
        else {
            A[1][i].mdist = INT_MAX *1.0;
        }
    }



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
    tsp();
//    for(int i = 1 ; i <= n ; ++i){
//        //memset(used,0,sizeof(used));
//        fill(used + 0 ,used+ N ,0);
//        tsp(0,0,1,1);
//    }

    cout << min_dist <<endl;
    return 0;
}
