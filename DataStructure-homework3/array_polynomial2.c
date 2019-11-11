#include <stdio.h>
#include <array_polynomial2.h>

// 다항식의 합 게산 함
void array_poly_add2(array_polynomial2 a[], 
		int sp, int fp, int sq, int fq, int *sr, int *fr)
{
	float temp;
	int avail;

	avail=fq+1;
	*sr=avail;

	while(sp<=fp && sq<=fq)
	{
		switch(compare2(a[sp].expon,a[sq].expon))
		{
			case -1: /* a[sp].expon < a[sq].expon */
				array_poly_append2(a,&avail,a[sq].coef,a[sq].expon);
				sq++;
				break;
			case 0: /* a[sp].expon == a[sq].expon */
				temp=a[sp].coef+a[sq].coef;
				array_poly_append2(a,&avail,temp,a[sq].expon);
				sq++; sp++;
				break;
			case 1: /* a[sp].expon > a[sq].expon */
				array_poly_append2(a,&avail,a[sp].coef,a[sp].expon);
				sp++;
				break;
		}
	}
	for(; sp<=fp;sp++)
		array_poly_append2(a,&avail,a[sp].coef,a[sp].expon);
	for(; sq<=fq;sq++)
		array_poly_append2(a,&avail,a[sq].coef,a[sq].expon);
	
	*fr=avail-1;
}

// 계수들의 값 비교 함수
int compare2(int a, int b)
{
	int result=a-b;
	if(result==0)
		return 0;
	else if(result<0)
		return -1;
	return 1;
}

// 다항식의 지수, 계수 추가 함수
void array_poly_append2(array_polynomial2 a[], int *index, float coef, int expon)
{
	a[*index].coef=coef;
	a[*index].expon=expon;
	(*index)++;
}

// 다항식 출력 함수
void array_polynomial_print2(array_polynomial2 a[],
		int sp,int fp, int sq, int fq, int sr, int fr)
{
	int i;
	for(i=sp;i<=fp;i++)
	{
		printf("%+.2fx^%d \t",a[i].coef,a[i].expon);
	}
	printf("\n");
	
	for(i=sq;i<=fq;i++)
	{
		printf("%+.2fx^%d \t",a[i].coef,a[i].expon);
	}
	printf("\n");

	for(i=sr;i<=fr;i++)
	{
		printf("%+.2fx^%d \t",a[i].coef,a[i].expon);
	}
	printf("\n");
}
