/*
ID: fuxiang2
PROG: kimbits
LANG: C++
*/
#include <iostream>
#include <cstdio>
using namespace std;
long long c(long a,long b){
	if(a<b)
		return 0;
	long long res=1;
	for(long i=1;i<=b;i++){
		res*=(a-i+1);
		res/=i;
	}
	return res;
}
long long superC(long a,long b){
	long long res=0;
	for(long i=0;i<=b;i++)
		res+=c(a,i);
	return res;
}
long long ans[100],index,maxGe,wei;
void fun(long wei,long long index,long left){
	if(wei==0)
		return ;
	long long done=superC(wei-1,left);
	ans[wei]=!(done>=index);
	if(done>=index)
		fun(wei-1,index,left);
	else
		fun(wei-1,index-done,left-1);
}
int main(){
	freopen("kimbits.in","r",stdin);
	freopen("kimbits.out","w",stdout);
	cin>>wei>>maxGe>>index;
	fun(wei,index,maxGe);
	for(long i=wei;i>=1;i--)
		cout<<ans[i];
	cout<<endl;
	return 0;
}
