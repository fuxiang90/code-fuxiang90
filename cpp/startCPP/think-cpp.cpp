
# include<iostream>
#  include<cstdlib>
# include<string>
using namespace std;


void in(int *&i)
{
    i ++;
}
int main()
{
    //system("ls"); //这里尽然会将内容输入到 bash

    int ii = 4;
    int *i = &ii;
    cout << i << endl;
    in(i);
    cout << i << endl;
    string a("123");
    string b("123");

    if(a == "123")
        cout<< "equal";
    return 0;
}
