#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main()
{
    long long   n ,k;
    while(cin>>n>>k){
        //scanf("I64I64",&n,&k);
        long long odd_num = (n/2) + n%2;
        //int even_num = n/2;

        if(k <= odd_num ){
            cout  <<  2*(k-1) +1 << endl;//printf("%I64\n",2*(k-1) +1);
        }else {
            k -= odd_num;
            //printf("%I64\n",2*(k) );
            cout << 2*k <<endl;
        }

    }
	return 0;
}
