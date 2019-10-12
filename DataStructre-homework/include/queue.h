#include <linkedlist.h>

#ifndef _QUEUE_H_
#define _QUEUE_H_

// 데이터 구조체 정의
typedef int Element; /* 노드의 데이터 타입 */
typedef char boolean; /* 논리 데이터 타입*/
typedef struct _Queue *pQueue; /* struct _Queue 포인터 */
typedef pQueue *ppQueue; /* struct _Queue 이중 포인터 */

typedef struct _Queue{ /* 큐 구조체 */
    pNode front;
    pNode rear;
    int size;
} Queue;

// 프로토 타입 함수 정의
void createQueue(ppQueue queue); // 큐 초기화 함수
void freeQueue(pQueue queue); // 큐 메모리 해제 함수
void destroyQueue(pQueue queue); // 큐 메모리 제거 함수
boolean isQueueEmpty(pQueue queue); // 큐가 비어있는지 확인
void enQueue(pQueue queue, Element element); // 큐 값 삽입 함수
Element deQueue(pQueue queue); // 큐 값 꺼내오는 함수

#endif
