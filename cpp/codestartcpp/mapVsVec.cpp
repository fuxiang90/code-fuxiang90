#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<cstdio>
#include<list>
using namespace std;

const int N = 3000000;
void vec()
{
    vector<int> vec_i;
    vec_i.resize(N+2);
    for(int i = 1 ; i<= N ; i ++) {
        vec_i[i] = i;
    }
     cout << "done" << endl;
    getchar();
}
void vec3()
{
    vector<int> vec_i;
    //vec_i.resize(N+2);
    for(int i = 1 ; i<= N ; i ++) {
        vec_i.push_back(i);
    }
     cout << "done" << endl;
    getchar();
}

void vec2()
{
    int * data ;
    data = new int[N+2];

    for(int i = 1 ; i<= N ; i ++) {
        data[i] = i;
    }
     cout << "done" << endl;
    getchar();
}

void listFun()
{
    list<int> vec_i;
    //vec_i.resize(N+2);
    for(int i = 1 ; i<= N ; i ++) {
        vec_i.push_back(i);
    }
    cout << "done" << endl;
    getchar();
}
void mapFun()
{
    map<int,int> map_i;

    for(int i = 1 ; i<= N ; i ++) {
        map_i.insert(map<int,int>::value_type(i,i));
    }
     cout << "done" << endl;
    getchar();
}

void setFun()
{
    set<int> set_i;

    for(int i = 1 ; i<= N ; i ++) {
        set_i.insert(i);
    }
    cout << "done" << endl;
    getchar();

}
struct node{
    int a;
    //set<int> b_set;
};

void setFun2()
{
    vector<struct node> node_vec;
    node_vec.resize(N);
      cout << "done" << endl;
    getchar();
}
int main()
{

    setFun2();

    return 0;
}
