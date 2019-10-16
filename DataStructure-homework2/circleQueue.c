#include <stdio.h>
#include <stdlib.h>
#include <circleQueue.h>

// 큐 생성 함수
void createQueue(ppQueue queue, int size)
{
    if ((*queue))
        return;

    printf("size: %d\n", size);
    *queue = (pQueue)malloc(sizeof(Queue));
    (*queue)->element = (pElement)calloc(size, sizeof(Element));
    (*queue)->element[0] = -1;
    (*queue)->front = size - 1;
    (*queue)->rear = size - 1;
    (*queue)->size = size;
}

// 큐 메모리 해제 함수
void freeQueue(pQueue queue)
{
    free(queue->element);
    free(queue);
}

// 큐가 꽉 차있는지 확인하는 함수
boolean isQueueFull(pQueue queue)
{
    if ((queue->front == queue->rear) && (queue->element[0] == FALSE))
    {
        return TRUE;
    }
    else
        return FALSE;
}

// 큐가 비어있는지 확인하는 함수
boolean isQueueEmpty(pQueue queue)
{
    if ((queue->rear == queue->front) && (queue->element[0] == TRUE))
    {
        return TRUE;
    }
    else
        return FALSE;
}

// 큐에 값을 넣는 함수
boolean enQueue(pQueue queue, Element element)
{

    if (isQueueFull(queue))
    {
        printf("큐가 가득 참\n");
        return FALSE;
    }
    else
    {
        queue->rear = (queue->rear) % (queue->size - 1) + 1;
        queue->element[queue->rear] = element;
        queue->element[0] = FALSE;
        return TRUE;
    }
}

// 큐에 값을 꺼내는 함수
boolean deQueue(pQueue queue, pElement result)
{
    if (isQueueEmpty(queue))
    {
        printf("큐가 비어 있음\n");
        return FALSE;
    }
    else
    {
        queue->front = (queue->front) % (queue->size - 1) + 1;
        *result = queue->element[queue->front];
        queue->element[0] = TRUE;
        return TRUE;
    }
}
