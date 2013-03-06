#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int Mul(int a,int b)
{
	int ans=0;
	int sign= ((a^b)>>31) & 0x01;
	a=abs(a);
	b=abs(b);
	while(b)
	{
		if(b & 0x01 )ans += a;
		b >>= 1;
		a <<= 1;
	}
	return sign?-ans:ans;
}
int main()
{

    cout << Mul(-11,11) << endl;
    cout << Mul(-11,-11) << endl;
    cout << Mul(0,11) << endl;
    cout << Mul(0,-11) << endl;
    return 0;
}
