#ifndef _PARSE_H_
#define _PARSE_H_

#include <windows.h>
#include <TCHAR.h>
#include <stdio.h>

#define WIDTH 50

BOOLEAN FileOpen(LPCSTR FileName);
VOID Clean();
BOOLEAN Parse();

DWORD ParseDosHdr(DWORD offset);
DWORD ParseNTHdr(DWORD offset);
DWORD ParseFileHdr(DWORD offset);
DWORD ParseOptionalHdr(DWORD offset);
DWORD ParseDataDir(DWORD offset);
DWORD ParseSectionHdr(DWORD offset, INT secCnt);


#endif