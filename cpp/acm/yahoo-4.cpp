#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
const int N = 1000;
int data[N][N];

int dest[N][N];
int row,col;
//set<int> num_set;
int p = 1073676287;
int h[N*N];

int sx,sy;
int ex,ey;

int dir[4][2] = { {-1,0} ,{1,0},{0,-1},{0,1} };

int isOk(int x ,int y){

    if(x >=0 && x < row  && y >=0 && y < col )
        return 1;
    return 0;
}


vector <int > re;

void dfs(int x,int y)
{


    for(int i = 0 ; i < 4 ; i ++){


    }
}

int main()
{
    int t;
    scanf("%d%d"&row,&col);

    for(int i = 0 ; i < row ; i ++){
        for(int j = 0 ; j < col ; j ++){
            scanf("%d",&data[i][j]);
        }
    }

     for(int i = 0 ; i < row ; i ++){
        for(int j = 0 ; j < col ; j ++){
            scanf("%d",&dest[i][j]);
        }
    }
    int c;
    while(scanf("%d",&c)!= EOF){
        h[c] = 1;

    }


	return 0;
}
