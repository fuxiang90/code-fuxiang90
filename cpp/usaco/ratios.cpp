/*
ID:fuxiang2
PROG: ratios
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
ofstream fout ("ratios.out");
ifstream fin ("ratios.in");

struct node{
    int a,b,c;
};

struct node data[5];


int t1,t2,t3;

int A ,B,C;


int main()
{
    fin>>t1>>t2>>t3;
    for(int i = 1 ; i<= 3 ; i ++){
        fin>>data[i].a>>data[i].b>>data[i].c ;
    }

    for(int i = 0 ;  i <= 99 ; i ++){
        int A1 = data[1].a * i ;
        int B1 = data[1].b * i ;
        int C1 = data[1].c * i ;
        for(int j = 0 ; j <= 99 ; j ++){
            int A2 = data[2].a * j ;
            int B2 = data[2].b * j ;
            int C2 = data[2].c * j ;
            for(int k = 0 ; k <= 99 ; k ++){
                int A3 = data[3].a * k ;
                int B3 = data[3].b * k ;
                int C3 = data[3].c * k ;

                A = A1 + A2 + A3;
                B = B1 + B2 + B3;
                C = C1 + C2 + C3;


                if(A >= t1 && A*t2 == t1*B && B*t3 == t2 *C && ( A != 0 || B != 0 || C!= 0)){
                    fout << i << " "<< j << " " << k << " "<<  A/t1 <<endl;
                    return 0;


               }

            }
        }
    }
    fout <<"NONE"<<endl;

    return 0;
}
