#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

int
main()
{
     char   *p1,*p2;
     p1=(char *)malloc(20);
     p2=(char *)realloc(p1,10);
    if(p1 == p2){
        cout << "same " << endl;
    }
    //cout << sizeof(p2) << endl;
}

