#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <priority_queue.h>
#include <queue.h>
#include <huffman_tree.h>

// tree 해제 함수
void HT_freeTree(pHuffmanTree root)
{
	if(root->right != NULL)
		HT_freeTree(root->right);
	if(root->left != NULL)
		HT_freeTree(root->left);

	root->left=NULL;
	root->right=NULL;
	HT_freeNode(root);
}

// node 해제 함수
void HT_freeNode(pHuffmanTree root)
{
	free(root);
	root=NULL;
}

// node 생성 함수
pHuffmanTree HT_createNode(char alpha, int freq)
{
	pHuffmanTree node=(pHuffmanTree)malloc(sizeof(HuffmanTree));
	if(!node)
	{
		fprintf(stderr,"메모리가 부족합니다\n");
		return NULL;
	}
	node->weight.alpha=alpha;
	node->weight.freq=freq;
	node->left=NULL;
	node->right=NULL;

	return node;
}

// 문자열 읽는 함수
char *fileInput(const char* filename)
{
	FILE *fp=fopen(filename,"rb");
	char buf[1024]={0,};	
	fgets(buf,sizeof(buf)-1,fp);
	char *str=(char*)calloc(strlen(buf),sizeof(char));
	strncpy(str,buf,strlen(buf));
	return str;
}

// 문자열 빈도수 체크 함수, 테이블 크기 반환
int checkFreq(Character *table, char *str)
{
	int i=0, index=0;
	for(i=0; i<strlen(str)-1; i++)
	{
		for(int j=0;j<=index && index<TABLESIZE;j++)
		{
			if(table[j].alpha==0)
			{
				table[j].alpha=str[i];
				table[j].freq=1;
				index++;
				break;
			}
			else if(table[j].alpha==str[i])
			{
				table[j].freq+=1;
				break;
			}
		}
	}
	return index;
}


// huffman tree 생성 함수
pHuffmanTree HT_createHuffmanTree(void)
{
	pHuffmanTree root=NULL;
	pHeap heap=NULL;
	Character table[TABLESIZE];
	heap=HEAP_create(TABLESIZE);
	char *str=fileInput("string.txt");

	// 문자열 빈도수 체크
	int index=checkFreq(table, str);


	/*
	// 문자열 빈도수 출력
	printf("index: %d\n",index);
	for(int j=0;j<index;j++)
		printf("%c %d\n", table[j].alpha,table[j].freq);
	*/

	// 우선순위 큐에 삽입
	// 빈도수 낮을 수록 우선순위가 높음
	for(int j=0;j<index;j++)
	{
		pHuffmanTree node=HT_createNode(table[j].alpha,table[j].freq);
		Element tmp;
		tmp.tree=node;
		HEAP_minPush(heap,tmp);
	}

	/*
	// 우선순위 큐 출력
	printf("---------------------\n");
	for(int j=0;j<index;j++)
	{
		Element tmp=HEAP_minPop(heap);
		printf("%c %d\n",tmp.tree->weight.alpha, tmp.tree->weight.freq);
	}
	*/

	// 우선순위 큐에서 2개의 node를 꺼내서 binary tree로 만들고,
	// 루트는 두 노드의 빈도수 합으로 만든다.
	// 그 후에 생성된 바이너리 트리의 루트노드 x를
	// 다시 우선순위 큐에 삽입한다.
	// 큐가 비어있을 때까지 진행, 큐가 비어있다면 바이너리 트리가 완성됨을 의미.
	while( heap->cur != 0 )
	{
		Element left=HEAP_minPop(heap);
		Element right=HEAP_minPop(heap);

		pHuffmanTree head=HT_createNode('*',left.tree->weight.freq+right.tree->weight.freq);
		head->left=left.tree;
		head->right=right.tree;
		Element tmp;
		tmp.tree=head;
		if(heap->cur != 0)	
			HEAP_minPush(heap,tmp);
		
		root=head;
	}

	free(str);
	HEAP_free(heap);
	printf("root addr: %p\n",root);
	return root;
}

// level 방식 출력
void Print(pHuffmanTree root)
{
	if(root==NULL)
		return;

	pHuffmanTree cur=root;
	pQueue queue=QUEUE_create(128);
	while(cur!=NULL)
	{
		printf("%c %d\n",cur->weight.alpha, cur->weight.freq);
		QUEUE_enqueue(queue,cur->left);
		QUEUE_enqueue(queue,cur->right);
		cur=QUEUE_dequeue(queue);
	}
}

// 알파벳 별 가변길이 코드 배열 생성
void HT_createTable(pHuffmanTree root, char str[],int len, char *table[])
{
	if(root->left == NULL && root->right == NULL)
	{
		str[len]='\0';
		int i=0;
		for(i=0;i<root->weight.alpha-'a';i++)
			;
		strncpy(table[i],str,len);
		printf("%s",str);
	}
	else
	{
		if(root->left != NULL)
		{
			str[len] = '0';
			HT_createTable(root->left,str,len+1,table);
		}
		if(root->right != NULL)
		{
			str[len]='1';
			HT_createTable(root->right,str,len+1,table);
		}
	}
}

// 인코드 함수(트리 루트 노드, 인코딩하고 싶은 문자열)
void HT_encode(pHuffmanTree root, char *str)
{

}


// 디코드 함수(트리 루트 노트, 디코딩하고 싶은 문자열)
void HT_decode(pHuffmanTree root, char *str)
{
	int i=0;
	pHuffmanTree tmp=root;
	while(str[i]!='\0')
	{
		if(str[i]=='0')
			tmp=tmp->left;
		else if(str[i]=='1')
			tmp=tmp->right;
		if(root->left==NULL && root->right ==NULL)
		{
			printf("%c",tmp->weight.alpha);
			tmp=root;
		}
		i++;
	}
	printf("\n");
}
