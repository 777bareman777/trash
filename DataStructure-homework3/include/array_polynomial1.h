#ifndef _ARRAY_POLYNOMIAL1_H
#define _ARRAY_POLYNOMIAL1_H

#define MAX_DEGREE 101 // 다항식의 최대 차수 + 1

// 배열을 이용한 첫번째 방법
// 다항식의 모든 차수에 대한 계수 값을 배열에 저장
// 모든 차수에 대한 계수 값들을 배열 coef에 저장
// 다항식의 최고 차수는 degree에 저장

/* 
   다항식의 덧셈이나 뺄셈 시에 같은 차수의 계수를
   쉽게 찾을 수 있음.
   다항식의 항의 계수가 0인 희소 다항식의 경우 공간 낭비가 심함.
*/

typedef struct _array_polynomial1
{
	int degree;
	float coef[MAX_DEGREE];
} array_polynomial1;

// 다항식의 합 계산 함수
array_polynomial1 array_poly_add1(array_polynomial1 a, array_polynomial1 b);
// 계수들의 값 비교 함수
int compare1(int a, int b);
// 다항식 출력 함수
void array_polynomial_print1(array_polynomial1 a);


#endif
