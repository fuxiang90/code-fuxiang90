#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    int nfeature = 50000;
    int SIFTN = 128;
    double **pszDiscriptor;
    *pszDiscriptor = (double * ) malloc(nfeature * sizeof(double *));
    for(int i = 0 ; i < nfeature ; i ++){
        *(pszDiscriptor + i) = (double *) malloc(sizeof(double) * SIFTN );
    }
    return 0;
}
