#include <stdio.h>
#include <array_polynomial1.h>

#define MAX(a,b) ( ((a)>(b)) ? (a):(b) )


// 배열을 이용한 구현 방식 1

// 다항식의 덧셈 함수
array_polynomial1 array_poly_add1(array_polynomial1 a, array_polynomial1 b)
{
	array_polynomial1 temp;
	int aIndex, bIndex, tempIndex;
	int aDegree, bDegree;

	aIndex=0; bIndex=0; tempIndex=0;
	aDegree=a.degree; bDegree=b.degree;
	temp.degree=MAX(aDegree,bDegree);

	while(aIndex<=a.degree && bIndex<=b.degree)
	{
		switch(compare1(aDegree,bDegree))
		{
			case -1: /* a.degree < b.degree */
				temp.coef[tempIndex++]=b.coef[bIndex++];
				bDegree--;
				break;
			case 0:	/* a.degree == b.degree */
				temp.coef[tempIndex++]=a.coef[aIndex++]+b.coef[bIndex++];
				aDegree--; bDegree--;
				break;
			case 1: /* a.degree > b.degree */
				temp.coef[tempIndex++]=a.coef[aIndex++];
				aDegree--;
				break;
		}
	}
	return temp;
}


// 다항식의 뺄셈 함수
array_polynomial1 array_poly_sub1(array_polynomial1 a, array_polynomial1 b)
{
	array_polynomial1 temp;
	int aIndex, bIndex, tempIndex;
	int aDegree, bDegree;

	aIndex=0; bIndex=0; tempIndex=0;
	aDegree=a.degree; bDegree=b.degree;
	temp.degree=MAX(aDegree,bDegree);

	while(aIndex<=a.degree && bIndex<=b.degree)
	{
		switch(compare1(aDegree,bDegree))
		{
			case -1: /* a.degree < b.degree */
				temp.coef[tempIndex++]=-(b.coef[bIndex++]);
				bDegree--;
				break;
			case 0:	/* a.degree == b.degree */
				temp.coef[tempIndex++]=a.coef[aIndex++]-b.coef[bIndex++];
				aDegree--; bDegree--;
				break;
			case 1: /* a.degree > b.degree */
				temp.coef[tempIndex++]=a.coef[aIndex++];
				aDegree--;
				break;
		}
	}
	return temp;
}

// 계수들의 값 비교 함수
int compare1(int a, int b)
{
	int result=a-b;
	if(result==0)
		return 0;
	else if(result<0)
		return -1;
	return 1;
}
// 다항식 출력 함수
void array_polynomial_print1(array_polynomial1 a)
{
	int i;
	for(i=0;i<a.degree;i++)
	{
		if(a.coef[i] != 0)
			printf("%+.2fx^%d \t", a.coef[i],a.degree-i);
	}
	printf("%+.2f^%d\n",a.coef[i],a.degree-i);
}

