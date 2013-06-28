#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;


class Solution {
public:
    bool isPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string dest;

        for(size_t i = 0 ; i < s.size() ; i ++){
            if(isalnum(s[i])  ){
                //if(!isdigit(s[i]) )
                    dest.push_back( tolower (s[i]) );
                //else
                   // dest.push_back( (s[i]) );
            }
        }

        //bool flag = true;

        int len = dest.size();

        for(int i = 0 ; i <len /2 ; i ++){
            if(dest[i] !=  dest[len-i -1 ])
                return false;
        }

        return true;

    }
};


int main()
{
    Solution test ;

    cout << test.isPalindrome("ab2a");
    cout <<test.isPalindrome("is");

	return 0;
}
