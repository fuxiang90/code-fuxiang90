/*
ID:fuxiang2
PROG: fence
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
ofstream fout ("fence.out");
ifstream fin ("fence.in");

const int N= 502;
int graph[N][N];
int degree[N];
stack<int> st;


map<int,int> m;
queue<int > q;
int n;

void dfs(int s)
{
    for(int i = 1 ; i <= n ; i ++){
        if(i != s  && graph[s][i] ){
            graph[i][s] --;
            graph[s][i] --;
            dfs(i);
        }
    }
    st.push(s);
}

void work()
{
    int s = 1;
    for(int i = 1 ; i <= n ; i ++){
        if(degree[i] % 2== 1){
            s = i ;
            break;
        }
    }

    for(int i = 1 ; i <= n ; i ++){
        if(i != s  && graph[s][i] ){
            graph[i][s] --;
            graph[s][i] --;
            dfs(i);
        }
    }
    st.push(s);
}


int main()
{
    int t;
    fin>>t;
    n= 0;
    for(int i = 1 ; i <= t ; i ++){
        int a,b;
        fin>>a>>b;
        // graph[a][b] = graph[b][a] = 1; //不能解决环的问题
        graph[a][b] ++;
        graph[b][a] ++;
        degree[a] ++;
        degree[b] ++;
        n = max(max(a,b),n);
    }

    work();
    while(!st.empty()){
        fout<<st.top()<<endl;
        st.pop();
    }

    return 0;
}
