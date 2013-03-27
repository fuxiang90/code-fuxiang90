#include<iostream>

#include<string>

using namespace std;

const int N = 1000000;
int add(int one)
{
    //std::string a("1111");

    return one + 1;
}
int main()
{
    cout << (1<<0) << endl;
    for(int i = 0 ; i < N ;  i++){
        add(i);
    }
    return 0;
}
