#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 300;
int data[N];
int n;


int ans ;

void dfs(int l ,int r ,int num ){

    if(l > r) return ;
    if(l + 1 == r){
        if(data[l+1] == data[r]){
            num +=2;

        }
        if(num > ans){
            ans = num;
        }

        return;
    }
    if(l == r){

        num ++ ;
        if(num > ans){
            ans = num;
        }
        return ;
    }

    int lpos = l; int rpos = r;
    if(data[l] == data[r]){
        while(data[lpos+1] == data[l] || data[lpos+1] < data[l]){
            lpos ++;
        }
        while(data[rpos -1] == data[r] || data[rpos -1] < data[r]){
            rpos --;
        }
        dfs(lpos+1,rpos-1,num+2);
        return ;
    }

    while(lpos <= r && data[lpos] != data[r] ){
        lpos ++;
    }
    dfs(lpos ,r ,num);


     while(rpos >= r && data[rpos] != data[l] ){
        rpos --;
    }
    dfs(l ,rpos ,num);


}
int main()
{
    freopen("in","r",stdin);
    int t;
    cin>>t;
    for(int i = 1 ; i<= t ; i++){
        cin>>n;
        for(int j = 1 ; j <= n ; j ++){
            cin>>data[j];
        }
        dfs(1,n,0);
        cout << ans <<endl;
        ans = 0;
    }
}
