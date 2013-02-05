#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;



const int N = 10000  + 10;
struct node {
    int length;
    int num;
};
struct node data[N];

int main()
{
    freopen("in","r",stdin);
    int n;
    cin>>n;
    for(int i = 0 ; i < n ; ++i ) {
        cin>> data[i].length >> data[i].num;
    }
    int pre_length = data[0].length ;
    int pre_num = data[0].num;
    for(int i = 1 ; i < n ; i ++) {

        for(int j = pre_length ; j !=  data[i].length  ; j ++) {
            int t = pre_num;
            pre_num/=4 ;
            if(t % 4 != 0)
                pre_num ++ ;
        }
        data[i].num += pre_num;
        pre_length = data[i].length;
        pre_num = data[i].num;
    }

    while(pre_num > 1 ){

        pre_length ++;
        int t = pre_num;
        pre_num/=4 ;
        if(t % 4 != 0)
            pre_num ++ ;
    }
    cout << pre_length  << endl;






    return 0;
}
