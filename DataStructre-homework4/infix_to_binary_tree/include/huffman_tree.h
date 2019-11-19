#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#define FILENAME "huffman.txt"
#define MAX_TREE_HT 100    
#define ALPHABET_SIZE 27


// 호프만 트리 노드
typedef struct MinHeapNode
{
	char data;
	int freq;
	int* array;
	struct MinHeapNode* left;
	struct MinHeapNode* right;
}MinHeapNode;

typedef struct MinHeap
{
	int size;
	int capacity;
	MinHeapNode** array;
}MinHeap;


typedef struct Table {
	char data;
	char huffmancode[MAX_TREE_HT];
}Table;

MinHeapNode* ALLOCATE_NODE(char data, int freq);
void SWAP_NODE(MinHeapNode** a, MinHeapNode** b);
void MIN_HEAPIFY(MinHeap* minHeap, int index);
int IS_HEAP_SIZE_ONE(MinHeap* minHeap);
MinHeapNode* EXTRACT_MIN(MinHeap* minHeap);
void INSERT_MIN_HEAP(MinHeap* minHeap, MinHeapNode* minHeapNode);
void printArr(int* arr, int n);
int IS_LEAF(MinHeapNode* root);
MinHeap* BUILD_MIN_HEAP(char* data, int* freq, int size);
MinHeapNode* BUILD_HUFFMAN_TREE(char* data, int* freq, int size);
void MAKE_HUFFMAN_CODE(MinHeapNode* root, int* arr, int top);
void ENCODING(char* story, int size);
MinHeapNode* HUFFMAN(char* data, int* freq, int size);
void DECODING();
int compare2(const void* A, const void* B);
void test2();

#endif
