#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector< vector <int> > data ;
        data.resize(rowIndex +1);
        data[0].push_back(1);
        //data[1].push_back(1);
        //data[1].push_back(1); //当输入为0 的时候 这里没有分配空间

        if(rowIndex < 1) return data[rowIndex];

        for(int i = 1 ; i <= rowIndex ; i ++){
            for(int j = 0 ; j <= i ; j ++ ){
                if(j == 0 || j == i ) data[i].push_back(1);
                else
                    data[i].push_back(data[i-1][j] + data[i-1][j-1] );
            }
        }

        return data[rowIndex];

    }
};
int main()
{
    Solution test;
    vector<int> a;
    a = test.getRow(3);

	return 0;
}
