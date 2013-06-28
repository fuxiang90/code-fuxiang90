#ifndef CRACK2_H_INCLUDED
#define CRACK2_H_INCLUDED

#include<list>

struct listNode{
    int value;
    struct listNode * next;
};
void fun2p1(struct listNode * head)
{
    set <int > mset;
}

struct listNode * findKnode( struct listNode * head, int k)
{
    if(k <= 0 ) return NULL;
    struct listNode * ptr = head;
    struct listNode * last_k_node = NULL;
    for(int i = 1  ; i <= k && ptr; i ++){
        ptr = ptr -> next;
    }
    if(ptr == NULL){
        return NULL;
    }

    last_k_node = head ;
    while(ptr ){
        ptr = ptr -> next;
        last_k_node = last_k_node -> next;
    }

    return last_k_node;

}

void deleteMiddleNode( struct listNode * head)
{

}
#endif // CRACK2_H_INCLUDED
