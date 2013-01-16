#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
class fString
{
public:
    fString() {}
    fString(char *s="")
    {
        data = s;
        delete s;
    }
private :
    char * data;
};

using namespace std;
int main()
{

    char *s = new char[10];
    strcpy(s,"hello " );

    fString  f(s);

    cout << s<< strlen(s)<< s[0]<< endl;
    string s1;
   // cout << s1[2];
    return 0;
}
