#include <stdio.h>
#include <infix_to_binary_tree.h>

int main(int argc, char *argv[])
{

	pTree root=NULL;
	root=createInfixToBinaryTree();

	printf("infix 방식\n");
	BT_infixPrint(root);
	printf("\n\n");

	printf("postfix 방식\n");	
	BT_postfixPrint(root);
	printf("\n\n");

	printf("prefix 방식\n");
	BT_prefixPrint(root);
	printf("\n\n");

	printf("level 방식\n");
	BT_levelPrint(root);
	printf("\n\n");

	return 0;
}
