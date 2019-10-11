#include "./include/myparsing.h"
#include "./include/myfat32.h"

int fat32_parsing_br(char** argv,struct __fat32* fat)
{
	int fd,len;
	char buf[BUF_SIZE]={0,};

	fd=open(argv[1],O_RDONLY);
	if(fd<0)
	{
		fprintf(stderr,"invaild open() argument -> fat32_parsing\n");
		return FAIL;
	}

	len=read(fd,buf,512);
	if(len!=512)
	{
		fprintf(stderr,"read fail -> fat32_parsing\n");
		close(fd);
		return FAIL;
	}
	for(int i=0;i<len;i++)
		buf[i]&=0xff;

	// boot Record	
	// buf+0
	fat->vbJumpCode[0]=buf[0]; fat->vbJumpCode[1]=buf[1]; fat->vbJumpCode[2]=buf[2];
	strncpy(fat->vcCreatingSystemIdentifier,buf+3,8); // buf+3
	fat->wSectorSize=*(buf+11); // buf+11
	fat->wSectorSize|=*(buf+12)<<8;
	fat->bSectorsPerCluster=*(buf+13); // buf+13
	fat->wReservedSectorCount=*(buf+14); //buf+14
	fat->wReservedSectorCount|=*(buf+15)<<8;
	fat->bNumberOfFATs=*(buf+16); // buf+16
	fat->wNumberOfRootDirectoryEntries=*(buf+17); // buf+17
	fat->wNumberOfRootDirectoryEntries|=*(buf+18)<<8;
	fat->wTotalSectors=*(buf+19); // buf+19
	fat->wTotalSectors|=*(buf+20)<<8;
	fat->bMediumIdentifer=*(buf+21); // buf+21
	fat->wSectorsPerFAT=*(buf+22); // buf+22
	fat->wSectorsPerFAT|=*(buf+23) <<8;
	fat->wSectorsPerTrack=*(buf+24); // buf+24
	fat->wSectorsPerTrack|=*(buf+25)<<8;
	fat->wNumberOfSides=*(buf+26); // buf+26
	fat->wNumberOfSides|=*(buf+27)<<8;
	fat->dwNumberOfHiddenSectors=*(buf+28); // buf+28
	fat->dwNumberOfHiddenSectors|=*(buf+29) <<8;
	fat->dwNumberOfHiddenSectors|=*(buf+30) <<16;
	fat->dwNumberOfHiddenSectors|=*(buf+31) <<24;
	fat->dwTotalSectors=*(buf+32); // buf+32
	fat->dwTotalSectors|=*(buf+33) <<8;
	fat->dwTotalSectors|=*(buf+34) <<16;
	fat->dwTotalSectors|=*(buf+35) <<24;
	fat->dwSectorsPerFAT32=*(buf+36); // buf+36
	fat->dwSectorsPerFAT32|=*(buf+37) <<8;
	fat->dwSectorsPerFAT32|=*(buf+38) <<16;
	fat->dwSectorsPerFAT32|=*(buf+39) <<24;
	fat->wExtensionFlag=*(buf+40); // buf+40
	fat->wExtensionFlag|=*(buf+41) <<8;
	fat->wFSVersion=*(buf+42); // buf+42
	fat->wFSVersion|=*(buf+43) <<8;
	fat->dwRootCluster=*(buf+44); // buf+44
	fat->dwRootCluster|=*(buf+45)<<8;
	fat->dwRootCluster|=*(buf+46)<<16;
	fat->dwRootCluster|=*(buf+47)<<24;
	fat->wFSInfo=*(buf+48); // buf+48
	fat->wFSInfo|=*(buf+49)<<8;
	fat->wBackupBootSector=*(buf+50); // buf+50
	fat->wBackupBootSector|=*(buf+51) <<8;
	for(int i=0;i<12;i++){fat->vbReserved[i]=*(buf+52+i);} // buf+52, always 0
	fat->bPhysicalDiskNumber=*(buf+64); // buf+64
	fat->bReserved=*(buf+65); // buf+65
	fat->bExtendedBootRecordSignature=*(buf+66); // buf+66
	strncpy(fat->vcVolumeIDNumber,buf+67,4); // buf+67
	strncpy(fat->vcVolumeLabel,buf+71,11); // buf+71
	fat->vcVolumeLabel[10]='\0';
	strncpy(fat->vcFileSystemType,buf+82,8); // buf+82
	fat->vcFileSystemType[7]='\0';
	for(int i=0;i<420;i++){fat->vbReservedForSystemUse[i]=*(buf+90+i);} // buf+90
	// buf+510
	if(buf[510]==0x55){
		if(buf[511]==0xffffffaa){
			fat->vbSignatureWord[0]=buf[510];
			fat->vbSignatureWord[1]=buf[511];
		}
		else{
			close(fd);   
			return FAIL;
		}
	}
	else {
		close(fd);
		return FAIL;
	}

	close(fd);
	return SUCCESS;
}
int fat32_parsing_fsinfo(char** argv,struct __fs_info_struct * fat)
{
	// FSINFO
	int fd,len;
	char buf[BUF_SIZE]={0,};

	fd=open(argv[1],O_RDONLY);
	if(fd<0)
	{
		fprintf(stderr,"invaild open() argument -> fat32_parsing\n");
	    close(fd);
		return FAIL;
	}
	lseek(fd,0x200,SEEK_SET);
	len=read(fd,buf,0x200);
	if(len!=0x200){
		fprintf(stderr,"read fail -> fat32_parsing\n");
		close(fd);
		return FAIL;
	}
	for(int i=0;i<0x200;i++)
		buf[i]&=0xff;
	// buf+0
	for(int i=0;i<4;i++) {fat->vbLeadSignature[i]=*(buf+i);}
	// buf+4
	for(int i=0;i<480;i++) {fat->vbReserved1[i]=*(buf+4+i);}
	// buf+484
	for(int i=0;i<4;i++) {fat->vbStructureSignature[i]=*(buf+484+i);}
	// buf+488
	fat->dwFreeClusterCount=(*(buf+488)&0xff);
	fat->dwFreeClusterCount|=(*(buf+489)&0xff) <<8;
	fat->dwFreeClusterCount|=(*(buf+490)&0xff) <<16;
	fat->dwFreeClusterCount|=(*(buf+491)&0xff) <<24;
	// buf+492
	fat->dwNextFreeCluster=*(buf+492);
	fat->dwNextFreeCluster|=*(buf+493) <<8;
	fat->dwNextFreeCluster|=*(buf+494) <<16;
	fat->dwNextFreeCluster|=*(buf+495) <<24;
	// buf+496
	for(int i=0;i<12;i++) {fat->vbReserved2[i]=*(buf+496+i);}
	// buf+508
	if(buf[510]==0x55){
		if(buf[511]==0xffffffaa){
			for(int i=0;i<4;i++) {fat->vbTrailSignature[i]=*(buf+508+i);}
		}
		else {
			close(fd);
			return FAIL;
		}

	}
	else {
		close(fd);
		return FAIL;
	}

	close(fd);
	return SUCCESS;
}

