

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const int N = 10000 + 10;
int value[N];
int weight[N];
int data[N][1000+10];
int weightsum = 0;

//1777086

int knapsack(int n)
{


    for(int i = 1 ; i <= n ; i ++){
        for(int j = 1; j <= weightsum ; j ++){
            if(weight[i] <= j)
                data[i][j]  = max(data[i-1][j] , data[i-1][j-weight[i]]  + value[i]);
            else
                data[i][j] = data[i-1][j];
        }
    }

    return data[n][weightsum];
}
int main()
{

    ifstream fin("knapsack1.txt");
    int n ;
    fin>> weightsum >> n;
    for(int i = 1 ; i <= n ; i ++){
        fin>>value[i] >> weight[i] ;
    }

    cout << knapsack(n) << endl;


    return 0;
}
