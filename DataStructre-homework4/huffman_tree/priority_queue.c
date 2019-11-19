#include <stdio.h>
#include <stdlib.h>
#include <priority_queue.h>

// Heap 생성 함수
pHeap HEAP_create(int size)
{
	pHeap root=(pHeap)malloc(sizeof(Heap));
	if(!root)
	{
		fprintf(stderr,"메모리가 부족합니다\n");
		return NULL;
	}
	root->element=(Element*)calloc(size,sizeof(Element));
	root->cur=0;
	
	return root;
}

// Heap 해제 함수
void HEAP_free(pHeap heap)
{
	free(heap->element);
	free(heap);
}

// Min Heap 에 데이터 삽입 함수
void HEAP_minPush(pHeap heap,Element element)
{
	// 힙의 가장 끝에 데이터 추가
	heap->cur++;
	heap->element[heap->cur]=element;

	int child=heap->cur;
	int parent=child/2;

	// 트리를 올라가면서, 부모 노드와 비교하는 과정
	while( child > 1 && heap->element[parent].tree->weight.freq > heap->element[child].tree->weight.freq)
	{
		// child 노드와 parent 노드를 교체한다.
		swap(&heap->element[parent],&heap->element[child]);
		// 한 레벨 위로 올라간다.
		child=parent;
		parent=child/2;
	}

}

// Min Heap 에서 데이터 꺼내기 함수
Element HEAP_minPop(pHeap heap)
{
	// 힙의 가장 첫번째 원소를 반환
	Element tmp=heap->element[1];

	// 첫번째 원소와 가장 큰에 있는 원소와 바꾸고,
	// 가장 끝 원소는 쓰지 않으니 cur를 감소시킨다.
	swap(&heap->element[1],&heap->element[heap->cur]);
	heap->cur--;

	// 부모 노드에 있는 가장 끝 원소를 자식 노드와 비교하면서
	// 하나씩 내리는 부분
	int parent=1;
	int child=parent*2;

	while(child<=heap->cur && heap->element[parent].tree->weight.freq > heap->element[child].tree->weight.freq)
	{
		// 자식노드중 작은 노드를 선택
		if(child + 1 <=heap->cur)
		{
			child=(heap->element[child].tree->weight.freq < heap->element[child+1].tree->weight.freq) ? child : child + 1;
		}

		swap(&heap->element[parent],&heap->element[child]);

		parent=child;
		child=child*2;

	}

	return tmp;
}

// swap 함수
void swap(Element *a, Element *b)
{
	Element tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}