void fat32_print_br(const struct __fat32 fat)
{
	printf("************************************\n");
	printf("          FAT32 Boot Record \n\n");
	printf("Jump Boot Code: 0x");
	for(int i=2;i>=0;i--) {printf("%x",fat.vbJumpCode[i]);} printf("\n");
	printf("OEM Name: %s\n",fat.vcCreatingSystemIdentifier);
	printf("Byte Per Sector: 0x%04x\n",fat.wSectorSize);
	printf("Sector Per Cluster: 0x%02x\n",fat.bSectorsPerCluster);
	printf("Reserved Sector Count: 0x%04x\n",fat.wReservedSectorCount);
	printf("Number of FATs: 0x%02x\n",fat.bNumberOfFATs);
	printf("Number of Root Directory Entries: 0x%04x\n",fat.wNumberOfRootDirectoryEntries);
	printf("Total Sectors 16: 0x%04x\n",fat.wTotalSectors);
	printf("Medium Identifer: 0x%02x\n",fat.bMediumIdentifer);
	printf("Sectors Per FAT 16: 0x%04x\n",fat.wSectorsPerFAT);
	printf("Sectors Per Track: 0x%04x\n",fat.wSectorsPerTrack);
	printf("Number of Sides: 0x%04x\n",fat.wNumberOfSides);
	printf("Number Of Hidden Sectors: 0x%08lx\n",fat.dwNumberOfHiddenSectors);
	printf("ToTal Sectors: 0x%08lx\n",fat.dwTotalSectors);
	printf("Sectors Per FAT32: 0x%08lx\n",fat.dwSectorsPerFAT32);
	printf("Extension Flag: 0x%04x\n",fat.wExtensionFlag);
	printf("File System Version: 0x%04x\n",fat.wFSVersion);
	printf("Root Directory Cluster: 0x%08lx\n",fat.dwRootCluster);
	printf("File System Info: 0x%04x\n",fat.wFSInfo);
	printf("Boot Record Backup Secotr: 0x%04x\n",fat.wBackupBootSector);
	printf("Reserved: 0x");
	for(int i=11;i>=0;i--){printf("%x",fat.vbReserved[i]);} printf("\n");
	printf("Physical Disk Number: 0x%02x\n",fat.bPhysicalDiskNumber);
	printf("Reserved 1: 0x%02x\n",fat.bReserved);
	printf("Boot Record Signature: 0x%02x\n",fat.bExtendedBootRecordSignature);
	printf("Volume ID Number: 0x");
	for(int i=3;i>=0;i--){printf("%02x",fat.vcVolumeIDNumber[i]&0xff);} printf("\n");
	printf("Volume Label: %s\n",fat.vcVolumeLabel);
	printf("File System Type: %s\n",fat.vcFileSystemType);
	printf("Signature Word: 0x%x%x\n",fat.vbSignatureWord[1],fat.vbSignatureWord[0]);
	printf("************************************\n");
}

