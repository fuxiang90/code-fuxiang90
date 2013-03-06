
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
const int N = 100000 + 10;
typedef long long  ll;


ll data_vec[N];
set<ll >data_set;

map<ll ,ll > data_map;
int flag[N] ;

long n,k;
long ans ;

int  main()
{
    /*
    几个错误 ，开始 以为 long 可以，后来要换成 long long
    然后 几个 特殊情况没有考虑 n==1 or k == 1的时候
    代码一定要注意对边界条件的处理
    */
    //ll x = 465919573 ;
    //cout << x * 999 << endl;
    //freopen("in","r",stdin);
    cin>>n>>k;
    for(int i = 1 ; i <= n ; i ++){
        int num;
        cin >> num ;
        data_vec[i -1] = num;
    }

    sort(data_vec + 0  ,data_vec + n);
    for(int i = 0 ; i < n ; i ++){
        data_map.insert(map<ll ,ll>::value_type(data_vec[i],i));
    }
    for(int i = 0 ; i < n ; i ++){
        if(flag[i] == 1) continue;
        ll knum = k * data_vec[i] ;
        map<ll ,ll>::iterator iter = data_map.find(knum);
        if(iter != data_map.end() ){
            flag[iter->second ] = 1;
            ans ++;
        }
    }
    if(n == 1 || k == 1)
        cout << n << endl;
    else
        cout << n - ans <<endl;

    return 0;
}
