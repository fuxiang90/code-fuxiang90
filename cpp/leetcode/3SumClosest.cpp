#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace::std;

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(),num.end());

        int sum = 0;
        int re = 0;
        int delta = 2*target;
        int len = num.size();
        for(int i = 0 ; i < len - 2 ; i ++){
            int l = i +1 ;
            int r = len -1;

            int pre = -1;
            int now = 1;
            while(l < r ){
                sum = num[i] + num[l] + num[r];

                if(sum == target) return target;
                else if(sum < target ){
                    if(abs(sum - target) < delta) delta = abs(sum - target),re = sum;
                    l ++ ;
                }
                else{
                    if(abs(sum - target) < delta) delta = abs(sum - target) ,re = sum;
                    r --;
                }


            }
        }//end for


        return re;
    }
};


int main()
{
    int i ;
    return 0;
}
