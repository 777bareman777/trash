/*
 * 허프만 트리는 주어진 문자열을 트리를 이용해 2진수로 압축하는 알고리즘이다.
 * 발생 빈도수에 따라 문자열을 표현하며, 가변길이 코딩이 가능하다.
 * 발생 빈도수가 높은 문자는 짧은 코드로 표현하고,
 * 발생 빈도수가 낮은 문자는 긴 코드로 표현한다.
 *
 * 문자열의 이진 표현에는 ASCII, KSC 한글, UNICODE가 있다.
 * ASCII 는 7bit로 표현하며, KSC 한글 과 UNICODE는 2바이트로 표현을 한다.
 *
 * 허프만 트리를 구성하는 방법은 다음과 같다.
 * -> 각 문자를 빈도수에 따라 정렬한다.
 * -> 모든 문자가 이진트리로 연결된다.
 * -> 두 낮은 빈도수를 갖은 두 문자 노드를 찾는다.
 * -> 이진트리로 합병을 시킨다.
 *
 *****************************************************************************
 *
 * -> 문자열을 검색해 각 문자의 빈도수를 조사해 우선순위 큐에 집어 넣는다.
 * -> 큐에서 2개의 노드를 추출해서 binary tree로 만들고,
 *    루트는 두 노드의 빈도수의 합으로 한다
 * -> 생성된 바이너리 트리의 루트노드 x를 다시 우선순위 큐에 삽입한다. 이 때,
 *    x의 빈도수는 x의 subtree 노드의 빈도수 합이다.
 * -> 모든 원소가 binary tree 안에 들어갈 떄 까지 위의 과정을 반복한다.
 * -> tree가 완성되면 root를 기준으로 왼쪽은 0, 오른쪽은 1의 가중치를 부여해
 *    트리의 노드에 코드를 부여한다.
 *
 */
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#define TABLESIZE 100

typedef struct _Character
{
	char alpha; // 문자
	int freq;   // 빈도수
} Character;

typedef struct _HuffmanTree *pHuffmanTree;
typedef struct _HuffmanTree
{
	Character weight;
	pHuffmanTree left;
	pHuffmanTree right;
} HuffmanTree;

// tree 해제 함수
void HT_freeTree(pHuffmanTree root);

// node 해제 함수
void HT_freeNode(pHuffmanTree root);

// node 생성 함수
pHuffmanTree HT_createNode(char alpha, int freq);

// huffman tree 생성 함수
pHuffmanTree HT_createHuffmanTree(void);

// 알파벳 별 가변길이 코드 배열 생성
void HT_createTable(pHuffmanTree root, char str[], int len, char *table[]);

// 인코드 함수
void HT_encode(pHuffmanTree root, char *str);

// 디코드 함수
void HT_decode(pHuffmanTree root, char *str);

//////////////////////////////////////////

// 문자열 읽는 함수
char *fileInput(const char* filename);

// 문자열 빈도수 체크 함수, 테이블 크기 반환
int checkFreq(Character *table,char *str); 

// level 방식 출력
void Print(pHuffmanTree root);

#endif
