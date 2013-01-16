#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

struct ci_char_traits:public char_traits<char>
{
    static bool eq(char c1 ,char c2)
    {
        return  toupper(c1) == toupper(c2);
    }
    static bool lt(char c1 ,char c2)
    {
        return  toupper(c1) < toupper(c2);
    }
    static int compare(const char * s1 , const char * s2 , size_t n)
    {
        //return memicmp(s1,s2,n);
        for(size_t i = 0 ; i < n ; i ++){
            if(lt(*s1,*s2)){
                return -1;
            }else if(!eq(*s1,*s2)){
                return 1;
            }
            ++ s1;
            ++ s2;
        }
        return 0;

    }
    static const char * find(const char  *s ,int n ,char a)
    {
        while(n-- > 0  && toupper(*s) != toupper(a)) {
            ++ s;
        }
        return n >=0?s:0;
    }
};

typedef basic_string<char ,ci_char_traits> ci_string;
int main()
{

    ci_string s1 = ("aac");
    if(s1 == "AAC"){
        cout <<"yes" << endl;
    }
    return 0;
}
