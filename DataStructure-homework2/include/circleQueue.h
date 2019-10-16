#ifndef _CIRCLEQUEUE_H_
#define _CIRCLEQUEUE_H_

/*
Problem 2: 20개의 정수 값를 처리할 수 있는 원형 큐(circular queue)를 설계하 고 구현하시오.
*/


#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef int Element;
typedef char boolean;
typedef Element *pElement;
typedef struct _Queue *pQueue;
typedef pQueue *ppQueue;

typedef struct _Queue{
    pElement element;
    int front, rear;
    int size;
} Queue;

// 큐 생성 함수
void createQueue(ppQueue queue,int size);
// 큐 메모리 해제 함수
void freeQueue(pQueue queue);
// 큐가 꽉 차있는지 확인하는 함수
boolean isQueueFull(pQueue queue);
// 큐가 비어있는지 확인하는 함수
boolean isQueueEmpty(pQueue queue);
// 큐에 값을 넣는 함수
boolean enQueue(pQueue queue, Element element);
// 큐에 값을 꺼내는 함수
boolean deQueue(pQueue queue, pElement result);



#endif
