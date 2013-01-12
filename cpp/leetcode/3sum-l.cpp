#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace::std;

class Solution {
public:
	long RSHash(string str)
	{
		int a = 378551;
		int b = 63689;
		long hash = 0;
		for(int i = 0; i < str.size(); i++)
		{
			hash = hash * a + str[i];
			a = a * b;
		}
		return hash;
	}
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector< vector<int> > result;
		int tmp = 0;
		int flag = 0;
		int a = 0, b = 0, c = 0;
		long hash;
		string str;
		vector<int> set;
		map<long, int> mymap;
		if(num.size() < 3)
			return result;
		sort(num.begin(), num.end());
			for(int x = 0; x < num.size() - 2; x++)
			{
				a = num[x];
				for(int i = x + 1, j = num.size() - 1; i < j; )
				{
					b = num[i];
					c = num[j];
					if(a + b + c < 0)
						i++;
					else if(a + b + c > 0)
						j--;
					else
					{
						str.clear();
						str += a;
						str += b;
						str += c;
						hash = RSHash(str);
						if(mymap.find(hash) == mymap.end())
						{
							mymap[hash] = 1;
							set.push_back(a);
							set.push_back(b);
							set.push_back(c);
							result.push_back(set);
							set.clear();
						}
						i++;

					}
				}




			}
			return result;

    }

};

int main()
{


}
