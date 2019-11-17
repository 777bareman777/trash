# 산술식의 이진트리와 활용

## 목적 (Purpose)

- 이진트리의 ADT 설계와 구현
- 이진트리의 노드 방문 방법을 이용한 산술식의 다른 표기
- 산술식의 이진트리 표현과 컴파일러의 처리방법의 이해
- 이진트리를 이용한 문자열 압출 알고리즘의 설계와 구현

## 설계 문제 (Design problem)

**Probelm 1** : 연산자 우선순위를 반영하는 산술식의 이진트리 설계와 구현
**Problem 2** : Huffman 트리를 이용한 문자열의 압축 알고리즘의 설계와 구현

## 기능과 사양 (Function and specification)

### 산술식의 이진트리 설계와 구현

- Infix 표기의 산술식을 입력받아 이진트리로 나타내는 프로그램의 작성
- 컴퓨터 내부에서 이진트리의 자료구조 표현을 제공해야 함
- 이진트리 관련 ADT가 C/C++ 함수로 작성되어야 함
- 선택한 이진트리에 대한 infix, prefix, postfix, level 순서에 대한 트리의 방문 함수 제공

### 문자열 압축 알고리즘의 설계와 구현

- 100 글자 이상이 포함되는 좋아하는 글을 입력받아 Huffman tree를 생성
- 입력 받은 글의 Huffman 코드를 출력
- 출력된 코드를 입력받아 문자열을 출력

## 평가 (Evaluation)

### 산술식의 이진트리 설계와 구현

- 설계 함수들 간의 논리적 관계를 고려하여 3개 이상의 소스파일로 나누어져 있어야 함
- 최소한 5개의 이상의 산술식에 대해 infix, prefix, postfix, level 순서의 방문 결과
- 각 산술식은 적어도 최소한 5개 이상의 연산자와 최소한 1개 이상의 () 가 있어야 함

### 문자열 압축 알고리즘의 설계와 구현

- 입력된 문자열이 100자 이상인가
- 입력된 문자열과 출력된 문자열의 동일 여부
- ASCII 문자열 코딩과 Huffman 코딩과 크기 비교

## 참고 자료

- https://playground10.tistory.com/98

- https://wooyaggo.tistory.com/95

- https://m.blog.naver.com/PostView.nhn?blogId=ndb796&logNo=220829142548&proxyReferer=https%3A%2F%2Fwww.google.com%2F

- https://withhamit.tistory.com/12






# 산술식의 binary tree 구현 알고리즘의

- operator 와 operand 를 위한 두개의 stack을 이용한다.

- Binary tree를 생성을 한다

	- 입력 expression 은 왼쪽부터 오른쪽으로 scan

	- operator 는 operator의 stack에 push

	- operand 는 operand의 stack에 push

	- 입력 operator 가 operator의 stack의 operator 보다 연산 순위가 크면 stack에 push

	- 그렇지 않으면, operand의 stack 에서 두 operand 에 대해 operator의 stack의 operator의 연산결과를 operand의 stack에 push 한다. 그 후에 입력 operator를 stack에 push 한다.

	- 입력 operator "(" 이면, oeprator의 stack에서 push를 하고 ")"를 만날때 까지 먼저 계산을 한다.

	- infix 표기 식의 scan이 끝나면 stack의 내용을 모두 계산한다.







