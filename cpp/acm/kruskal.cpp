/*
ID:fuxiang2
PROG: agrinet
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
ofstream fout ("agrinet.out");
ifstream fin ("agrinet.in");

const int N = 105;
int mat[N][N];
int n;
int used[N];
int dist[N];

vector<pair<int,int> > edge;

int p[N]; //p指的当前集合的根节点

void Union(int a,int b)
{
	if(p[a] == -1)
		p[a] = a;
	for(int i = 1 ; i < n ; i ++)
		if(p[i] == p[b])
			p[i] = p[a]; //将原来b的块指向a所在的块

}
int find( int a)
{
	return p[a];
}
int kruskal()
{
    for(int i = 1 ; i < n ; i ++){
        int mindist = 0x33fffff;

        //得到最小的边
        for(int j = 1 ; j <= n ; j ++){
            for(int k = 1 ; k <= n ; k ++){
                if (  (used[j]==0 || used[k]==0) &&
    }

}
int main()
{
	fin>>n;


	return 0;
}

