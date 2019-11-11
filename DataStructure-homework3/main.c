#include <stdio.h>
#include <stdlib.h>
#include <polynomial.h>
#include <array_polynomial1.h>
#include <array_polynomial2.h>

int main()
{
	// 선형 리스트를 이용한 두 다항식의 가감 테스트
	/*
	poly_ptr a=NULL;
	poly_ptr b=NULL;

	a=getNode();
	a->coef=-2;a->expon=0;a->link=NULL;
	a=polyAddItem(a,1,1);
	a=polyAddItem(a,-1,2);
	a=polyAddItem(a,3.2,3);
	a=polyAddItem(a,6.7,4);

	b=getNode();
	b->coef=-2;b->expon=0;b->link=NULL;
	b=polyAddItem(b,1,1);
	b=polyAddItem(b,-1,2);
	b=polyAddItem(b,3.2,3);
	b=polyAddItem(b,6.7,4);

	poly_ptr result=NULL;
	result=poly_add(a,b);

	WriteListItem(a);
	WriteListItem(b);
	WriteListItem(result);
	*/
	
	// 첫번째 배열 자료구조를 이용한 두 다항식의 가감 테스트
	/*
	array_polynomial1 a={ 5, {3,6,0,0,0,10}};
	array_polynomial1 b={ 4, {7,0,5,0,1}};
	array_polynomial1 result;
	result=array_poly_add1(a,b);
	array_polynomial_print1(a);
	array_polynomial_print1(b);
	array_polynomial_print1(result);
	*/

	// 두번째 배열 자료구조를 이용한 두 다항식의 가감 테스트
	array_polynomial2 a[SIZE]={ {5,10},	{4,5}, {3,0}, {3,5},{8,2},{5,0}, {0,0}, };
	int sp=0, fp=2;
	int sq=3, fq=5;
	int sr=0, fr=0;

	array_poly_add2(a,sp,fp,sq,fq,&sr,&fr);
	array_polynomial_print2(a,sp,fp,sq,fq,sr,fr);


	return 0;
}
