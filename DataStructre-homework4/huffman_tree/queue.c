#include <huffman_tree.h>
#include <queue.h>

// 큐 생성 함수
pQueue QUEUE_create(int size)
{
	pQueue queue=NULL;
	queue=(pQueue)malloc(sizeof(Queue));
	if(!queue)
		return NULL;

	// 0 인덱스는 사용하지 않음.
	// 마지막 연산을 비교해서, 꽉차있는지 비어있는지 확인하고자 함.
	queue->element=(pHuffmanTree*)calloc(size,sizeof(pHuffmanTree));
	queue->element[0]=(pHuffmanTree)-1;
	queue->front=size-1;
	queue->rear=size-1;

	return queue;	
}

// 큐 메모리 해제 함수
void QUEUE_free(pQueue queue)
{
	free(queue->element);
	free(queue);
}

// 큐 크기를 가져오는 함수 
int QUEUE_getSize(pQueue queue)
{
#if defined(__APPLE__)
	return malloc_size(queue->element)/sizeof(queue->element[0]);
#elif defined(__MINGW32__)
	return _msize(queue->element)/sizeof(queue->element[0]);
#elif defined(__linux__)
	return malloc_usable_size(queue->element)/sizeof(queue->element[0]);
#endif
}

// 큐가 가득 차있는지 확인하는 함수
bool QUEUE_isFull(pQueue queue)
{
	if((queue->front==queue->rear) && (queue->element[0]==(pHuffmanTree)false))
	{
		return true;
	}
	else
		return false;
}

// 큐가 비어있는지 확인하는 함수
bool QUEUE_isEmpty(pQueue queue)
{
	if((queue->front==queue->rear) && (queue->element[0]==(pHuffmanTree)true))
	{
		return true;
	}
	else
		return false;
}

// 큐에 값을 넣는 함수
void QUEUE_enqueue(pQueue queue,pHuffmanTree element)
{
	if(QUEUE_isFull(queue) || element == NULL)
		;
	else
	{
		queue->rear = (queue->rear) % (QUEUE_getSize(queue) - 1) + 1;
		queue->element[queue->rear] = element;
		queue->element[0]=(pHuffmanTree)false;
	}
}

// 큐에 값을 꺼내는 함수
// 반환 값이 -1 이면, 에러로 확인
// 음수 처리 못함
pHuffmanTree QUEUE_dequeue(pQueue queue)
{
	if(QUEUE_isEmpty(queue))
		;
	else
	{
		queue->front=(queue->front)%(QUEUE_getSize(queue) - 1)+1;
		pHuffmanTree tmp=queue->element[queue->front];
		queue->element[0]=(pHuffmanTree)true;
		return tmp;
	}
	return NULL;
}
