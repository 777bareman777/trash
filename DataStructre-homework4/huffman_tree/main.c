#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <huffman_tree.h>

int main(int argc, char *argv[])
{
	pHuffmanTree root=NULL;
	root=HT_createHuffmanTree();
	printf("huffman_tree\n");
 	Print(root);


	printf("\n\n");
	char *input=fileInput("string.txt");
	char str[1024]={0,};
	char encoding[1024]={0,};
	char *code[26]={0,};

	HT_createTable(root,str,0,code);
	int i=0;
	while(input[i]!='\0')
	{
		strcat(encoding,code[input[i]-'a']);
		i++;
	}

	for(i=0;i<'z'-'a';i++)
	{
		if(code[i]!=NULL)
			printf("%c : %s\n",'a'+i,code[i]);
	}
	HT_decode(root,encoding);
	free(input);
	
	
	return 0;
}
