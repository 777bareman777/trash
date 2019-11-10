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
		printf("%.2fx^%d \t",tnode->coef,tnode->expon);
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

