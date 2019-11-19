#include <stdio.h>
#include <infix_to_binary_tree.h>
#include <huffman_tree.h>

int main(int argc, char *argv[])
{

	while(1)
	{
		int i;
		printf("1번 산술식 이진트리, 2번 호프만 코딩, 3번 프로그램 종료: ");
		scanf("%d",&i);

		switch(i)
		{
			case 1:
				test1();
				break;
			case 2:
				test2();
				break;
			case 3:
				return 0;
		}
	}
}
