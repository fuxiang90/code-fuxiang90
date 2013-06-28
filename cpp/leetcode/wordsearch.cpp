#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
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
// #include<queue>
//class Solution {
//public:
//
//    vector <vector<int> > data;
//
//    vector<vector<int> > levelOrder(TreeNode *root) {
//        // Start typing your C/C++ solution below
//        // DO NOT write int main() function
//        if(root  == NULL) return data;
//        queue<TreeNode * > q;
//        q.push(root);
//        while(!q.empty() ){
//
//
//        }
//
//    }
//
//    void work(int deep );
//};

class Solution {
public:
    double pow(double x, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(n == 1) return x;
        if(n == -1) return 1.0/x;
        if(n == 0) return 1;

        double res = x*1.0;
        int p = n;


        while(p){
            res *= res;
            p /=2;

        }
    }
};


long fab(long n)
{
    n

}

int main()
{
    Solution test;
    cout << test.sqrt(3);
	return 0;
}
