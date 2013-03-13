#include<stdio.h>
#include<string.h>
#include<queue>
#include<iostream>
using namespace std;

int dp[101][101], map[101][101];

struct node
{ int x,y;
};

int dir[4][2] = { {-1,0} ,{0,1},{1,0},{0,-1} //上 ，右 ，下，左
};
int n,k;
queue<node>S;

int isSave(int x ,int y)
{
    if(x >= 0 && x < n && y < n && y >= 0)
        return 1;
    return 0;
}
int BFS()
{
    while(!S.empty()) S.pop();
    node cur; cur.x=0,cur.y=0;
    S.push(cur);
    int ans = dp[0][0];
    while( !S.empty() )
    {
         cur = S.front(); S.pop();
         int i = cur.x, j = cur.y;
         for(int x = 1; x <= k; x++ )
         {
             for(int m = 0 ; m < 4 ; m ++)
             {

                 int newx = i + x*dir[m][0] ;
                 int newy = j + x*dir[m][1] ;
                if( isSave(newx,newy) && map[newx][newy] > map[i][j]
                   && (dp[newx][newy] < dp[i][j] + map[newx][newy]) )

                   {
                       node next ;
                       next.x = newx,next.y = newy;
                       dp[newx][newy] = dp[i][j] + map[newx][newy];
                       S.push(next);
                       if(dp[newx][newy] > ans ) ans = dp[newx][newy] ;

                   }
             }

         }
    }
    return ans;
}
int main()
{
    while(scanf("%d%d",&n,&k),n!=-1&&k!=-1 )
    {
          for(int i = 0; i < n; i++ )
              for(int j = 0; j < n; j++ )
                  scanf("%d",&(map[i][j]));
          memset(dp,0,sizeof(dp));
          dp[0][0] = map[0][0];
          printf("%d\n",BFS());
    }
    return 0;
}
