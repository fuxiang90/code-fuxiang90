#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
};
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if(root == NULL ) return ;

        if(root -> left){
            root->left = root->right;
        }

        if(root -> )

    }
};



int main()
{
	return 0;
}
