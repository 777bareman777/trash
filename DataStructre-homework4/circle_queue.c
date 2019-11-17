#include <stdlib.h>
#include <circle_queue.h>


// 큐 생성 함수
pQueue QUEUEcreate(int size)
{
	pQueue queue=NULL;
	queue=(pQueue)malloc(sizeof(Queue));
	if(!queue)
		return NULL;

	// 0 인덱스는 사용하지 않음.
	// 마지막 연산을 비교해서, 꽉차있는지 비어있는지 확인하고자 함.
	queue->value=(pTree*)calloc(size,sizeof(pTree));
	queue->value[0]=(pTree)-1;
	queue->front=size-1;
	queue->rear=size-1;
	queue->size=size;

	return queue;	
}

// 큐 메모리 해제 함수
void QUEUEfree(pQueue queue)
{
	free(queue->value);
	free(queue);
}

// 큐가 가득 차있는지 확인하는 함수
bool QUEUEisFull(pQueue queue)
{
	if((queue->front==queue->rear) && (queue->value[0]== (pTree)false))
	{
		return true;
	}
	else
		return false;
}

// 큐가 비어있는지 확인하는 함수
bool QUEUEisEmpty(pQueue queue)
{
	if((queue->front==queue->rear) && (queue->value[0]==(pTree)true))
	{
		return true;
	}
	else
		return false;
}

// 큐에 값을 넣는 함수
void QUEUEenQueue(pQueue queue,pTree value)
{
	if(QUEUEisFull(queue) || value == NULL)
		;
	else
	{
		queue->rear = (queue->rear) % (queue->size - 1) + 1;
        queue->value[queue->rear] = value;
        queue->value[0] = (pTree)false;
	}
}

// 큐에 값을 꺼내는 함수
pTree QUEUEdeQueue(pQueue queue)
{
	if(QUEUEisEmpty(queue))
		;
	else
	{
		queue->front=(queue->front)%(queue->size-1)+1;
		pTree tmp=queue->value[queue->front];
		queue->value[0]=(pTree)true;
		return tmp;
	}
	return NULL;
}
