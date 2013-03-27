#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<cstdio>
using namespace std;

int main()
{
    map<pair<int ,int> ,int> pair_map;

    pair_map.insert(map<pair<int ,int> ,int>::value_type(make_pair(1,2),2));
    pair_map.insert(map<pair<int ,int> ,int>::value_type(make_pair(1,3),2));
    pair_map.insert(map<pair<int ,int> ,int>::value_type(make_pair(1,2),2));
    pair_map.insert(map<pair<int ,int> ,int>::value_type(make_pair(2,2),2));
    return 0;
}
