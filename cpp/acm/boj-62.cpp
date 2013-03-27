#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


int n ;
int K,x,y;
int a,b;
class ModNode
{
public:
    int a;
    int b;

    bool operator < (const  ModNode & m) const{
        return make_pair(a,b) < make_pair(m.a ,m.b);
    }
};
class state
{
public:
    int m; //表示多少位x
    int n;
    int mod;
    state(int _m ,int _n ,int _mod ){
        m= _m;
        n = _n;
        mod = _mod;
    }
};

int compute(int m,int n){

    int mod_num = 0;
    //int mod = 0;
    for(int i = 0 ; i < m ; i ++  ){
        mod_num = (mod_num)%K *(10%K) %K;
        mod_num = (mod_num + x%K)%K;
    }

     for(int i = 0 ; i < n ; i ++ ){
         mod_num = (mod_num)%K *(10%K) %K ;
         mod_num = (mod_num + y%K)%K;
    }

    return mod_num;

}

int compute(int m,int n ,ModNode & mod_node){

    int mod_num = 0;
    //int mod = 0;
    for(int i = 0 ; i < m ; i ++  ){
        mod_num = (mod_num)%K *(10%K) %K;
        mod_num = (mod_num + x%K)%K;
    }
    mod_node.a = mod_num;

    int mod_b = 0;
    for(int i = 0 ; i < n ; i ++ ){
         mod_num = (mod_num)%K *(10%K) %K ;
         mod_num = (mod_num + y%K)%K;

        mod_b = (mod_b)%K *(10%K) %K ;
        mod_b = (mod_b + y%K)%K;
    }

    mod_node.b = mod_b;

    return mod_num;

}
void work()
{
    set <ModNode> mod_set;
    queue<state> q;


    state t(1 ,0 , compute(1,0));
    q.push(t);
    ModNode tnode ;
    compute(1,0,tnode);
    mod_set.insert(tnode);
    int flag = 0;
    while(!q.empty()){
        state  top = q.front();
        q.pop();
        int mod_num = compute(top.m + 1 , top.n ,tnode);
        if(mod_set.find(tnode) == mod_set.end()){
            state t(top.m + 1 , top.n ,mod_num);
            mod_set.insert(tnode);
            q.push(t);
        }
        if(mod_num == 0){
            flag = 1;
            cout << top.m+1 << " " << top.n << endl;
            break;
        }
       mod_num =  compute(top.m + 1 , top.n ,tnode);
       if(mod_set.find(tnode) == mod_set.end()){
            state t(top.m  , top.n + 1,mod_num);
            mod_set.insert(tnode);
            q.push(t);
        }
        if(mod_num == 0){
            flag = 1;
            cout << top.m << " " << top.n + 1<< endl;
            break;
        }

    }//end while

    if(flag == 0 )
        cout << "No such number!" <<endl;
}
int main()
{
    freopen("in","r",stdin);
    cin >> n ;
    for(int i = 1 ; i <= n ; i ++){
        cin>> K >>x >>y;
        work();
    }
    return 0;
}
