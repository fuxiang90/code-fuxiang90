#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class nodec
{
public:
int a;
int b;
double c;
};

struct nodes
{
int a;
int b;
double c;
};

vector<nodec> node_vec;
nodec * node_ptr;
const int N =10000000;

void test1()
{
    node_vec.resize(N);
    for(int i = 0 ; i < N ; i ++){
        node_vec[i].a = i;
        node_vec[i].b = i;
        node_vec[i].c = i;
    }
}

void test2()
{
    node_ptr = (nodec * )malloc(N*sizeof(nodec));
     for(int i = 0 ; i < N ; i ++){
        node_ptr[i].a = i;
        node_ptr[i].b = i;
        node_ptr[i].c = i;
    }
}
int main()
{
    test2();
    int a;
    cin>>a;
    return 0;
}
