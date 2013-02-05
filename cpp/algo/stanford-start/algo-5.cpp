#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include <list>
#include <vector>
#include <iostream>
#include<fstream>
#include<set>
#include<algorithm>
using namespace std;


set<int> mySet;


int solve(int sum)
{
	set<int>::iterator iter = mySet.begin();

	for( ;  iter != mySet.end() ;iter ++)
	{
		if(*iter > sum )
			return 0;

		if(mySet.find(sum-(*iter)) != mySet.end() )
			return 1;
	}

	return 0;
}

int main()
{
	//char *filename = "HashInt.txt";
	ifstream input("HashInt.txt");
	
	int data[9] = {
				231552,234756,596873,648219,726312,981237,988331,1277361,1283379
	};
	int x = 0;
	while (input >> x)
	{
		mySet.insert(x);
	}
	
	for(int i = 0 ; i < 9 ; i ++)
	{
		std::cout << solve(data[i]);
	}
	return 0;

}