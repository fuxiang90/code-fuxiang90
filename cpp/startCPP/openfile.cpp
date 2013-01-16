#include <iostream>
#include <boost/regex.hpp>
int main()
{

    boost::wregex a(L"1325");
    if(boost::regex_match(L"1325",a)) {
        std::cout<<"yes"<<std::endl;
    } else {
        std::cout<<"no"<<std::endl;
    }
    getchar();
    return 0;
}
