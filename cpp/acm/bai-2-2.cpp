#include <iostream>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int N = 100000+10;
int n,m;
vector<int> ai;
vector<int> bi;

set<int>di;
int work()
{
    bool flag = true;
    while(true){
        flag = false;
        for(int i = 1; i< n ; i ++ ){
            bi[i] = ai[i+1] - ai[i];
        }
        int j = 1;
        for(int i = 1 ; i < n ; i ++){
            if( di.find(bi[i]) == di.end()){
                ai[j ++] = ai[i+1];
            }
            else {
                flag = true;
            }

        }
        n = j -1;
    }

    return n;

}
int main()
{
    freopen("in","r",stdin);
    int T;

    cin>>T;
    ai.reserve(N);
    for(int i = 1; i <= T ; i ++){

         fill_n(ai.begin(),N-1,0);
        cin>>n>>m;

        int num;

        for(int j = 1 ; j < n ; j ++){
            cin>>num;
            ai[j] =  num;
        }

        for(int j = 1 ; j <= m; j ++){
            cin>>num;
            di.insert(num);
        }


        cout << "Case " << i << ":"<<work()<<endl;
    }
    return 0;
}
