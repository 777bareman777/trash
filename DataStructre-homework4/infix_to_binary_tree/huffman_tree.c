#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <huffman_tree.h>

MinHeapNode* root;
Table* table;
int k = 0;

//호프만트리를 만들기 위한 함수이다.
MinHeapNode* HUFFMAN(char* data, int* freq, int size)
{
	MinHeapNode* root = BUILD_HUFFMAN_TREE(data, freq, size);        //호프만 트리를 만든다.
	int top = 0;
	root->array = (int*)malloc(MAX_TREE_HT);
	MAKE_HUFFMAN_CODE(root, root->array, top);
	return root;
}

//호프만 트리를 만드는 함수
MinHeapNode* BUILD_HUFFMAN_TREE(char* data, int* freq, int size)
{
	MinHeapNode* left, * right, * top;    //트리에 필요한 top과 left,right를 만들어준다.


	MinHeap* minHeap = BUILD_MIN_HEAP(data, freq, size);        //호프만 트리를 만들기위한 Min Heap을 만들어준다.


	//minHeap의 size가 1일때까지 반복한다. 호프만 트리 만드는 과정
	while (!IS_HEAP_SIZE_ONE(minHeap))
	{
		//가장 빈도수 낮은 두 값을 빼온다.
		left = EXTRACT_MIN(minHeap);
		right = EXTRACT_MIN(minHeap);
		top = ALLOCATE_NODE('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		INSERT_MIN_HEAP(minHeap, top);
	}

	printf("%c\n\n", EXTRACT_MIN(minHeap)->data);
	return EXTRACT_MIN(minHeap);
}


//새로운 노드를 만들어준다. MinHeap에 저장을 하기 위해서
MinHeapNode* ALLOCATE_NODE(char data, int freq)
{
	MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
	temp->left = NULL;
	temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}

//MIN_HEAP으로 만드는 HEAPIFY과정을 보인다.
void MIN_HEAPIFY(MinHeap* minHeap, int index)
{
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
	{
		smallest = left;
	}
	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
	{
		smallest = right;
	}
	if (smallest != index)
	{
		SWAP_NODE(&minHeap->array[smallest], &minHeap->array[index]);
		MIN_HEAPIFY(minHeap, smallest);
	}
}

//힙의 사이즈가 1인지 아닌지 판단해주는 함수
int IS_HEAP_SIZE_ONE(MinHeap* minHeap)
{
	return (minHeap->size == 1);
}

//Root에 있는 원소를 추출후 다시 MinHeap을 만드는 과정이다.
MinHeapNode* EXTRACT_MIN(MinHeap* minHeap)
{
	MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	minHeap->size--;
	MIN_HEAPIFY(minHeap, 0);
	return temp;
}

//구성된 MIN_HEAP에 새로운 NODE(top,left,right)를 추가시켜주는 과정이다.
void INSERT_MIN_HEAP(MinHeap* minHeap, MinHeapNode* minHeapNode)
{
	int i;
	minHeap->size++;    //Min Heap의 사이즈를 하나 추가시켜준다.

	i = minHeap->size - 1;    //마지막 인덱스

	//빈도수를 비교해가며 어디에 들어가야할지 인덱스를 찾는 과정이다.
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
	{
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

//MIN_HEAP를 만든다.
MinHeap* BUILD_MIN_HEAP(char* data, int* freq, int size)
{
	int i, n;

	MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
	minHeap->size = size;
	minHeap->capacity = size;
	minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));

	//만들어준 MinHeap의 각 노드에 알파벳과 빈도수를 넣어준다.
	for (i = 0; i < size; i++)
	{
		minHeap->array[i] = ALLOCATE_NODE(data[i], freq[i]);
	}

	//minHeap을 Heapify 해서 넘겨준다.
	n = (minHeap->size - 1) / 2;
	for (i = n; i >= 0; i--)
	{
		MIN_HEAPIFY(minHeap, i);
	}
	return minHeap;
}

//호프만코드를 만드는 과정이다.
void MAKE_HUFFMAN_CODE(MinHeapNode* root, int* arr, int top)
{
	int i;
	//왼쪽이 있다면 배열에 0을 추가하고 왼쪽 자식으로 이동한다.
	if (root->left)
	{
		arr[top] = 0;
		MAKE_HUFFMAN_CODE(root->left, arr, top + 1);
	}
	//오른쪽이 있다면 배열에 1을 추가하고 오른쪽 자식으로 이동한다.
	if (root->right)
	{
		arr[top] = 1;
		MAKE_HUFFMAN_CODE(root->right, arr, top + 1);
	}
	//leaf일때 그에 해당하는 알파벳과 호프만코드를 저장한다.
	if (IS_LEAF(root))
	{
		//root->data 에는 호프만코드의 알파벳
		table[k].data = root->data;

		//arr에는 호프만코드가 들어있음.
		for (i = 0; i < top; i++) {
			table[k].huffmancode[i] = arr[i] + 48;
			//printf("%c\n",table[k].huffmancode[i]);
		}
		table[k].huffmancode[i] = '\0';
		k++;
	}
}

//인코딩 함수
void ENCODING(char* story, int size) {
	int i = 0;
	FILE* fp = fopen("week10_incoding_output.txt", "w");
	//테이블에 index값으로 접근하여 문자열들을 호프만코드로 바꾸어준다.
	for (i = 0; i < size; i++) {
		//띄어쓰기 ' '일때는 아스키코드로 바로 index 접근을 할수 없기때문에 따로 만들어준다.
		if (story[i] == ' ') {
			fprintf(fp, "%s", table[0].huffmancode);
		}
		else {
			fprintf(fp, "%s", table[story[i] - 96].huffmancode);
		}
	}
	fclose(fp);
	printf("*******ENCODING SUCCESS********\n");
}
//디코딩 함수
void DECODING() {
	int i, size = 0;
	char temp_char;
	MinHeapNode* tempNode = root;
	int* code = (int*)malloc(sizeof(int));

	FILE* fp = fopen("week10_incoding_output.txt", "r");
	FILE* fop = fopen("week10_decoding_output.txt", "w");

	//호프만 코드를 가져온다.
	while (!feof(fp))
	{
		code = (int*)realloc(code, sizeof(int) * (size + 1));
		fscanf(fp, "%c", &temp_char);
		code[size] = temp_char - 48;
		size++;
	}

	//가져온 호프만 트리를 탐색하는데 0이면 left로 1이면 right로 이동하여
	//leafNode일 경우 텍스트파일에 저장한다.
	for (i = 0; i < size; i++) {
		if (IS_LEAF(tempNode)) {
			fprintf(fop, "%c", tempNode->data);
			tempNode = root;
		}

		if (code[i] == 0) {
			tempNode = tempNode->left;
		}
		else if (code[i] == 1) {
			tempNode = tempNode->right;
		}
	}

	fclose(fp);
	fclose(fop);
	printf("*******DECODING SUCCESS********\n");
}

//leaf 노드인가 아닌가에 대해 판단해주는 함수이다.
int IS_LEAF(MinHeapNode* root)
{
	return !(root->left) && !(root->right);
}

void SWAP_NODE(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

int compare2(const void* A, const void* B)
{
	Table* ptrA = (Table*)A;
	Table* ptrB = (Table*)B;

	char a = ptrA->data, b = ptrB->data;

	if (a == b) return 0;
	else if (a > b) return 1;
	else return -1;
}

void test2() {
	FILE* fp_r; //파일 입출력 변수
	FILE* fp_table;
	int cnt = 0;    //파일 입력 변수 개수
	int i, ascii_number;
	char* story = (char*)malloc(sizeof(char));    //문자열 배열
	char* letter = (char*)malloc(sizeof(char) * 27);    //' ' ~ 'Z' 까지 저장하는 배열
	int* frequency = (int*)malloc(sizeof(int) * 27);    //위의 배열에 대한 빈도수를 저장하는 배열
	table = (Table*)malloc(sizeof(Table) * 27);    //알파벳과 빈도수에 대한 테이블을 저장하는 구조체 배열
	fp_r = fopen(FILENAME, "rt");        //파일 읽기
	if (fp_r == NULL)    //파일 없다면 에러 처리
	{
		//printf("**** File open error ****\n");
		system("pause");
		exit(1);
	}
	//story라는 배열로 알파벳을 받아옴.
	while (!feof(fp_r))
	{
		story = (char*)realloc(story, sizeof(char) * (cnt + 1));
		fscanf(fp_r, "%c", &story[cnt]);
		cnt++;
	}
	//모든 데이터와 빈도수의 배열을 0으로 초기화 해줌.
	for (i = 0; i < 27; i++)
	{
		letter[i] = ' ';
		frequency[i] = 0;
	}
	//받아온 문자열을 알파벳을 저장하는 배열과 빈도수를 저장하는 배열로 나누어서 저장해준다.
	for (i = 0; i < cnt; i++)
	{
		ascii_number = story[i] - 97;
		//띄어쓰기 ' '일때는 따로 관리해줘야한다.
		if (story[i] == ' ') {
			letter[26] = story[i];
			frequency[26]++;
		}
		else {
			if (ascii_number != -148) {
				letter[ascii_number] = story[i];
				frequency[ascii_number]++;
			}
		}
	}
	root = HUFFMAN(letter, frequency, ALPHABET_SIZE);    //호프만 트리를 만들고 ROOT값을 가져온다.

	fclose(fp_r);
	qsort(table, ALPHABET_SIZE, sizeof(Table), compare2);    //테이블을 알파벳기준 정렬을 한다.

	printf("*******TABLE********\n");
	fp_table = fopen("week10_table.txt", "w");    //테이블을 텍스트 파일로 만들어준다.
	for (i = 0; i < ALPHABET_SIZE; i++) {
		fprintf(fp_table, "%c, %s\n", table[i].data, table[i].huffmancode);
		printf("%c, %s\n", table[i].data, table[i].huffmancode);
	}
	printf("-----------------------------------\n");
	ENCODING(story, cnt - 1);    //인코딩
	DECODING();        //디코딩
}
