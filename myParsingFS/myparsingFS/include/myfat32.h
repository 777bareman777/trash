#ifndef __MYFAT32_H__
#define __MYFAT32_H__

typedef struct __fat32{
	BYTE vbJumpCode[3];
	char vcCreatingSystemIdentifier[8];
	WORD wSectorSize;
	BYTE bSectorsPerCluster;
	WORD wReservedSectorCount;
	BYTE bNumberOfFATs;
	WORD wNumberOfRootDirectoryEntries;
	WORD wTotalSectors;
	BYTE bMediumIdentifer;
	WORD wSectorsPerFAT;
	WORD wSectorsPerTrack;
	WORD wNumberOfSides;
	DWORD dwNumberOfHiddenSectors;
	DWORD dwTotalSectors;
	DWORD dwSectorsPerFAT32;
	WORD wExtensionFlag;
	WORD wFSVersion;
	DWORD dwRootCluster;
	WORD wFSInfo;
	WORD wBackupBootSector;
	BYTE vbReserved[12];
	BYTE bPhysicalDiskNumber;
	BYTE bReserved;
	BYTE bExtendedBootRecordSignature;
	char vcVolumeIDNumber[4];
	char vcVolumeLabel[11];
	char vcFileSystemType[8];
	BYTE vbReservedForSystemUse[420];
	BYTE vbSignatureWord[2];
} fat32, *p_fat32;

typedef struct __fs_info_struct{
	BYTE vbLeadSignature[4];
	BYTE vbReserved1[480];
	BYTE vbStructureSignature[4];
	DWORD dwFreeClusterCount;
	DWORD dwNextFreeCluster;
	BYTE vbReserved2[12];
	BYTE vbTrailSignature[4];
} fs_info_struct, *p_fs_info_struct;

typedef struct __directory_sturct{
	char vcNameAndExtension[11];
	BYTE bAttribute;
	BYTE bReservedForNT;
	BYTE bCreatedTimeTenth;
	WORD wCreatedTime;
	WORD wCreatedDate;
	WORD wLastAccessaDate;
	WORD wStartingaClusterNumberHigh;
	WORD wTimeRecorded;
	WORD wDateRecorded;
	WORD wStartingClusterNumberLow;
	DWORD dwFileLength;
} 	directory_struct, *p_directory_struct;

typedef struct __long_file_name_struct{
	BYTE border;
	BYTE vcName1[10];
	BYTE bAttribute;
	BYTE bType;
	BYTE bChecksum;
	BYTE vcName2[12];
	WORD WFirstClusterLow;
} long_file_name_struct, *p_long_file_name;


int fat32_parsing_br(char** ,struct __fat32 * );
int fat32_parsing_fsinfo(char** ,struct __fs_info_struct *);
void fat32_print_br(const struct __fat32);
void fat32_print_fsinfo(const struct __fs_info_struct);

int fat32_searching_fat(char **,const struct __fat32);

#endif
