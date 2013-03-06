/* This is one of the solution set to CareerCup 150 problems.
 * 
 * Problem 2.2
 *
 * Method: Use two pointers to iterate through the list,
 * the first one has k distance to the second one, when the
 * second one gets to the end, return the first pointer.
 *
 * Author: Hu Kun (Kimurate)
 * Date: 02/26/2013
 * Compile command: gcc-4.7 2.2.c -std=c99
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct _node
{
	struct _node * next;
	char content;
} node;
 
node *createLinkedListFromHead(char *list);
void printLinkedList(const node *listHead);
node *findKthToLast(const node * head, int k);
 
int main()
{
	char *list = "abcdefg";
	const node *head = createLinkedListFromHead(list);
 
	printLinkedList(head);
	int k = 4;
	node *kthNode = findKthToLast(head, k);
	if(kthNode)
		printf("The %dth to last element is %c\n", k, kthNode->content);
	else
		printf("Error, maybe the k is too big.\n");
 
	return 0;
}
 
node *findKthToLast(const node * head, int k)
{
	node *p = head->next;
	node *q = p;
	int kCount=k;
	while(kCount-- && p) p = p->next;
	if(!p)
	{
		printf("Error: Choose a smaller k.\n");
		return NULL;
	}
	while(p)
	{
		p = p->next;
		q = q->next;
	}
 
	return q;
}
 
void printLinkedList(const node *listHead)
{
	node *p = listHead->next;
	while(p)
	{
		printf("%c", p->content);
		p = p->next;
	}
	printf("\n");
}
 
node *createLinkedListFromHead(char *list)
{
	node *head = (node*)malloc(sizeof(node));
	if(head == NULL)
	{
		printf("Allocate head failed.\n");
		return NULL;
	}
	head->next = NULL;
	node *rear = head;
 
	//Create the linked list
	for(int i=0, len=strlen(list); i<len; i++)
	{
		node *p = (node*)malloc(sizeof(node));
		if(p == NULL)
		{
			printf("Allocate head failed.\n");
			return NULL;
		}
		p->content = list[i];
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
 
	return head;
}
