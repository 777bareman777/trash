#ifndef __MYPARSING_H__
#define __MYPARSING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 1024

// FileSystem numbering
#define FAT32 1

#define FAIL -1
#define SUCCESS 0

// data type
#define BYTE unsigned char
#define BOOL int
#define WORD unsigned short
#define DWORD unsigned long
#define UINT unsigned int

int filesystem_parsing(char **);

#endif
