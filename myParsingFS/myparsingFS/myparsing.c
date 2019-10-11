#include "./include/myparsing.h"
#include "./include/myfat32.h"

#define magic_number 8

int filesystem_parsing(char ** argv)
{
	int fd;
	char buf[magic_number+1]={0,};

	fd=open(argv[1],O_RDONLY);
	if(fd<0){
		fprintf(stderr,"invalid open() argument\n");
		fprintf(stderr,"program exit\n");
		return FAIL;
	}
	lseek(fd,0x50,SEEK_SET);
	read(fd,buf,magic_number);
	buf[magic_number+1]='\0';
	close(fd);

	// print file system
	/* 
	for(int i=0;i<8;i++)
		printf("%02x ",buf[i]);
	printf("\n%s\n",buf);
	*/

	if(strcmp(buf,"  FAT32")){
		printf("IT is FAT32 file system\n");
		return FAT32;
	}
	else{
		printf("I don't know this file system\n");
		return FAIL;
	}
}
