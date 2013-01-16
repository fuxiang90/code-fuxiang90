#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

const int N = 100+ 1; //  暂时最多处理100 个任务

int ta;//在机器1上话费的时间
int tb;
int cost;//当前的总耗时
int best;//最少时间
int data[2][N];
int path[N];
int bestPath[N];
int n;
int used[N];
ifstream fin ("in");
ofstream fout("out");
void dfs(int i)
{
    if(i > n  ){
        if(cost < best){
            for(int i = 1 ; i <= n ; i ++)
                bestPath[i] = path[i];
            best = cost;
        }

        return;
    }

    for(int j = 1 ; j <= n ; j ++){
        if(used[j] == 0){
            int temptb = tb;
            ta += data[0][j];
            tb = max(ta,tb) + data[1][j];
            cost += tb;
            used[j] = 1;//标记被访问
            path[i] = j;
            if(cost < best)
                dfs(i + 1);
            used[j]  = 0;
            ta -= data[0][j];
            cost -= tb;
            tb = temptb;
        }
    }
}
int main()
{
    fin >> n;
    for(int i = 1 ; i<= n ; i ++){
        fin>>data[0][i] >> data[1][i];
    }

    best = 0x3fffffff;
    ta = tb = 0;
    cost = 0;
    dfs(1);
    fout << best <<endl;

    for(int i = 1 ; i <= n ; i ++)
        fout<<bestPath[i] << " " ;
    fout <<endl;
    return 0;
}
