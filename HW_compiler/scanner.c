#include <scanner.h>

extern Node *op_table[MAX_TABLE];
extern Node *sym_table[MAX_TABLE];

char *ClangKeyword[]={"asm", "auto", "break", "case", "char", "const",
	"continue", "default", "do", "double", "else", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while","enum"};

char *ClangOperation[]={"++", "--", "()", "[]", ".", "->", "(){}",
	"++","--","+","-","!","~","()","*","&", "sizeof", "_Alignof",
	"*", "/", "%",
	"+","-",
	"<<",">>",
	"<","<=",
	">",">=",
	"==","!=",
	"&",
	"^",
	"|",
	"&&",
	"||",
	"?:",
	"=",
	"+=","-=",
	"*=","/=","%=",
	"<<=",">>=",
	"&=","^=","|="};

char *ClangDelimiter[]={"(",")","{","}","[","]",";"};

char *ClangEtc[]={"#","include","headerfile"};

char *ClangSymbol[]={"IDENTIFIER","DIGIT"};


// operation talbe을 만드는 함수
// C 프로그래밍의 언어의 키워드, 연산자들을 넣었음.
void init()
{
	HTBinit(op_table);
	HTBinit(sym_table);
	for(ClangKeywordIndex i = _ASM ; i<_ENUM_COUNT_KEYWORD ; i++)
	{
//		printf("%s -> %d\n",ClangKeyword[i-_ASM],i);
		HTBadd(op_table,ClangKeyword[i-_ASM],i);
	}
	for(ClangOperationIndex i = _POSTFIX_INCREMENT ; i<_ENUM_COUNT_OPERATION;i++)
	{
//		printf("%s -> %d\n",ClangOperation[i-_POSTFIX_INCREMENT],i);
		HTBadd(op_table,ClangOperation[i-_POSTFIX_INCREMENT],i);
	}
	for(ClangDelimiterIndex i = _LEFT_PAREN; i<_ENUM_COUNT_DELIMITER;i++)
	{
//		printf("%s -> %d\n",ClangDelimiter[i-_LEFT_PAREN],i);
		HTBadd(op_table,ClangDelimiter[i-_LEFT_PAREN],i);

	}
	for(ClangEtcIndex i=_SHARP;i<_ENUM_COUNT_ETC;i++)
	{
//      printf("%s -> %d\n",ClangEtc[i-_SHARP],i);
		HTBadd(op_table,ClangEtc[i-_SHARP],i);
	}
}

bool scanner()
{
	int i=0,j=0;
	FILE *fp=NULL;
	FILE *op=NULL;
	FILE *sym=NULL;
	char line[1024]={0,};
	char tmp[MAX_KEY]={0,};


	fp=fopen("code.txt","r");
	if(!fp)
	{
		perror("code.txt open failed\n");
		return false;
	}
	op=fopen("operation.csv","w");
	if(!op)
	{
		perror("operation.csv open faild\n");
		return false;
	}
	sym=fopen("symbol.csv","w");
	if(!sym)
	{
		perror("symbol.csv open failed\n");
		return false;
	}

	while(fgets(line,sizeof(line)-1,fp)!=0)
	{
		i=0;
//		printf("line: %s\n",line);
		while(line[i] !='\0')
		{
			j=0;memset(tmp,0,sizeof(tmp));
			// 영문, 언더바 판별 조건문
			// 그와 동시에 C언어 키워드 판별 조건문
			if( (line[i]>='A' && line[i]<='Z') || (line[i]=='_') || (line[i]>='a' && line[i]<='z'))
			{
				j=0; memset(tmp,0,sizeof(tmp));
				tmp[j]=line[i];
				// 다음에 오는 문자가 영문, 언더바인지 판별하는 조건문
				// 만약 다음 문자가 영문, 언더바가 아니면 빠져나옴
				while(1)
				{	
					i++;j++;

					//printf("line[%d]: %c\n",i,line[i]);

					if( (line[i]>='A' && line[i]<='Z') || (line[i]=='_') || (line[i]>='a' && line[i]<='z') || (line[i]>='0' && line[i] <='9') )
					{
						tmp[j]=line[i];
					}
					else
					{
						break;
					}

				}

				Node *node_tmp=HTBsearch(op_table,(const char*)tmp);
				// 해시 값이 없다면, 심볼로 판단
				if(node_tmp == NULL)
				{
					//printf("%s 심볼이 존재 하지 않음. 값 삽입\n",tmp);

					// 해시 값이 없다면, 심볼로 판단해서 갑 삽입
					node_tmp=HTBsearch(sym_table,(const char*)tmp);
					if(node_tmp==NULL)
					{
						HTBadd(sym_table,tmp,_IDENTIFIER);
						node_tmp=HTBsearch(sym_table,(const char*)tmp);
					}
					fprintf(sym,"%s,%d\n",node_tmp->key,node_tmp->value);

				}
				// 그외 나머지는 명령어로 판단
				else
				{
					// 키워드는 값이 1~33까지임.
					if(node_tmp->value>=_ASM && node_tmp->value<=_ENUM)
					{
						fprintf(op,"%s,%d\n",node_tmp->key,node_tmp->value);
					}
					// 연산자중 문자로 표시하는 것
					// sizeof , _Alignof
					if(node_tmp->value==_SIZE_OF || node_tmp->value==_ALIGNO_OF)
					{
						fprintf(op,"%s,%d\n",node_tmp->key,node_tmp->value);
					}
				}
			}
			// 숫자 판별 조건문
			else if( line[i]>='0' && line[i]<='9')
			{
				j=0; memset(tmp,0,sizeof(tmp));

				tmp[j]=line[i];

				// 다음에 오는 문자가 숫자인지 판별하는 반복문
				// 만약 다음 숫자가 숫자가 아니면 빠져나옴
				while(1)
				{
					i++;j++;
					if( line[i]>='0' && line[i]<='9')
						tmp[j]=line[i];
					else
					{	
						break;
					}
				}
				Node *node_tmp=HTBsearch(op_table,(const char*)tmp);
				if(node_tmp == NULL)
				{
					//printf("%s 심볼이 존재 하지 않음. 값 삽입\n",tmp);

					// 해시 값이 없다면, 심볼로 판단해서 갑 삽입
					node_tmp=HTBsearch(sym_table,(const char*)tmp);
					if(node_tmp==NULL)
					{	
						HTBadd(sym_table,tmp,_DIGIT);
						node_tmp=HTBsearch(sym_table,(const char*)tmp);
					}
					fprintf(sym,"%s,%d\n",node_tmp->key,node_tmp->value);
				}
			}
			// 전처리 판별 조건문
			else if(line[i]=='#')
			{
				j=0; memset(tmp,0,sizeof(tmp)); i++;

				// 다음에 오는 문자가 include 인지 define 인지 판별하는 반복문
				// 만약에 이러한 문자가 아니면 빠져나옴
				while(1)
				{
					if( (line[i]>='A' && line[i]<='Z') || (line[i]=='_') || (line[i]>='a' && line[i]<='z') || (line[i]>='0' && line[i] <='9') )
					{
						tmp[j]=line[i];
					}
					else
					{
						break;
					}
					j++;i++;
				}

				// 다음에 오는 문자가 include 로 판단
				if(HTBStrCmp(tmp,ClangEtc[_INCLUDE-_SHARP])==0)
				{

					j=0; memset(tmp,0,sizeof(tmp)); i++;
					while(1)
					{
						i++;
						// 공백 문자 패스
						if(line[i]==' ')
						{
							continue;
						}
						// 헤더 파일 이름의 시작
						else if(line[i]=='<')
						{
							continue;
						}
						// 헤더 파일 이름의 끝
						else if(line[i]=='>')
						{
							break;
						}
						tmp[j]=line[i];
						j++;
					}
					
					Node *node_tmp=HTBsearch(sym_table,(const char*)tmp);
					// 심볼 테이블에 값이 없으면, 해시 값 넣기
					if(node_tmp==NULL)
					{
						HTBadd(sym_table,tmp,_HEADER_FILE);
						node_tmp=HTBsearch(sym_table,(const char*)tmp);
					}
					fprintf(sym,"%s,%d\n",node_tmp->key,node_tmp->value);
				}
			}
			// 연산자 판별 조건
			else
			{
				j=0; memset(tmp,0,sizeof(tmp));

				tmp[j]=line[i];
				Node *node_tmp=HTBsearch(op_table,(const char*)tmp);

				// 연산자는 예약어 이므로.
				// 없으면 공백으로 판단.
				if(node_tmp==NULL)
				{
					i++;
					continue;
				}

				//printf("{%s, %d}\n",node_tmp->key,node_tmp->value);

				// 다음에 오는 문자가 연산자인지 판별하는 반복문
				// 연산자가 아니라면 빠져나옴
				while(1)
				{
					i++;j++;
					tmp[j]=line[i];
					node_tmp=HTBsearch(op_table,(const char*)tmp);
					// 연산자는 예약어 이므로
					// 없으면 그 전까지를 연산자로 판단
					if(node_tmp==NULL)
					{
						tmp[j]='\0';
						break;
					}
				}
				node_tmp=HTBsearch(op_table,(const char*)tmp);
				if(node_tmp==NULL)
				{
					// 연산자는 예약어 이기 때문에
					// 비어있을 수가 없음.
				}
				else
				{
					//node_tmp=HTBsearch(op_table,(const char*)tmp);
					fprintf(op,"%s,%d\n",node_tmp->key,node_tmp->value);
				}
			}
		}
	}
	fclose(fp);
	fclose(op);
	fclose(sym);
	return true;	
}

void printOpTableWithFile()
{
	FILE *op_fp=NULL;
	char line[1024]={0,};

	op_fp=fopen("operation.csv","r");
	if(!op_fp)
	{
		perror("operation.csv open failed\n");
		return ;
	}

	printf("****\top table\t****\n\n");
	{
		while(fgets(line,sizeof(line)-1,op_fp)!=0)
		{
			printf("%s\n",line);
		}
	}
}

void printSymbolTableWithFile()
{
	FILE *sym_fp=NULL;
	char line[1024]={0,};

	sym_fp=fopen("symbol.csv","r");
	if(!sym_fp)
	{
		perror("symbol.csv open failed\n");
		return ;
	}

	printf("****\tsymbol table\t****\n\n");
	{
		while(fgets(line,sizeof(line)-1,sym_fp)!=0)
		{
			printf("%s\n",line);
		}
	}

}

void destroyFile()
{
	unlink("symbol.csv");
	unlink("operation.csv");
}

void print()
{
	printOpTableWithFile();
	printSymbolTableWithFile();
	destroyFile();
}
