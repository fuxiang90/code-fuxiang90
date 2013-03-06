#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int isOk(int year)
{
    set<int > ch_set;
    for(int i = 0 ; i < 4 ; i ++){

        ch_set.insert(year%10);
        year = year /10;
    }
    if(ch_set.size() == 4)
        return 1;
    else
        return 0;
}
int main()
{
    int year;
    cin>> year;
    for(int i = year + 1 ; i <= 9000 ; i ++){
        if(isOk(i) == 1){
            cout << i << endl;
            break;
        }
    }

    return 0;
}
