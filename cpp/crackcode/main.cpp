#include <iostream>

#include "my.h"
#include "crack5.h"
#include "crack8.h"
using namespace std;

//void swap(int & a ,int &b){
//
//    int t = a;
//    a = b;
//    b = t;
//}

void sina4(int a[] ,int len)
{
    int pos = 2;
    int next_pos = 2;
    //int flag = 1;
    while(pos <= len) {
        while(next_pos <= len && a[next_pos] <= a[pos -1 ]) {
            next_pos ++ ;
        }
        if(next_pos > len) {
            break;
        }
        swap(a[pos] ,a[next_pos]);
        pos ++;
    }
}
int main()
{

    //int a[] = { 0, 1, 1,2,3,3,5,6,7};
    int a[] = { 0, 1, 1,1,1,1,1,1,1};
    sina4(a,8);

    for(int i = 1 ; i <= 8 ; i ++ ){
        cout << a[i] << endl;
    }
    //fun3(12);
    //fun8p5(2,0);
    cout << "Hello world!" << endl;
    return 0;
}
