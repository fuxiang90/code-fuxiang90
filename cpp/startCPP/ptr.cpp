/*
  Name:
  Copyright:
  Author:
  Date:  22-12-2012
  Description:
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct ListNode{
    int N_value;
    ListNode* N_next;
};

void AddNode(ListNode** pHead, int value);

void addnode(ListNode * head ,int value)
{
    printf("%x %x \n" , head, &head  );
    ListNode * node = new ListNode();
    node->N_next = NULL;
    node->N_value = value;

   if(head == NULL){
    head = node;
    //head->N_next = node;
   }
   else{
    node->N_next= head->N_next;
    head->N_next = node;
   }
   printf("%x %x \n" , head, &head  );

}
main()
{
    int a = 4;

    // int * b = malloc(sizeof int );



    ListNode* pNode = NULL;

    printf("%x %x\n", pNode,&pNode);
    addnode(pNode,10);
    printf("%x %x\n", pNode,&pNode);
    ListNode* tempNode = pNode;
    while(tempNode != NULL)
    {
        printf("%d\n",tempNode->N_value);
        tempNode = tempNode->N_next;
    }

    return 0;
}

void AddNode(ListNode** pHead, int value)
{
    printf("%x %x  %x\n" , *pHead, pHead  ,& pHead);
    ListNode* newNode = new ListNode();
    newNode->N_value = value;
    newNode->N_next = NULL;

    //ListNode* tempNode = *pHead;

    if(*pHead == NULL)
        *pHead = newNode;
    else
    {
        ListNode* tempNode = *pHead;
        while(tempNode->N_next != NULL)
            tempNode = tempNode->N_next;
        tempNode->N_next = newNode;
    }

}
