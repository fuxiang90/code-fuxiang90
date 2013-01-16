#include <iostream>
#include <string>
#include <ctime>
#include <string.h>
using namespace std;
int main()
{
    string s = "我是中国人";

    char *s1 = "hello ";

    cout << strrev(s1);

    cout << s.substr(0,s.size() - 3) << endl;

    cout <<s.substr(s.size() -3 , 3);
}
