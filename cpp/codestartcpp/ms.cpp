#include <iostream>

using namespace std;

class a
{
public:
    virtual void f()
    {
        std::cout << "a" <endl;
    }

    void f() const {
        cout << "a const" <endl;
    }
};
class b : public a
{
     void f(){
        cout << "b" <endl;
    }

    void f() const {
        cout << "b const" <endl;
    }
};

int main()
{
    a * a_t = new b();
    a_t ->f();
	return 0;
}
