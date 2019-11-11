#include <scanner.h>
#include <unistd.h>

extern Node *op_table[MAX_TABLE];
extern Node *sym_table[MAX_TABLE];
extern char *ClangKeyword[];
extern char *ClangOperation[];
extern char *ClangDelimiter[];
extern char *ClangSymbol[];


int main(int argc, char *argv[])
{

	// op table 생성
	init();

	// symbol table 생성
	scanner();


	// 해시 테이블에 저장된 녀석들 모두 출력
	printf("****\top table\t****\n\n");
	HTBprint_hash(op_table);
	printf("****\tsymbol table\t****\n\n");	
	HTBprint_hash(sym_table);

	// op table + symobl table 출력
	// .csv 파일에 입력을 시키고, 그것을 읽어들여서 출력
	print();


	return 0;
}
