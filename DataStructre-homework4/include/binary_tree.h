#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

// reference
// https://meylady.tistory.com/16
// https://wkdtjsgur100.github.io/binary-search-tree/
//
//



/*
 * binary tree는 각 노드의 subtree의 2개 이하로 이루어져 있으며, 각 node는
 * left subtree, right subtree 들과 계층적 관계를 갖고 있다. Tree는 empty
 * 일 수 있지만, binary tree는 empty가 될 수가 없다. 또한 binary tree의
 * subtree들은 순서(order)의 관계를 가지만, tree의 subtree 들은 순서의 관
 * 계를 고려하지 않는다.
 * 
 *************************************************************************
 *
 * binary tree 같은 자료 구조는 subtree의 2개 이하로 이루어져 있고, 각 노드의
 * 번호를 찾을 수 있는 규칙이 간단하기 때문에 배열을 통해서도 쉽게 구현할 수가
 * 있다. 트리의 균형이 잘 잡혀있는 경우, 시간복잡도가 O(logN) 이다
 *
 *************************************************************************
 *
 * binary tree에는 left subtree, right subtree가 존재하며, 항상 두 개의 subtree
 * 가 존재하는 것은 아니다. binary tree 에도 다양한 종류가 있다. 아래에 나열된
 * 것들이 대표하는 binary tree 이다.
 * -> Skewed binary tree(편향이진트리)
 * -> Full binary tree(포화이진트리),
 * -> Complete binary tree(완전이진트리)
 *
 *************************************************************************
 *
 * Skewed binary tree(편향이진트리)는 하나의 subtree로만 이뤄진 경우이다.
 * -> Right skewed binray(오른쪽편향 이진트리), Left skewed binary(왼쪽편향 이진트리)
 * 이런 경우 linear data structure 와 다른 점이 없기 때문에 좋지 않는 트리의
 * 구조중 하나이다. 특정 노트를 탐색하는 경우 시간복잡도가 O(n)이기 때문이다.
 * 
 *************************************************************************
 *
 * Fuull binary tree(포화이진트리)는 두개의 subtree로만 이뤄진 경우이다.
 * 이런 경우는 드문 경우에 속한다. Full binary tree의 경우 트리의 depth만
 * 알아도 그 계층의 노드의 개수를 알 수 있고, 전체 노드의 개수를 파악할 수 있다.
 * 만약 depth 가 h라면, full binary tree는 2^h-1 개의 노드를 가진다.
 * 
 * 또한 node의 번호는 1에서 2^h-1 순으로 주어지고, level에 따라 root 아래로
 * 같은 level에서는 왼쪽에서 오른쪽으로 번호를 준다.
 * 만약 node X의 parent 가 node floor(X/2) 이며,
 * 그렇지 않으면 X=1(root) 이다.
 *
 * node 1은 root이며 parent가 존재하지 않다.
 * node X의 왼쪽 child는 node 2X이며, 그렇지 않으면 2X>n 이다.
 * 만약 2X>n 이면, node X 는 왼쪽 child가 없다는 것이다.
 * node X의 오른쪽 child는 node 2X+1이며, 그렇지 않으면 2X+1>n 이다.
 * 만약 2X+1>n 이면, node X는 오른쪽 child가 없다는 것이다.
 *
 *************************************************************************
 *
 * Complete binary tree(완전이진트리)는 가장 일반적인 구조이다. 트리의 깊이를
 * 알고 있다면, 예상 노드의 개수(최대)를 구할 수 있다. 또한 트리의 탐색을 할 때,
 * 무조건 왼쪽노드나 오른쪽 노드가 있는지 확인해야 한다. 
 * 
 * Complete binary tree는 적어도 n개의 node를 갖는 fully binary tree 라고 볼 수 있다.
 * Tree 내 모든 node을 leve에 따라 root 아래로, 같은 level에서는 왼쪽에서 오른쪽 순으로
 * 번호를 주면 된다. 즉, 1에서 n까지 번호를 준 binary tree는 유일한 n node를 갖는
 * Complete binary tree 라고 볼 수 있다.
 *
 *************************************************************************
 *
 */

typedef struct _Tree *pTree;
typedef struct _Tree *pNode;
typedef struct _Tree
{
	int value;
	pTree left;
	pTree right;
} Tree,Node;

// node 생성 함수
pNode BT_createNode(void);

// node 삽입 함수
pTree BT_insert(pTree root, int value);

// 최소 값을 가진 node 함수 검색 함수
pNode BT_findMinNode(pNode tree);

// node 삭제 함수
pTree BT_delete(pTree root, int value);

// node 검색 함수
pTree BT_search(pTree root, int value);

// infix 방식으로 트리 출력 함수
void BT_infixPrint(pTree root);

// postfix 방식으로 트리 출력 함수
void BT_postfixPrint(pTree root);

// prefix 방식으로 트리 출력 함수
void BT_prefixPrint(pTree root);

// level 방식으로 트리 출력 함수
void BT_levelPrint(pTree root);


#endif
