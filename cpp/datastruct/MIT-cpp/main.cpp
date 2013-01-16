#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Expression.h"
using namespace std;



int main()
{
    const fExpression* ftest = new fExpression("1+2");
    ftest->print();
    return 0;
}
