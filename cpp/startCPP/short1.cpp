#include<string>
#include<iostream>
#include<map>
#include<fstream>
#include<queue>
#include<algorithm>
using namespace std;



int main()
{
    short test = 32767;

    printf("%d%d   %d", test, (test >> 8) ,sizeof(short));



    return 0;
}
