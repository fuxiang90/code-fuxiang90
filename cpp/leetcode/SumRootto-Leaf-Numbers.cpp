#include <iostream>
#include <vector>
using namespace std;
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//class Solution {
//public:
//
//    void CountSum(TreeNode * root ,sum){
//        if(root ->left == NULL && root->right == NULL){
//            all_sum += sum;
//        }
//        if(root -> left){
//            CountSum(root -> left , sum*10 + root->left->value);
//        }
//
//        if(root -> right){
//            CountSum(root -> right , sum*10 + root->right->value);
//        }
//    }
//    int all_sum ;
//    int sumNumbers(TreeNode *root) {
//        // Start typing your C/C++ solution below
//        // DO NOT write int main() function
//        all_sum = 0;
//        if(root == NULL) return 0;
//        CountSum(root ,root->value);
//
//        return all_sum;
//
//
//    }
//};


class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = num.size();
        int max_num = 0;
        int min_num = 0x3fffffff;
        for(int i = 0 ; i < len ; i ++ ){
            if(max_num < num[i]) max_num = num[i];
            if(min_num > num[i]) min_num = num[i];
        }

        int new_len = max_num -min_num + 1;
        int *data = new int[new_len+1];
        for(int i = 0 ; i < len ; i ++ ){
            int new_num = num[i] - min_num ;
            data[new_num ]++;
        }
        int max_len = 0;
        int tlen = 0;
        for(int i = 0 ; i <= new_len ;i ++){
                if(data[i] ){
                    tlen ++ ;
                }else {
                    if(tlen > max_len) max_len = tlen;
                    tlen = 0;
                }
        }
        delete []data;
        return max_len;

    }
};
int main()
{
	return 0;
}
