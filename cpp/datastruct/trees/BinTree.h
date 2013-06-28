#ifndef _BINTREE_H
#define _BINTREE_H

//二叉树
# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<stack>
# include<iostream>
using namespace std;
typedef struct TreeNode * TREENODEPTR;
struct TreeNode
{
	int data;
	TREENODEPTR LChild;
	TREENODEPTR RChild;
};



TREENODEPTR FindTree( TREENODEPTR root,int key)
{
	if(root == NULL)
		return NULL;
	if(key < root->data)
		return FindTree(root->LChild,key);
	else if(key > root->data)
		return FindTree(root->RChild,key);
	else
		return root;
}
TREENODEPTR TreeMalloc(TREENODEPTR *root)
{
	return *root = (TREENODEPTR)malloc(sizeof(struct TreeNode));

}
TREENODEPTR FindMinTree(TREENODEPTR root)
{
	if(root == NULL)
		return NULL;
	if(root -> LChild)
		return FindMinTree(root->LChild);
	else
		return root;
}

TREENODEPTR FindMaxTree(TREENODEPTR root)
{
	if(root == NULL)
		return NULL;
	if(root -> RChild)
		return FindMaxTree(root->RChild);
	else
		return root;
}

void InsertTree(TREENODEPTR & root,int key )//为了方便 用了 C++ 的特性
{
	if(root == NULL)
	{
		//root = (TREENODEPTR)malloc(struct TreeNode);
		if( (root = TreeMalloc(&root)) == NULL)
			printf("memory error\n");
		root ->data = key;
		root ->LChild = NULL;
		root ->RChild = NULL;
	}
	else if(key > root->data)
		InsertTree(root->RChild,key);
	else if(key < root->data)
		InsertTree(root->LChild,key);
}

void CreatTree(TREENODEPTR & root)
{
    int i;
	srand(time(NULL));
	int data[20] = {0,67,51,97,91};
    for(i = 1; i <= 4 ; i ++)
	{
		//srand(time(NULL)); 这里每次成的 随机数会一样
        //InsertTree(root,rand()%100);

        InsertTree(root,data[i]);
	}
}

// TREENODEPTR DeleteTree_t(TREENODEPTR & root , TREENODEPTR  Parent ,int key)
// {
//
// 	int mData = root -> data;
// 	if(mData == key && Parent==NULL)
// 	{
// 		printf("根节点被删除 \n");
// 		free(root);
// 		return NULL;
// 	}
// 	if(key > mData)
// 		DeleteTree(root->RChild,root,key);
// 	else if(key < mData)
// 		DeleteTree(root->LChild,root,key);
// 	else // 找到
// 	{
// 		TREENODEPTR CellTree ;
//
//
// 	}
//
//
// }

TREENODEPTR DeleteTree(TREENODEPTR  root , int key)
{

	TREENODEPTR  temp;
	int mdata = root ->data;
	if(root == NULL )
		printf("root is null \n");
	if( key > mdata )
		root->RChild = DeleteTree(root->RChild,key);
	else if(key < mdata)
		root->LChild = DeleteTree(root->LChild,key);
	else
	{
		if(root ->LChild && root->RChild)
		{

			temp = FindMinTree(root->RChild);
			root ->data = temp->data;
			//root->RChild = DeleteTree(root->RChild,key);
			root->RChild = DeleteTree(root->RChild,root->data); //2012 5-22 修正

		}
		else// if one or no child
		{
			temp = root;
			if(root ->LChild == NULL)
				root = root->RChild;
			else if(root ->RChild == NULL)
				root = root->LChild;

			free(temp);
		}
	}

	return root;


}
void PrintTree(TREENODEPTR root,int deep)
{
	int i;
	if(root != NULL)
	{



		//printf("L ");
		PrintTree(root->LChild,deep+1);

		for(i = 0 ; i < deep ; i ++)	printf("\t");
		printf("%d\n",root->data);

		//printf("R ");
		PrintTree(root->RChild,deep+1);
	}
}

/*上面是2011年4月写的*/

/*用非递归的方式*/
void PreTree(TREENODEPTR root )
{
    stack<TREENODEPTR> S;
    S.push(root);
    TREENODEPTR tmp = NULL;
    TREENODEPTR pre = NULL;
    while(!S.empty())
    {
        tmp = S.top();
        if( (tmp->LChild == NULL&& tmp->RChild == NULL) || tmp->LChild ==pre || tmp->RChild == pre)
        {
            printf("%d \n",tmp->data);
            pre = tmp;
            S.pop();

        }
        else if(tmp -> LChild )
        {
            S.push(tmp->LChild);
        }
        else if (tmp -> RChild )
        {
            S.push(tmp->RChild);
        }
    }
}


void PreTree2(TREENODEPTR root )
{
    stack<TREENODEPTR> S;
    S.push(root);
    TREENODEPTR tmp = NULL;
    while(!S.empty())
    {
        tmp = S.top();
        S.pop();
        printf("%d \n",tmp->data);

        if (tmp -> RChild )
        {
            S.push(tmp->RChild);
        }
        if(tmp -> LChild )
        {
            S.push(tmp->LChild);
        }
    }
}
/*用非递归的方式*/
void InorderTree(TREENODEPTR root )
{
    if(root == NULL) return ;
    stack<TREENODEPTR> S;
    S.push(root);
    TREENODEPTR tmp = NULL;
    TREENODEPTR pre = NULL;
    while(!S.empty())
    {
        tmp = S.top();
        if( tmp->LChild && tmp->LChild != pre )
        {
            while(tmp->LChild){
                tmp = tmp->LChild;
                S.push(tmp);
            }

        }
        else if(tmp -> RChild )
        {
            printf("%d \n",tmp->data);
            S.pop();
            S.push(tmp->LChild);
        }
        else
        {
            printf("%d \n",tmp->data);
            S.pop();
        }

        pre = tmp;
    }
}

void InorderTree2(TREENODEPTR t)
{
    stack<TREENODEPTR> s;

    TREENODEPTR p=t;

    while (p!=NULL || !s.empty())
    {
        while (p!=NULL)             //遍历左子树
        {
            s.push(p);
            p=p->LChild;
        }

        if (!s.empty())
        {
            p = s.top();
            s.pop();
            printf("%d \n",p->data);        //访问根结点
            p=p->RChild;            //通过下一次循环实现右子树遍历
        }//endif

    }//endwhile
}
void hashNode(){}
void getCommonFather(TREENODEPTR root ,int a ,int b)
{

}
void testBST()
{
	TREENODEPTR roota = NULL;
	CreatTree(roota);
	PrintTree(roota,0);
//	PreTree2(roota);
//	printf("---------inorder----------\n");
//	//InorderTree(roota);
//	InorderTree2(roota);
//	int key;
//	while(scanf("%d",&key)!=EOF)
//	{
//		DeleteTree(roota,key);
//		PrintTree(roota,0);
//
//		printf("\n\n");
//
//	}
}
#endif

