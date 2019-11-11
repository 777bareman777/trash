#include <scanner.h>
#include <unistd.h>

extern Node *tb[MAX_TABLE];
extern char *ClangKeyword[];
extern char *ClangOperation[];
extern char *ClangDelimiter[];
extern char *ClangSymbol[];


int main(int argc, char *argv[])
{

	// op table 생성후, 테이블 상태 표시
	init();
//	HTBprint_hash(tb);

	// symbol table 생성후, 테이블 상태 표시
	scanner();
//	HTBprint_hash(tb);

	// 입력된 operation 과 symbol 출력
	print();

	return 0;
}
