#include <stdlib.h>
#include <stack.h>


// 스택 생성 함수
pStack STACKcreate(int size)
{
	pStack stack=NULL;
	stack=(pStack)malloc(sizeof(Stack));
	if(!stack)
		return NULL;
	
	stack->value=(pTree*)calloc(size,sizeof(pTree));
	stack->top=-1;
	stack->size=size;
	return stack;
}

// 스택이 가득 차있는지 확인하는 함수
bool STACKisFull(pStack stack)
{
	if(stack->top == stack->size-1)
		return true;
	else
		return false;
}

// 스택이 비어있는지 확인하는 함수
bool STACKisEmpty(pStack stack)
{
	if(stack->top==-1)
		return true;
	else
		return false;
}

// 스택에 값 넣는 함수
void STACKpush(pStack stack,pTree value)
{
	if(STACKisFull(stack))
		;
	else
	{
		stack->top+=1;
		stack->value[stack->top]=value;
	}
}

// 스택에서 값 가져오는 함수
pTree STACKpop(pStack stack)
{
	if(STACKisEmpty(stack))
		;
	else
	{
		pTree tmp=stack->value[stack->top];
		stack->top-=1;
		return tmp;
	}

	return NULL;
}
// 스택 해제 함수
void STACKfree(pStack stack)
{
	free(stack->value);
	free(stack);
}
