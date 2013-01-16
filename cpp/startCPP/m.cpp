# include<iostream>

using namespace std;

#define BASE_DATA int fd;int type;
struct parent
{
    BASE_DATA
};
struct child1
{
    BASE_DATA
    int c1;//data of child1;
};
struct child2
{
    BASE_DATA
    int c2;//data of child2;
};

int main()
{
    struct child1 a = {1,1,2};
    struct child2 b = {1,2,3};
    struct parent *p = &a;
    //struct parent *p = (struct child2*)&b;

    if (p->type == 1)
    {
        cout << (struct child1 *)p->c1<< endl;
    }
    else if (p->type == 2)
    {
        //cout << p->c2 << endl;
        cout << (struct child2 *)p->c2 << endl;
    }

    return 0;
}
