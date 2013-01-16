
#include <iostream>

using namespace std;

struct node
{
    int a:8;
    int b:4;
    int d:21;
    double c;

};
int main()
{
    struct node n;
    n.a = 134;
    n.b = 31;
    cout << n.a << endl;
    cout << sizeof(int)<<endl;
    cout << sizeof(double) <<endl;
    cout <<sizeof(struct node) <<endl;
}
