#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdbool.h>

#if defined(__APPLE__)
#include <malloc/malloc.h>
#elif defined(__MINGW32__)
#include <malloc.h>
#elif defined(__linux__)
#include <malloc.h>
#endif

typedef struct _Queue *pQueue;
typedef struct _Queue
{
	pHuffmanTree *element;
	int front,rear;
} Queue;

// 큐 생성 함수
pQueue QUEUE_create(int size);

// 큐 메모리 해제 함수
void QUEUE_free(pQueue queue);

// 큐 크기 가져오는 함수
int QUEUE_getSize(pQueue queue);

// 큐가 가득 차있는지 확인하는 함수
bool QUEUE_isFull(pQueue queue);

// 큐가 비어있는지 확인하는 함수
bool QUEUE_isEmpty(pQueue queue);

// 큐에 값을 넣는 함수
void QUEUE_enqueue(pQueue queue,pHuffmanTree element);

// 큐에 값을 꺼내는 함수
pHuffmanTree QUEUE_dequeue(pQueue queue);

#endif
