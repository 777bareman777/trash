#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

/*
Problem 1: 다음 다항식을 계산하는 프로그램을 작성하시오.
f(x)=6.7x4+3.2x3−x2+x−2, 여기서x∈[−10,10]
1. 함수 f(x)의 계산은 독립된 함수로 작성하여야 하며, 계산 후 그래프를
그리시오.
2. f(x) = 0을 만족하는 x를 구하는 방법을 기술하시오.
3. 주어진 구간에서 f(x)가 최소값을 갖는 x를 구하는 방법을 기술하시오.
4. 선형리스트를 이용한 f(x)를 구현하시오.
*/

typedef struct _term_node *poly_ptr;
typedef poly_ptr poly_node;
typedef poly_ptr poly_list;

typedef struct _term_node {
    float coef;
    int expon;
    poly_ptr link;
} term_node;

// 맨 앞에 값 추가
poly_list polyAddItem(poly_list pl,float coef,int expon);
// expon 값을 가지고 노드 찾기
poly_node FindItem(poly_list pl, int expon);
// 맨 앞에 값 제거
poly_list DeleteFirstItem(poly_list pl);
// expon  값을 가지고 제거
poly_list DeleteItem(poly_list pl, int expon);
// 메모리 제거
poly_list MakeListEmpty(poly_list pl);
// 리스트 내용 출력
void WriteListItem(poly_list pl);

// 다항식 계산
float CalculatePolynomial(poly_list pl,float x);

#endif
