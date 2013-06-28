#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    //ListNode(int x) : val(x), next(NULL) {}
};


class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if(m == n) return head;
        ListNode * pre = NULL;
        ListNode * node = head;
        int i;
        for( i = 1 ; i < m && node; i ++) {
            pre = node;
            node = node->next;
        }

        if(node == NULL ) return head;

        if(NULL == pre) head = Reverse(head ,n-m +1);
        else {
            pre ->next = Reverse(node , n-m + 1);
        }

        return head;


    }

    ListNode *Reverse(ListNode *head, int n) {

        ListNode * node = head;

        if(head == NULL  || head -> next == NULL) return head;

        //ListNode * pre ;
        ListNode * t;
        ListNode * next =  node ->next;
        for(int i = 1 ; i < n && node  && next ; i ++) {
            t = next ;
            next = next ->next;
            t -> next = node ;
            node = t;
        }

        if(node && next ) {
            head ->next = next;
        }
        return node ;

    }
};
int main()
{
    struct ListNode data[4] ;
    data[0].val = 0;
    data[0].next = &(data[1]);

    data[1].val = 1;
    data[1].next = &data[2];

    data[2].val = 2;
    data[2].next = &data[3];

    data[3].val = 3;
    data[3].next = NULL;

    struct ListNode * head = &data[0] ;


    Solution test ;
    head = test.reverseBetween(&data[0] ,2,3);

    //head = test.Reverse(head ,2);
    return 0;
}
