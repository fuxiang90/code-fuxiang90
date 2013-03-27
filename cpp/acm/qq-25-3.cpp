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
const int N = 7;
int mat[N][N];
int m;
int x;
int y;

struct node{
    int x;
    int y;
    int time;
};
int dir[4][2] = {{-1,0} ,{1,0},{0,-1},{0,1}};

int main()
{
    while( cin>> mat[1][1] >> mat[1][2] >>
    mat[1][3] >> mat[1][4] >> mat[1][5] >> mat[1][6] ){

        for(int i = 2 ; i <=6 ; i ++){
            for(int j = 1 ; j <= 6 ; j ++){
                cin>>mat[i][j];
            }
        }// end for
        cin>>m;
        for(int i = 1 ; i <= m ;i ++){
            cin>>x>>y;

        }
    }
    return 0;
}
