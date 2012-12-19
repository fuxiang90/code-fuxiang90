#ifndef RB_TREE_INCLUDE
#define RB_TREE_INCLUDE

# include<cstdio>
# include<cstdlib>
# include<time.h>
# include<stack>
# include<iostream>
using namespace std;


typedef struct RbTreeNodePtr;

struct RbTreeNode{
    int value;
    int height;
    struct RbTreeNodePtr *LChild;
    struct RbTreeNodePtr *LChild;
    struct RbTreeNodePtr *Parent;
};
#endif
