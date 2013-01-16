
#include <iostream>

using namespace std;

class CFoo_pimpl; //申明一下  然后再在cpp 文件中定义细节 和 实现

class CFoo
{
public:
    CFoo();
    ~CFoo();
    bool ProcessFile(const string & csFile);

private:
   CFoo_pimpl *   m_pImpl;
};


