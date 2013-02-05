// http://www.careercup.com/question?id=15203723
// 为题目写，没有编译 ，只是记录思路
/*
13 Answers
Given a Binary Tree (not BST) with integer values . 1) Find path from root to any node with max sum. 2) As there can be many path's find all of them. 3) Print all such paths.

Do this in O(n) : n is number of node's in tree. he wanted an O(n) solution not O(n)+O(n) ie. u can't traverse tree twice .
*/

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct node{
    int x;
    struct node * l;
    struct node * r;
    //struct node * p;
};

int max_sum = 0;
vector<  vector<int> > max_sum_path;
void getMaxSum(struct node *head , int curr_sum ,vector<int> &path)
{

    curr_sum += head->x;

    if(curr_sum > max_sum){
        max_sum = curr_sum;
        max_sum_path.erase(max_sum_path.begin() , max_sum_path.end());
    }

    if(head->l ){
        path.push_back(1);// 1 :left 2 :rigth
        getMaxSum(head->l , curr_sum , path);
        path.pop_back();

    }
    if(head->r ){
        path.push_back(2);// 1 :left 2 :rigth
        getMaxSum(head->r , curr_sum , path);
        path.pop_back();
    }

    if(curr_sum == max_sum){
        max_sum_path.push_back(path);
    }
}
