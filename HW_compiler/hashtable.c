#include <hashtable.h>

// 해시 테이블
Node *op_table[MAX_TABLE]; // op 테이블
Node *sym_table[MAX_TABLE]; // symbol 테이블

// 해시 테이블 초기화 함수
void HTBinit(Node *tb[MAX_TABLE])
{
	int i;
	for(i=0;i<MAX_TABLE;i++)
	{
		tb[i]=NULL;
	}
}


// 문자열 복사 함수
void HTBStrCpy(char *dest, const char *src)
{
	while(*src!='\0')
	{
		*dest=*src;
		dest++; src++;
	}
	*dest='\0';
}
// 문자열 비교 함수
int HTBStrCmp(const char *dest, const char *src)
{
	while(*dest != '\0' && (*dest==*src))
	{
		dest++; src++;
	}
	return *dest-*src;
}

// 해시 함수
// 직접 구현하지 않고, openssl 라이브러리의 md5 해시 알고리즘을 이용했음.
// 해시 테이블의 인덱스로 활용하기 때문에
// 해시 값을 적절하게 인덱스 값으로 바꿔줘야 함.
// 값을 MAX_TABLE 나누었을 때, 나머지 값을 인덱스로 사용
int HTBhash(const char* str)
{
	int i;
	int hash=401;
	unsigned char digest[MD5_DIGEST_LENGTH]; // 16

	MD5_CTX context;
	MD5_Init(&context);
	MD5_Update(&context,str,strlen(str));
	MD5_Final(digest,&context);

	for(i=0;i<MD5_DIGEST_LENGTH;i++)
		hash=((hash<<4)+(int)(digest[i])) % MAX_TABLE;	

	return hash % MAX_TABLE;
}

// key 값 추가 함수
void HTBadd(Node *tb[MAX_TABLE],const char *key, int value)
{
	// 	새로운 node를 key와 value를 가지고 초기화
	Node *new_node=(Node*)malloc(sizeof(Node));
	HTBStrCpy(new_node->key,key);
	new_node->value=value;

	// key값을 가지고, 해시 함수를 통해
	// 인덱스 값을 구함.
	int index=HTBhash(key);

	if(tb[index]==NULL)
	{	
		tb[index]=new_node;
	}
	else
	{
		do
		{
			if(tb[index]->value==-1)
				break;
			index++;
			index%=MAX_TABLE;
		}while(tb[index]!=NULL);

		tb[index]=new_node;
	}

}

// key 값에 해당하는 value를 찾음.
Node *HTBsearch(Node *tb[MAX_TABLE],const char *key)
{
	int index=HTBhash(key);

	// 순차 탐색
	while(tb[index] != NULL)
	{
		if(HTBStrCmp(tb[index]->key,key)==0)
		{
			return tb[index];
		}
		index++;
		index%=MAX_TABLE;
	}
	return NULL;
}

// 삭제 함수
bool HTBdestroy(Node *tb[MAX_TABLE],const char *key)
{
	int index=HTBhash(key);
	
	// 비어 있는지 확인
	if(tb[index] == NULL)
	{
		return false;
	}

	while(tb[index]!=NULL)
	{
		if(HTBStrCmp(tb[index]->key,key) == 0)
		{
			free(tb[index]);
			Node *node_tmp=(Node*)malloc(sizeof(Node));
			HTBStrCpy(node_tmp->key,"dummy");
			node_tmp->value=-1;
			return true;
		}
		index++;
		index%=MAX_TABLE;
	}
	return false;
}

// 해시 테이블 내용 출력
void HTBprint_hash(Node *tb[MAX_TABLE])
{
	int i;
	for(i=0;i<MAX_TABLE;i++)
	{
		if(tb[i]!=NULL)
		{
			printf("index: %d\n",i);
			printf("{%s, %d}, ", tb[i]->key,tb[i]->value);
			printf("\n\n");
		}
	}
}
