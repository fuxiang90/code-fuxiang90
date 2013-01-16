



#include "pipml.h"


//here defines PIMPl class, because it is use only in this file
class CFoo_pimpl
{
public:
    CFoo_pimpl()
    {
    }

    ~CFoo_pimpl()
    {
    }
    bool ProcessFile(const string & csFile)
    {
        cout << csFile << endl;
        return true;
    }
};

CFoo::CFoo()
:m_pImpl(new CFoo_pimpl())
{
}

CFoo::~CFoo()
{
    //do not have to delete, std::auto_ptr is very nice
}

bool CFoo::ProcessFile(const string & csFile)
{
    //just call your PIMPL function ;-)
    return m_pImpl->ProcessFile(csFile);
}
