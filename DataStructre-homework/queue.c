#include <stdlib.h>
#include <queue.h>

// 큐 초기화 함수
void createQueue(ppQueue queue)
{
    *queue=(pQueue)malloc(sizeof(queue));
    (*queue)->front=(*queue)->rear=NULL;
    (*queue)->size=0;
}

// 큐 값 삽입
void enQueue(pQueue queue, Element element)
{
    // 큐가 NULL 이면, 값을 삽입하지 않음.
    if(!queue)
        return ;
    
    // 노드 생성
    pNode n; 
    createNode(&n,element);

    // 큐에 값 삽입
    if(queue->size==0)
    {
        queue->front=queue->rear=n; // 하나도 없을 경우, 
                                    // front와 rear를 동일하게 둠.
    }
    else
    {
        queue->rear->link=n; // 현재 맨 뒤의 node가 추가된 node를 가리키게 설정
        queue->rear=n; // 맨 뒤를 추가된 node로 변경
    }
    queue->size+=1; // 큐 크기 증가
}

// 스택 값 꺼내기
Element deQueue(pQueue queue)
{
    pNode n;
    Element element;

    // 큐가 비어있는지 확인
    // 비어있다면, 0의 값을 꺼냄
    if(isQueueEmpty(queue))
    {
        return 0;
    }

    n=queue->front; // n을 큐의 맨 앞부분으로 설정
    element=n->element; // n의 element를 꺼냄
    queue->front=n->link; // n 다음의 node를 큐의 맨 앞부분으로 설정
    queue->size-=1; // 큐의 크기 감소
    freeNode(n); // 사용한 node 메모리 해제
    return element;
}

// 큐가 비어있는지 확인
boolean isQueueEmpty(pQueue queue)
{
    // Queue가 비어있을 경우 1 반환, 아닐 경우 0 반환
    return (queue->front==NULL && queue->front==NULL);
}

// 큐 메모리 해제
void freeQueue(pQueue queue)
{
    if(!queue) return; // 메모리가 제거된 상태

    while(queue->size != 0)
    {
        pNode n=queue->front; // n을 큐의 맨 앞부분으로 설정
        queue->front=n->link; // n의 element를 꺼냄
        queue->size-=1; // 큐의 크기 감소
        freeNode(n); // 사용한 node 메모리 해제
    }
    queue->front=queue->rear=NULL; // 큐의 맨 앞부분과 뒤를 NULL로 설정
}

// 큐 메모리 제거
void destroyQueue(pQueue queue)
{
    freeQueue(queue);
    if(!queue) return ; // 메모리가 제거된 상태
    free(queue);
    queue=NULL;
}
