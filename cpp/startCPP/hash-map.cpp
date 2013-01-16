#include <iostream>
#include <ext/hash_map>

#include<cstdio>
#include<cstring>
using namespace __gnu_cxx;

using namespace std;

struct eqstr{
	bool operator()(const char *s1, const char *s2)const{
		return strcmp(s1,s2) == 0;
	}
};

int main(){
	hash_map<const char *,int,hash<const char *>,eqstr> months;
	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	cout << "march -> " << months["march"] << endl;

	return 0;
}
