#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const int N = 100000 + 10;
int n,m;
int data[N];

struct node
{
    int l;
    int r;
};
struct node index[N];
int flag ;

void work()
{
//    int pos = 1;
//    while(pos+1 <= n && data[pos + 1] >= data[pos ] ){
//        pos ++;
//    };
//    // 如果数列全是递增的情况
//    //if(pos  >= n ){
//     //   flag = 1;
//    //    return;
//    //}
//    index[1].l = pos + 1;
//    while(pos + 1<= n && data[pos + 1] <= data[pos ] ){
//        pos ++;
//    };
//    index[1].r = pos ;
//
//
//    for(int i = 2 ; i <= n ; i ++){
//        if(index[i-1].l != 0  &&(index[i-1].r > i)){
//            if(data[i] >= data[i-1]){
//                index[i].l = index[i-1].l;
//                index[i].r = index[i-1].r;
//            }else{
//                index[i].l = i;
//                index[i].r = index[i-1].r;
//            }
//        }else{
//            int pos = i;
//            while(pos+1 <= n && data[pos+1] >= data[pos] ){
//                pos ++;
//            };
//            index[i].l = pos + 1;
//            while(pos + 1<= n && data[pos + 1] <= data[pos ] ){
//                pos ++;
//            };
//            index[i].r = pos ;
//        }
//    }
    int pos = 1;
    while(pos+1 <= n && data[pos + 1] >= data[pos ] ){
        pos ++;
    };
    // 如果数列全是递增的情况
    //if(pos  >= n ){
     //   flag = 1;
    //    return;
    //}
    index[1].l = pos + 1;
    while(pos + 1<= n && data[pos + 1] <= data[pos ] ){
        pos ++;
    };
    index[1].r = pos ;


    for(int i = 2 ; i <= n ; i ++){
        if(index[i-1].r != 0  &&(index[i-1].r > i)){
            index[i].r = index[i-1].r;
        }else{
            int pos = i;
            while(pos+1 <= n && data[pos+1] >= data[pos] ){
                pos ++;
            };
            index[i].l = pos + 1;
            while(pos + 1<= n && data[pos + 1] <= data[pos ] ){
                pos ++;
            };
            index[i].r = pos ;
        }
    }
}
int main()
{
    //freopen("in","r",stdin);
    cin>>n>>m;
    for(int i = 1 ; i <= n ; i ++){
        cin>> data[i];
    }
    work();
    int a,b;
    for(int i = 1 ; i <= m ; i ++){
        cin>>a>>b;
        if(a == b || a == n || (b-a) == 1){
            cout << "Yes"<<endl;
        }else{
            if( (flag == 0 ) && b  <= index[a].r ){
                cout << "Yes"<<endl;
            }else{
                cout << "No" <<endl;
            }
        }
    }

    return 0;
}
