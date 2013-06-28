// constructing multisets
#include <iostream>
#include <set>

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};
using namespace std;

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

int main ()
{


    std::multiset<int> first;                          // empty multiset of ints

	int myints[]= {10,20,30,20,20};
	std::multiset<int> second (myints,myints+5);       // pointers used as iterators

	for(std::multiset<int>::iterator iter = second.begin() ; iter != second.end() ;iter ++){
		std::cout << *iter <<endl;

	}

	std::multiset<int> third (second);                 // a copy of second

	std::multiset<int> fourth (second.begin(), second.end());  // iterator ctor.

	std::multiset<int,classcomp> fifth;                // class as Compare

	bool(*fn_pt)(int,int) = fncomp;
	std::multiset<int,bool(*)(int,int)> sixth (fn_pt); // function pointer as Compare

	return 0;
}
