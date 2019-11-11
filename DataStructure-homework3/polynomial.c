#include <stdio.h>
#include <stdlib.h>
#include <polynomial.h>


// 맨 앞에 값 추가
poly_ptr polyAddItem(poly_ptr pl, float coef, int expon)
{
    poly_ptr ptrNode=NULL;
    ptrNode=(poly_ptr)malloc(sizeof(struct _poly));
    if(ptrNode==NULL){
        fprintf(stderr,"메모리를 할당할 수 없습니다.\n");
    }
    else
    {
        ptrNode->coef=coef;
        ptrNode->expon=expon;
        ptrNode->link=pl;
        pl=ptrNode;
    }
    return pl;
}

// expon 값을 가지고 노드 찾기
poly_ptr FindItem(poly_ptr pl,int expon)
{
	poly_ptr tnode=pl;
	while(tnode != NULL)
	{
		if(tnode->expon == expon)
		{
			printf("%d 차 is in pl\n",expon);
			return tnode;
		}
		tnode=tnode->link;
	}
	printf("%d 차 does not exist.\n",expon);
	return NULL;
}

// 맨 앞에 값 제거
poly_ptr DeleteFirstItem(poly_ptr pl)
{
	poly_ptr anode=pl;
	if( anode == NULL)
	{
		printf("pl is emplty.\n");
	}
	else
	{
		pl=anode->link;
		free(anode);
	}
	return pl;
}

// expon 값을 가지고 제거
poly_ptr DeleteItem(poly_ptr pl, int expon)
{
	poly_ptr anode=pl;
	poly_ptr dnode=anode->link;
	while(dnode != NULL)
	{
		if(dnode->expon == expon){
			anode->link=dnode->link;
			free(dnode);
			break;
		}
		anode=dnode;
		dnode=anode->link;	
	}	
	return pl;
}

// 메모리 제거
poly_ptr MakeListEmpty(poly_ptr pl)
{
	poly_ptr anode=pl;
	poly_ptr bnode=NULL;

	while(anode != NULL)
	{
		bnode=anode->link;
		free(anode);
		anode=bnode;
	}
	pl=NULL;
	return pl;
}

// 리스트 내용 출력
void WriteListItem(poly_ptr pl)
{
	poly_ptr tnode=pl;
	while( tnode != NULL)
	{	
		printf("%+.2fx^%d \t",tnode->coef,tnode->expon);
		tnode=tnode->link;
	}
	printf("\n");
}

// 다항식 계산
float CalculatePolynomial(poly_ptr pl,float x)
{
	float sum=0;
	poly_ptr tnode=pl;
	while( tnode != NULL)
	{
		float tmp=1;
		for(int i=0;i<tnode->expon;i++)
		{
			tmp*=x;
		}
		tmp*=tnode->coef;
		sum+=tmp;
		tnode=tnode->link;
	}
	return sum;
}

////////////////////////////////////////

// 두 다항식의 가감(덧셈, 뺄셈) ADT

// 노드 생성
poly_ptr getNode()
{
	poly_ptr node;
	node=(poly_ptr)malloc(sizeof(poly));
	if(node==NULL)
	{
		perror("The memory is full\n");
		exit(1);
	}
	return node;
}

// 노드 추가
void append(float coef, int expon, poly_ptr *pptr)
{
	poly_ptr temp;
	temp=getNode();
	
	temp->coef=coef;
	temp->expon=expon;
	(*pptr)->link=temp;
	*pptr=temp;
}

// 노드 삭제
void erase(poly_ptr *pptr)
{
	poly_ptr temp;
	while(*pptr)
	{
		temp=*pptr;
		*pptr=(*pptr)->link;
		free(temp);
	}
}

poly_ptr poly_add(poly_ptr a, poly_ptr b)
{
	poly_ptr front, rear, temp;
	float sum;

	rear=getNode();
	front=rear;

	while(a != NULL && b != NULL)
	{
		switch(compare(a->expon,b->expon))
		{
			case -1: /* ( a->expon < b->expon */
				append(b->coef,b->expon,&rear);
				b=b->link;
				break;
			case 0: /* a->expon == b->expon */
				sum=a->coef + b->coef;
				if(sum)
					append(sum,a->expon,&rear);
				a=a->link; b=b->link;
				break;
			case 1: /* a->expon > b->expon */
				append(a->coef,a->expon,&rear);
				a=a->link;
				break;
		}
	}

	for(; a; a=a->link)
		append(a->coef,a->expon,&rear);
	for(; b; b=b->link)
		append(b->coef,b->expon, &rear);
	
	rear->link=NULL;
	temp=front;
	front=front->link;
	free(temp);
	return front;
}

int compare(int a, int b)
{
	int result=a-b;
	if(result==0)
		return 0;
	else if(result<0)
		return -1;
	return 1;
}
