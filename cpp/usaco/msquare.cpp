/*
ID:fuxiang2
PROG: msquare
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
ofstream fout ("msquare.out");
ifstream fin ("msquare.in");

int basic[2][4];
const int N = 134217728+ 10;
char hash[N];
struct node{
    int data[2][4];
    string s;
};
struct node start;
struct node end;
void op(int n ,struct node & now)
{
    if(n == 1){
        for(int i = 0 ; i < 4 ; i ++){
            std::swap(now.data[0][i],now.data[1][i]);
        }
    }
    else if (n == 2){
        for(int i = 0 ; i < 2 ; i ++){
            int t = now.data[i][3];
            now.data[i][3] = now.data[i][2];
            now.data[i][2] = now.data[i][1];
            now.data[i][1] = now.data[i][0];
            now.data[i][0] = t;

        }
    }
    else if (n ==3){
        int t = now.data[0][1];
        now.data[0][1] = now.data[1][1];
        now.data[1][1] = now.data[1][2];
        now.data[1][2] = now.data[0][2];
        now.data[0][2] = t;
    }

}

long calHash(struct node n)
{
    long re = 0;
    for(int i = 0 ; i < 8 ; i ++){
        re = n.data[i/4][i%4]  -1+ (re) *8;
    }
    return re;
}

bool isTarget(struct node n){
    for(int i = 0 ; i < 8 ; i ++){
        if(n.data[i/4][i%4] != end.data[i/4][i%4])
            return false;
     }

     return true;
}
void bfs()
{
    queue<struct node> q;
    q.push(start);

    vector<int >path;

    hash[calHash(start)]  = 1;
    while(!q.empty()) {
        struct node temp = q.front();// top();
        q.pop();
        for(int i = 1 ; i <= 3 ; i ++ ){
            struct node next = temp;
            op(i,next);
            next.s.push_back('A' + i-1);

            long key = calHash(next);
            if(hash[key] == 0){
                hash[key] = 1;
                q.push(next);
            }else {
                continue;
            }

            if(isTarget(next) == true){
                fout<<next.s.size() <<endl;
                for(int i = 0  ; i < next.s.size() ; i ++){
                    if(i %60 == 0  && i != 0)
                        fout <<endl;
                    fout << next.s[i];

                }

                fout <<endl;
                return ;
            }
        }
    }

}
int main()
{

    for(int i = 0 ; i < 8 ; i ++){
        fin>>end.data[i/4][i%4];
        start.data[i/4][i%4]  =i + 1;
    }
    bfs();
    return 0;
}
