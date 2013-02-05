#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int main()
{
    string s;
    getline(cin,s);
    cout<<s<<endl;
    //for(string::size_type i=0; i!=s.size(); ++i)
     for(string::size_type  i=0;i<=s.size();++i)   //如果为for(string::size_type  i=0;i<=s.size();++i)，则出错！为什么
    {
        if(ispunct(s[i]))//判断是否为标点符号
            s[i]='@';      //将标点符号改为@
    }
    cout<<s<<endl;
    return 0;
}
