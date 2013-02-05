#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include <list>
#include <vector>
#include <iostream>
#include<fstream>
#include<set>
#include<algorithm>
using namespace std;


const int N = 875714 + 10;
vector < list<int > > graph;
vector < list<int > > graphrev;
vector< list <int > > graph2;

int t ;
int s;
int M;
vector<int> f;
vector<int> used;
vector<int> leader;

vector<int > re;
void dfs(int node)
{
	used[node] = 1;
	leader[node] = s;
	list<int> link = graphrev[node];
	list<int>::iterator iter;
	for(iter = link.begin() ; iter != link.end() ; iter ++)
	{
		int next = *iter;
		if(used[next] == 0)
		{
			dfs(next);
		}
		
	}
	t ++;
	f[node] = t;

}

void dfs2(int node)
{
	used[node] = 1;
	list<int> link = graph2[node];
	list<int>::iterator iter;
	for(iter = link.begin() ; iter != link.end() ; iter ++)
	{
		int next = *iter;
		if(used[next] == 0)
		{
			dfs2(next);
		}

	}
	t ++;
}
void dfs_loop()
{
	s = 0;
	t = 0;
	for(int i = M ; i >= 1 ; i --)
	{
		s = i;
		if(used[i] == 0)
		{
			dfs(i);
		}
	}

	for(int i = 1 ; i <= M ; i ++)
	{
		list<int > temp = graphrev[i];
		list<int >::iterator iter ;
		for(iter = temp.begin()  ; iter != temp.end() ; iter ++)
		{
			int y = *iter;
			if(graph2[f[y]].empty())
			{
				list<int > l(1,f[i]);
				graph2[f[y]] = l;
			}
			else
				graph2[f[y]].push_back(f[i]);
		}

		used[i] = 0;
	}
	
	for(int i = M ; i >= 1 ; i --)
	{
		if(used[i] == 0)
		{
			t = 0;
			dfs2(i);
			re.push_back(t);
		}
	}
}


int main()
{
	graph.resize(N);
	used.resize(N);
	graphrev.resize(N);
	f.resize(N);
	leader.resize(N);
	graph2.resize(N);
	ifstream  input("SCC.txt");
	int x,y;
	while(input >> x>>y)
	{
		if( graph[x].empty() )
		{
			list<int > l(1,y);
			graph[x] = l;
		}
		else
			graph[x].push_back(y);

		if(graphrev[y].empty())
		{
			list<int > ll (1,x);
			graphrev[y] = ll;
		}
		else
			graphrev[y].push_back(x);

		if(M < y)
			M = y;
		if(M <x )
			M = x;
	}

	dfs_loop();
	
	sort(re.begin(),re.end());

	vector<int>::iterator iter;

	for(iter = re.begin() ; iter != re.end() ; iter  ++)
	{
		cout << *iter << endl;
	}


	return 0;

}