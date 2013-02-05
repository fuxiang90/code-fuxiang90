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
    int T;
    cin>>T;
    for(int i = 0 ; i < T ; ++ i ){
        int degree ;
        cin>>degree ;
        int n = 360/(180 - degree);
        if(  360 ==  n* (180 - degree)){
            cout << "YES" << endl;
        }else {
             cout << "NO" << endl;
        }
    }
    return 0;
}
