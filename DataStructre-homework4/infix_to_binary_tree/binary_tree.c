#include <stdio.h>
#include <stdlib.h>
#include <binary_tree.h>
#include <circle_queue.h>

// tree 해제 함수
void BT_freeTree(pTree root)
{
	if(root->right != NULL)
		BT_freeTree(root->right);
	if(root->left != NULL)
		BT_freeTree(root->left);

	root->left=NULL;
	root->right=NULL;
	BT_freeNode(root);
}
// node 해제 함수
void BT_freeNode(pNode root)
{
	free(root);
}

// node 생성 함수
pNode BT_createNode(int value)
{
	pNode node=(pNode)malloc(sizeof(Node));
	if(!node)
	{
		fprintf(stderr,"메모리가 부족합니다\n");
		return NULL;
	}
	node->value=value;
	node->left=NULL;
	node->right=NULL;

	return node;
}

// infix 방식으로 트리 출력 함수
void BT_infixPrint(pTree root)
{
	if(root==NULL)
		return;

	BT_infixPrint(root->left);
	printf("%c ",root->value);
	BT_infixPrint(root->right);
}

// postfix 방식으로 트리 출력 함수
void BT_postfixPrint(pTree root)
{
	if(root==NULL)
		return ;

	BT_postfixPrint(root->left);
	BT_postfixPrint(root->right);
	printf("%c ",root->value);
}

// prefix 방식으로 트리 출력 함수
void BT_prefixPrint(pTree root)
{
	if(root==NULL)
		return ;

	printf("%c ",root->value);
	BT_prefixPrint(root->left);
	BT_prefixPrint(root->right);
}

// level 방식으로 트리 출력 함수
void BT_levelPrint(pTree root)
{
	if(root==NULL)
		return ;

	pQueue queue=QUEUEcreate(100);
	while(root!=NULL)
	{
		printf("%c ",root->value);
		QUEUEenQueue(queue,root->left);
		QUEUEenQueue(queue,root->right);
		root=QUEUEdeQueue(queue);
	}

	QUEUEfree(queue);
}
