#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector <int > >re;

        set<int > reSet;
        sort(num.begin() ,num.end() );
        int len = num.size();

        for(int i = 0 ; i < len ; i ++){
            if(num[i] > 0) break;
            for(int j = i + 1 ; j < len ; j ++){

                int t = num[i] + num[j];
                if(t > 0 ) break;
                for(int k = j + 1 ; k < len ; k ++){
                    int sum = t + num[k];
                    //if(k+1 < len && num[k]))
                    if(sum == 0  ) {
                        vector<int> r;
                        r.push_back(num[i]);
                        r.push_back(num[j]);
                        r.push_back(num[k]);

                        int hashkey = hash(num[i],num[j],num[k]);
                        if(reSet.find(hashkey) == reSet.end()){
                            re.push_back(r);
                            reSet.insert( hashkey );
                        }


                    }
                    else if(sum > 0 ) break;
                }
            }
        }

        return re;

    }

    int hash(int a ,int b,int c){
        return a*100 + b * 10 +c ;
    }
};


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