void fat32_print_fsinfo(const struct __fs_info_struct fat)
{
	printf("************************************\n");
	printf("          FAT32 FSINFO\n\n");
	printf("Lead Signature: 0x");
	for(int i=3;i>=0;i--) {printf("%02x",fat.vbLeadSignature[i]);} printf("\n");
	printf("Reserved 1: 0x");
	for(int i=479; i>=0;i--) {printf("%02x",fat.vbReserved1[i]);} printf("\n");
	printf("Structre Signature: 0x");
	for(int i=3;i>=0;i--) {printf("%02x",fat.vbStructureSignature[i]);} printf("\n");
	printf("Free Cluster Count: 0x%08lx\n",fat.dwFreeClusterCount);
	printf("Next Free Cluster: 0x%08lx\n",fat.dwNextFreeCluster);
	printf("vbReserved2: 0x");
	for(int i=11;i>=0;i--) {printf("%02x",fat.vbReserved2[i]);} printf("\n");
	printf("Trail Signature: 0x");
	for(int i=3;i>=0;i--) 	{printf("%02x",fat.vbTrailSignature[i]);} printf("\n");
	printf("************************************\n");

}

int fat32_searching_fat(char ** argv,const struct __fat32 fat)
{
	int fd,count=0;
	DWORD fat_len=(fat.wReservedSectorCount+fat.dwSectorsPerFAT32)*fat.wSectorSize;
	BYTE buf[4];
	DWORD fat_area=fat.wReservedSectorCount*fat.wSectorSize;

	fd=open(argv[1],O_RDONLY);
	if(fd<0){
		fprintf(stderr,"open fail -> fat32_searching_fat\n");
		return FAIL;
	}
	lseek(fd,fat_area,SEEK_SET);

	printf("fat_len : %08x\n",fat_len);
	printf("fat_area : %08x\n",fat_area);

	for(int i=fat_area;i<=fat_len;i+=4){
		read(fd,buf,4);
		printf("0x");
		for(int i=3;i>=0;i--)
			printf("%02x",buf[i]);
		printf("  "); count++;
		if(count==4) {
			count=0;
			printf("\n");
		}
	}

	return 	SUCCESS;
}

