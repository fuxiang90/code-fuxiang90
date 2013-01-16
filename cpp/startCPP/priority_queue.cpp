#include<string>
#include<iostream>
#include<map>
#include<fstream>
#include<queue>
#include<algorithm>
using namespace std;

struct base
{
    int a;
    int b;
    bool operator < (const struct base & n) const{
        return make_pair(a,b) > make_pair(n.a ,n.b);
    }
    base(int _a ,int _b):a(_a),b(_b){}
};

struct road: base
{
    int c;
};
int main()
{

    base b1(1,2);
    base b2(2,3);

    priority_queue< struct base> q;
    q.push(b1);
    q.push(b2);

    //for_each(q.begin() ,q,end() ,"cout << ")
//    for(priority_queue<struct base>::iterator it = q.begin() ; it != q.end() ; it ++){
//        cout <<it->a<<endl;
//    }
     while(!q.empty()){
        cout << q.top().a << endl;;
        q.pop();
     }

    return 0;
}
