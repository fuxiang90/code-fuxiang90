/*

参考： http://www.cs.ubc.ca/labs/beta/Courses/CPSC445-08/Handouts/kmp.pdf
http://delab.csd.auth.gr/~dimitris/courses/cpp_fall05/books/SIAM_JNL_Comp_77_KMP_string_matching.pdf
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;



/*

string patt 的有效下标 从1 开始
*/
vector<int>  next(string patt)
{

    int len = patt.size();
    vector<int > f(len + 2,0);
    f[0] = 0;
    f[1] = 0;
    int k = 0;
    for(int i = 2; i < len ; i ++) {
        while( k >  0 &&  (patt[k+1] != patt[i]) ) {
            k = f[k];
        }
        if(patt[k+1] ==  patt[i]) {
            k ++;
        }
        f[i] = k;
    }

    return f;
}

bool kmp(string text , string patt)
{
    vector<int> result = next("0ababababca");

    int len = text.size();
    int j = 0;
    for(int i = 1 ; i < len ; i ++){
        while( j > 0 &&patt[j+1] != text[i]){
            j = f[j];
        }

        if(patt[j + 1] == text[i]){
            j ++;
        }
    }
}
int main()
{
    cout << "Hello world!" << endl;


    copy(result.begin()  + 1, result.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
