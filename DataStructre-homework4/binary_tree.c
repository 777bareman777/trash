#include <stdio.h>
#include <stdlib.h>
#include <binary_tree.h>

// node 생성 함수
pNode BT_createNode(void)
{
	pNode node=(pNode)malloc(sizeof(Node));
	if(!node)
	{
		fprintf(stderr,"메모리가 부족합니다\n");
		return NULL;
	}
	node->left=NULL;
	node->right=NULL;

	return node;
}

// node 삽입 함수
pTree BT_insert(pTree root, int value)
{
	// 최초 root 노드 생성
	if(root==NULL)
	{
		root=BT_createNode();
		if(root)
			root->value=value;
		return root;
	}
	// root 노드부터 탐색하면서 값 삽입
	else
	{
		if(root->value > value)
			root->left=BT_insert(root->left,value);
		else
			root->right=BT_insert(root->right,value);
	}

	return root;

}

pNode BT_findMinNode(pNode root)
{
	pNode tmpNode=root;
	while(tmpNode->left != NULL)
		tmpNode=tmpNode->left;
	return tmpNode;
}

// node 삭제 함수
pTree BT_delete(pTree root, int value)
{
	pNode tmpNode=NULL;

	if(root==NULL)
		return NULL;
	
	if(root->value > value)
		root->left=BT_delete(root->left,value);
	else if(root->value < value)
		root->right=BT_delete(root->right,value);
	else
	{
		// child node가 둘 다 있는 경우
		if(root->right != NULL && root->left !=	NULL)
		{
			tmpNode=BT_findMinNode(root->right);
			root->value=tmpNode->value;
			root->right=BT_delete(root->right,tmpNode->value);
		}
		else
		{
			tmpNode=(root->left == NULL) ? root->right : root->left;
			free(root);
			return tmpNode;
		}
	}

	return root;
}

// node 검색 함수
pTree BT_search(pTree root, int value)
{
	if(root == NULL)
		return NULL;

	if(root->value == value)
		return root;
	else if(root->value >value)
		return BT_search(root->left,value);
	else
		return BT_search(root->right,value);
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
