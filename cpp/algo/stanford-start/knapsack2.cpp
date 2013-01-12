#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;



const int N = 2000000 + 10;
int value[N];
int cap[N];
int data[N];
int capsum = 0;

//2595919

int knapsack(int n)
{

    for(int i = 1 ; i <= n ; i ++){
        for(int j = capsum; j >= 1 ; j --){
            if(cap[i] <= j)
                data[j]  = max(data[j] , data[j-cap[i]]  + value[i]);
        }
    }

    return data[capsum];
}
int main()
{

    ifstream fin("knapsack1.txt");

    int n ;
    fin>> capsum >> n;
    for(int i = 1 ; i <= n ; i ++){
        fin>>value[i] >> cap[i] ;
    }

    cout << knapsack(n) << endl;

    return 0;
}

