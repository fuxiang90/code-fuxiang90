#include<iostream>
#include<cmath>
#include<stdio.h>
using namespace std;

//typedef __int64_t long long

//__int64  a;
//__int64_t a;
typedef unsigned long long ull;
unsigned long long n;
unsigned long long k;
unsigned long long getMin(ull i)
{
    return (2+ (2+i-1) )*i /2 - (i-1);
}
unsigned long long getMax(ull i)
{
    return (k + (k-i + 1))*i /2 -(i-1);
}


long work()
{
    long l = 1;

    long r = k-1;

    while(l <= r){
        unsigned long mid = l + (r-l)/2;
        unsigned long long  max_n = getMax(mid);
        if(max_n == n){
            return mid;
        }else if(max_n < n){
            l = mid + 1;
        }else {
            //long long min_n = getMin(mid);

            if( mid >1 && getMax(mid-1) >= n ){
                r = mid -1;
            }else if(mid >1 && getMax(mid-1) < n){
                return mid ;
            }else if(mid == 1){
                if(getMin(mid) <= n && getMax(mid)>=n){
                    return mid;
                }
            }

        }
    }
    return -1;
}
int main()
{
    freopen("in","r",stdin);
    cin>>n>>k;
    if( n< 2 ){
        cout << 0<<endl;
    }
    else
        cout << work() <<endl;

}
