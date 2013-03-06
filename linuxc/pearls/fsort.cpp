#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<set>
using namespace std;

int main()
{
    ifstream fin("in");
    int data;
    vector<int > vec;
    while(fin>> data){
        vec.push_back(data);
    }
    sort(vec.begin() ,vec.end());
    return 0;
}
