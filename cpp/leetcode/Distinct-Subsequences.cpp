#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
class Solution {
public:

    string src;
    string dest;
    int num;
    int src_len;
    int dest_len;
    //int  data;
    int numDistinct(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        num = 0;
        src = S;
        dest = T;
        src_len = src.size();
        dest_len = dest.size();
        if(src_len == 0 ||dest_len == 0 )
            return 0;
        //dfs(0,0);

        num = work();

        return num;
    }

    void dfs(int src_pos ,int dest_pos){
        if(dest_pos == dest_len){
            num ++;
        }
        if(src_pos ==  src_len ){

            return ;
        }

//        if(dest_pos == dest_len -1 && src[src_pos ] == dest[dest_pos]){
//            num ++;
//            return ;
//        }

        for(int  i = src_pos ; i < src_len ; i ++){
            if(src[i] ==  dest[dest_pos]){

                dfs(i+1,dest_pos + 1);
            }

        }
    }

    int work()
    {
        int dp[2][10000];
//        for(int i = 0 ; i < src_len ;i++){
//            if(src[i] == dest[0] ){
//                if(i == 0 ){
//                    dp[0][i] = 1;
//                }else {
//                    dp[0][i] = dp[0][i-1] + 1;
//                }
//            }else {
//                if(i == 0 ){
//                    dp[0][i] = 0;
//                }else {
//                    dp[0][i] = dp[0][i-1];
//                }
//            }
//
//        }//end for
//
//        for(int i = 1 ; i < dest_len ; i ++){
//            for(int j = 0 ; j < src_len ; j ++){
//                if(j < i ) dp[i%2][j] = 0;
//                else if (j ==i){
//                    if(src[j] == dest[i] && dp[(i+1)%2][j-1] == i -1 ) dp[i%2][j] = dp[(i+1)%2][j-1] ;
//                    else  dp[i%2][j] = 0;
//                }
//                else {
//                    if(src[j] == dest[i]) dp[i%2][j] =max ( dp[(i)%2][j-1] + 1  ,dp[(i+1)%2][j-1] );
//                    else dp[i%2][j] = dp[(i)%2][j-1] ;
//                }
//            }
//
//        }

        dp[0][0] = 1;
        for(int i = 0 ; i < src_len ;i++){
            dp[0][i+1] = 0;

        }//end for
        for(int i = 1  ; i <= dest_len ; i ++) {
            for(int j = 1 ; j <= src_len ; j ++){
                if(src[j-1] == dest[j-1]){
                    dp[i%2][j] = dp[(i+1)%2][j] + dp[i%2][j-1];
                }else{
                    dp[i%2][j] = dp[(i+1)%2][j];
                }
            }

        }
        return dp[(dest_len)%2][src_len ];
    }


};


int main()
{
    Solution test;
    cout << test.numDistinct("aacaacca", "ca");
	return 0;
}
