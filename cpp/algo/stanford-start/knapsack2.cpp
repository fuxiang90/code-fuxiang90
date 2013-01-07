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
int weight[N];
int data[N];
int weightsum = 0;

//2595919

int knapsack(int n)
{

    for(int i = 1 ; i <= n ; i ++){
        for(int j = weightsum; j >= 1 ; j --){
            if(weight[i] <= j)
                data[j]  = max(data[j] , data[j-weight[i]]  + value[i]);

        }
    }

    return data[weightsum];
}
int main()
{

    ifstream fin("knapsack2.txt");

    int n ;
    fin>> weightsum >> n;
    for(int i = 1 ; i <= n ; i ++){
        fin>>value[i] >> weight[i] ;
    }

    cout << knapsack(n) << endl;

    return 0;
}

