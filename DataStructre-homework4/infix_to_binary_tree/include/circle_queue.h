#ifndef _CIRCLE_QUEUE_H_
#define _CIRCLE_QUEUE_H_

#include <binary_tree.h>
#include <stdbool.h>

typedef struct _Queue *pQueue;
typedef struct _Queue
{
	pTree *value;
	int front,rear;
	int size;
} Queue;

// 큐 생성 함수
pQueue QUEUEcreate(int size);

// 큐 메모리 해제 함수
void QUEUEfree(pQueue queue);

// 큐가 가득 차있는지 확인하는 함수
bool QUEUEisFull(pQueue queue);

// 큐가 비어있는지 확인하는 함수
bool QUEUEisEmpty(pQueue queue);

// 큐에 값을 넣는 함수
void QUEUEenQueue(pQueue queue,pTree value);

// 큐에 값을 꺼내는 함수
pTree QUEUEdeQueue(pQueue queue);

#endif
