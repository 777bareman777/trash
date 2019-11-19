/*
 * 우선순위 큐란 우선 순위를 가진 항목들을 저장하는 큐.
 * 우선 순위가 높은 데이터가 먼저 빠져나가게 된다.
 * 우선순위 큐는 시뮬레이션 시스템, 네트워크 트래픽 제어, OS 작업 스케줄링에 사용된다.
 * 
 * 우선순위 큐의 구현은 기본적으로 힙을 이용한다.
 * 힙이란 complete binary tree 에 있는 노드 중에서 키 값이 가장 큰 노드나
 * 키 값이 가장 작은 노드를 찾기 위해서 만들어진 자료구조이다.
 *
 * 최대 힙(Max Heap)
 * 키 값이 가장 큰 노드를 찾기 위한 complete binary tree
 * 루트 노드 : 키 값이 가장 큰 노드
 * 부모 노드의 키 값 >= 자식 노드의 키 값
 * 
 * 최소 힙(Min Heap)
 * 키 값이 가장 작은 노드를 찾기 위한 complete binary tree
 * 루트 노드 : 키 값이 가장 작은 노드
 * 부모노드의 키 값 >= 자식 노드의 키 
 *
 *************************************************************
 *
 * (삽입)
 * complete binary tree를 유지하면서, 확장한 노드에 삽입할 원소 저장
 * 노드가 n개인 complete binary tree에서 다음 노드의 확장 자리는 n+1 번의 노드가 됨.
 * n+1번 자리에 노드를 확장하고, 그 자리에 삽입할 원소를 저장한다.
 *
 * 만들어진 complte binary tree 내에서 삽입 원소의 제자리를 찾기
 * 현재 위치에서 부모 노드와 비교하여 크기 관계를 확인한다.
 * 현재 부모 노드의 키값 >= 삽입원소의 키 값(최대 힙 기준)의 관계가 성립하지 않으면
 * 현재 부모노드의 원소와 삽입 원소의 삽입 원소의 자리를 서로 바꾼다.
 *
 * (삭제)
 * 힙에서의 삭제는 다음의 규칙을 따른다.
 * 우선 삭제는 루트 노드의 원소만 삭제할 수 있다.
 * 루트 노드의 원소를 삭제하여 반환한다.
 * 원소의 개수가 n-1개로 줄었으므로, 노드의 수가 n-1인 완전 이진 트리로 조정한다.
 *
 * 노드가 n개인 완전 이진 트리에서 노드 수 n-1개의 완전 이진트리가 되기 위해서
 * 마지막 노드, 즉 n번 노드를 삭제한다.
 * 삭제된 n번 노드에 있던 원소는 비어있는 루트 노드에 저장한다.
 *
 * 완전 이진 트리 내에서 루트에 임시 저장된 원소의 제자리를 찾아가도록한다.
 * 현재 위치에서 자식 노드와 크기 관계를 확인한다.
 * 현재 위치의 키 값 >= 현재 자식 노드의 키 값(최대힙 기준)의 관계가 성립하지 않으면,
 * 현재 자식 노드의 원소와 현재 위치에서 저장된 원소의 자리를 서로 바꾼다.
 *
 *
 */


#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_


#include <huffman_tree.h>
#define MAXSIZE 100

typedef struct _Element
{
	pHuffmanTree tree;
} Element;

typedef struct _Heap{
	Element *element;
	int cur;
} Heap, *pHeap;


// Heap 생성 함수
pHeap HEAP_create(int size);

// Heap 해제 함수
void HEAP_free(pHeap heap);

// Min Heap 에 데이터 삽입 함수
void HEAP_minPush(pHeap heap,Element element);

// Min Heap 에서 데이터 꺼내기 함수
Element HEAP_minPop(pHeap heap);

// swap 함수
void swap(Element *a, Element *b);


#endif
