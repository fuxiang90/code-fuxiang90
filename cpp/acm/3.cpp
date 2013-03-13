#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

void fun(vector <int > A ,vector <int > B,vector <int>C ,vector<int > re)
{

    int i ,j,k;
    int maxN = 0x3fffffff;
    A.push_back(maxN);
    B.push_back(maxN);
    C.push_back(maxN);
    i = j = k = 0;
    while( i < A.size() || j <  B.size() || k < C.size() ){

        if (A[i] == maxN && B[j] == maxN && C[k] == maxN)
            break;
        if ( A[i]  < min(B[j],C[k] ) ){
            re.push_back(A[i]);
            i ++;
        }
        else if( B[j]  < min(A[i] ,C[k]) ){
            re.push_back(B[j]);
            j ++;
        }
        else {
            re.push_back(C[k]);
            k ++;
        }

    }

}

int main()
{
    vector <int > A;
    vector<int > B ;
    vector <int > C;
    vector <int > c;

         int k;

         for (k=2 ; ++k < 4;k++)

             {

                ++k;

             }


    return 0;
}
