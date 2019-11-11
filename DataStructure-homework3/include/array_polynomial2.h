#ifndef _ARRAY_POLYNOMIAL2_H
#define _ARRAY_POLYNOMIAL2_H

#define SIZE 100

// 배열을 이용한 두번째 방법
// 계수, 차수 값을 가지는 구조체 배열을 선언해, 0이 아닌 항들만 저장

/*
  의미 있는 항들만 저장하므로, 희소 다항식의 경우 공간을 절약할 수 있음.
  희소 다항식이 아닌 경우 공간의 낭비가 심함.   
*/

typedef struct _array_polynomial2
{
	float coef;
	int expon;
} array_polynomial2;

// 다항식의 덧셈 계산 함수
void array_poly_add2(array_polynomial2 a[],
		int sp, int fp, int sq, int fq, int *sr, int *fr);

// 다항식의 뺼셈 게산 함수
void array_poly_sub2(array_polynomial2 a[],
        int sp, int fp, int sq, int fq, int *sr, int *fr);

// 다항식의 지수, 계수 추가 함수
void array_poly_append2(array_polynomial2 a[], int *index ,float coef, int expon);

// 계수들의 값 비교 함수
int compare2(int a, int b);

// 다항식 출력 함수
void array_polynomial_print2(array_polynomial2 a[],
		int sp, int fp, int sq, int fq, int sr, int fr);


#endif
