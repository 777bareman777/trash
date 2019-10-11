#include "./include/myparsing.h"
#include "./include/myfat32.h"

int main(int argc, char** argv)
{
	int check;
	check=filesystem_parsing(argv);
	switch(check)
	{
		case FAT32:{
			fat32 fat_br;
			fs_info_struct fat_fsinfo;		
			if(fat32_parsing_br(argv,&fat_br)==SUCCESS){
				if(fat32_parsing_fsinfo(argv,&fat_fsinfo)==SUCCESS){
					printf("parsing SUCCESS\n");
				}
				fat32_print_br(fat_br);
				fat32_print_fsinfo(fat_fsinfo);
			}
			else{
				fprintf(stderr,"parsing FAIL\n");
				return FAIL;
			}
			if(fat32_searching_fat(argv,fat_br)==SUCCESS){
				printf("sarching\n");
			}
			else{
				fprintf(stderr,"searching FAIL\n");
				return FAIL;
			}
			break;
				   }
		default:
			return FAIL;
	}



	return SUCCESS;
}


