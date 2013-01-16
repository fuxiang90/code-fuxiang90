

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
using namespace std;


const int N = 100 + 10;
int value[N];
int cap[N]; /*每个物品的容量*/
int data[N][100000+10];
int capsum = 0;/*背包的总容量*/

//1777086

int knapsack(int n)
{
//    for(int i = 0 ; i <= capsum ; i ++){
//        data[0][i] = 0;
//    }
    for(int i = 1 ; i <= n ; i ++){
        for(int j = 1; j <= capsum  ; j ++){
        //for(int j = capsum; j >= 1 ; j --){
            //data[i][j] = data[i-1][j];
            if(cap[i] <= j)
                data[i][j]  = max(data[i-1][j] , data[i-1][j-cap[i]]  + value[i]);
            else
                data[i][j] = data[i-1][j];
        }
    }

    return data[n][capsum];
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
