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

const int MAXN = 510;
const int INF = 999999;
int  graph[MAXN][MAXN];
int  dist[MAXN];
char used[MAXN];
int Q[MAXN];
int n,h;
// 参数n表示结点数，s表示源点
int SPFA(int n, int s)
{
	// pri是队列头结点，end是队列尾结点
    int i, pri, end_i, p;
    memset(used, 0, sizeof(used));
    for(int i=0; i<MAXN; ++i)
        Q[i] = 0;
    for (i=0; i<n; i++)
        dist[i] = INF;
    dist[s] = 0;
    used[s] = 1;
    Q[0] = s; pri = 0; end_i = 1;
    while (pri < end_i)
    {
        p = Q[pri];
        for (i=0; i<n; ++i)
        {
			//更新dis
            if (dist[p]+graph[p][i] < dist[i])
            {
                dist[i] = dist[p]+graph[p][i];
                if (!used[i])     //未在队列中
                {
                    Q[end_i++] = i;
                    used[i] = 1;
                }
            }
        }
        used[p] = 0;   // 置出队的点为未标记
        pri++;
    }
    return 1;
}
int main()
{
    freopen("in","r",stdin);

    while(cin>>n>>h) {


        for(int i = 1 ; i <= n ; i ++) {
            for(int j = 1 ; j <= n ; j ++) {

                cin>>graph[i][j];
            }
        }
        int ans = 0;
        SPFA(n,1);
        ans += dist[n];
        SPFA(n,n);
        ans += dist[1];
        if( ans > h ){
            cout << -1 << endl;
        }else {
            cout << ans << endl;
        }
    }
    return 0;
}
