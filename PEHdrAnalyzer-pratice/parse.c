#include "parse.h"

CHAR m_szPeName[128];
HANDLE	m_hImgFile;
HANDLE	m_hImgMap;
LPBYTE	m_pImgView;


BOOLEAN FileOpen(LPCSTR FileName)
{
    strncpy(m_szPeName,FileName,sizeof(m_szPeName));

    m_hImgFile=CreateFile(m_szPeName,GENERIC_READ,FILE_SHARE_READ,
                            NULL,OPEN_EXISTING,0,NULL);
    if(m_hImgFile==INVALID_HANDLE_VALUE)
    {
        fprintf(stderr,"%s open failed\n",m_szPeName);
        return FALSE;
    }

    m_hImgMap=CreateFileMapping(m_hImgFile,NULL,
                                PAGE_READONLY,0,0,NULL);
    if(!m_hImgMap)
    {
        fprintf(stderr,"%s map failed\n",m_szPeName);
        return FALSE;
    }

    m_pImgView=(LPBYTE)MapViewOfFile(m_hImgMap, FILE_MAP_READ,0,0,0);
    if(!m_pImgView)
    {
        fprintf(stderr,"%s view failed\n",m_szPeName);
        return FALSE;
    }

    return TRUE;
}

VOID Clean()
{
    if(m_pImgView)
    {
        UnmapViewOfFile(m_pImgView);
        m_pImgView=NULL;
    }
    if(m_hImgMap)
    {
        CloseHandle(m_hImgMap);
        m_hImgMap=NULL;
    }
    if(m_hImgFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_hImgFile);
        m_hImgFile=INVALID_HANDLE_VALUE;
    }

    memset(m_szPeName,0,sizeof(m_szPeName));
}

BOOLEAN Parse()
{
    DWORD offset=0;

    PIMAGE_DOS_HEADER pIDH=(PIMAGE_DOS_HEADER)m_pImgView;
    if(pIDH->e_magic != IMAGE_DOS_SIGNATURE)
    {
        fprintf(stderr,"It is not PE file format\n");
        return FALSE;
    }

    TCHAR buf[128]={0,};

    offset=ParseDosHdr(offset);
    

    offset=pIDH->e_lfanew;
    PIMAGE_NT_HEADERS pINH=(PIMAGE_NT_HEADERS)(m_pImgView+offset);
    if(pINH->Signature != IMAGE_NT_SIGNATURE)
    {
        fprintf(stderr,"It is not PE file format\n");
        return FALSE;
    }


    offset=ParseNTHdr(offset);
    offset=ParseSectionHdr(offset,(INT)pINH->FileHeader.NumberOfSections);

    return TRUE;
}

DWORD ParseDosHdr(DWORD offset)
{
	LPCSTR pcszFld[] =
	{
		"e_magic   ", "e_cblp    ", "e_cp      ", "e_crlc    ", "e_cparhdr ",
		"e_minalloc", "e_maxalloc", "e_ss      ", "e_sp      ", "e_csum    ",
		"e_ip      ", "e_cs      ", "e_lfarlc  ", "e_ovno    ", "e_res[0]  ",
		"e_res[1]  ", "e_res[2]  ", "e_res[3]  ", "e_oemid   ", "e_oeminfo ", 
		"e_res2[0] ", "e_res2[1] ", "e_res2[2] ", "e_res2[3] ", "e_res2[4] ",
		"e_res2[5] ", "e_res2[6] ", "e_res2[7] ", "e_res2[8] ", "e_res2[9] ",
		"e_lfanew  "
	};
	INT anSize[] = 
	{
		sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), 
		sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), 
		sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
		sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
		sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
		sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
		sizeof(LONG)
	};

    LPCSTR Description[] =
    {
        "Signature                        ", "Bytes on Last Page of File       ", "Pages in File                    ", "Relocations                      ",
        "Size of Header in Paragraphs     ", "Minimum Extra Paragraphs         ", "Maximum Extra Paragraphs         ", "Initial (relative) SS            ",
        "Initial SP                       ", "Checksum                         ", "Initial SP                       ", "Initial (relative) CS value      ", 
        "File address of relocation table ", "Overlay number                   ", "Reserved words                   ", "Reserved words                   ",
        "Reserved words                   ", "Reserved words                   ", "OEM identifier                   ", "OEM information                  ", 
        "Reserved words                   ", "Reserved words                   ", "Reserved words                   ", "Reserved words                   ",
        "Reserved words                   ", "Reserved words                   ", "Reserved words                   ", "Reserved words                   ",
        "Reserved words                   ", "Reserved words                   ", "File address of new exe header   "
    };

    BYTE buf[128]={0,};
    LPBYTE pIter=m_pImgView + offset;
    INT cnt=sizeof(pcszFld)/sizeof(LPCSTR);
    sprintf(buf,"[%08X] IMAGE_DOS_HEADER",offset);
    fprintf(stdout,"%s\n",buf);
    for(INT i=0;i<cnt;i++)
    {
        memset(buf,0,sizeof(buf));
        if(i==cnt-1)
        {
            sprintf(buf,"[%08X]\t%s : 0x%08X %*s", offset,pcszFld[i],*((LPLONG)pIter), WIDTH-4, Description[i] );
        }
        else
        {
            sprintf(buf,"[%08X]\t%s : 0x%04X %*s", offset,pcszFld[i],*((LPWORD)pIter), WIDTH, Description[i]);
        }

        printf("%s\n",buf);
        pIter+=anSize[i];
        offset+=anSize[i];
    }

    printf("\n\n");
    return offset;
}

DWORD ParseNTHdr(DWORD offset)
{
    BYTE buf[128]={0,};
    LPBYTE pIter=m_pImgView + offset;

    sprintf(buf,"[%08X] IMAGE_NT_HEADERS",offset);
    fprintf(stdout,"%s\n",buf);

    memset(buf,0,sizeof(buf));
    sprintf(buf,"[%08X]\tSignature %08X",offset,*((LPDWORD)pIter));
    printf("%s\n",buf);
    offset+=sizeof(DWORD);
    
    printf("\n\n");



    offset=ParseFileHdr(offset);
    
    printf("\n\n");



    offset=ParseOptionalHdr(offset);
    
    printf("\n\n");

    return offset;
}

DWORD ParseFileHdr(DWORD offset)
{
    LPCSTR pcszFld[] =
	{
		"Machine                ", "NumberOfSections       ", "TimeDateStamp          ", 
		"PointerToSymbolTable   ", "NumberOfSymbols        ", "SizeOfOptionalHeader   ", 
		"Characteristics        " 
	};

	INT anSize[] = 
	{
		sizeof(WORD ), sizeof(WORD ), sizeof(DWORD), sizeof(DWORD),
		sizeof(DWORD), sizeof(WORD ), sizeof(WORD )
	};

    BYTE buf[1024]={0,};
    LPBYTE pIter=m_pImgView+offset;
    INT cnt=sizeof(pcszFld)/sizeof(LPCSTR);

    sprintf(buf,"[%08X] IMAGE_FILE_HEADER",offset);
    printf("%s\n",buf);
    for(INT i=0; i<cnt; i++)
    {
        memset(buf,0,sizeof(buf));
        if(anSize[i]==sizeof(WORD))
        {
            sprintf(buf,"[%08X]\t%s : 0x%04X", offset,pcszFld[i],*((LPWORD)pIter) );
            if(i==0)
            {
                if(*((LPWORD)pIter)==IMAGE_FILE_MACHINE_I386)
                {
                    strncat(buf,"\tIMAGE_FILE_MACHINE_I386",strlen("\tIMAGE_FILE_MACHINE_I386"));
                }
                else if(*((LPWORD)pIter)==IMAGE_FILE_MACHINE_IA64)
                {
                    strncat(buf,"\tIMAGE_FILE_MACHINE_IA64",strlen("\tIMAGE_FILE_MACHINE_IA64"));
                }
            }
            if(i==cnt-1)
            {
                
                WORD temp=*((LPWORD)pIter);
                BYTE a[128]={0,};
                if( (temp & (1<<0)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_RELOCS_STRIPPED,"IMAGE_FILE_RELOCS_STRIPPED");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (2<<0)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_EXECUTABLE_IMAGE,"IMAGE_FILE_EXECUTABLE_IMAGE");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (4<<0)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_LINE_NUMS_STRIPPED,"IMAGE_FILE_LINE_NUMS_STRIPPED");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (8<<0)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_LOCAL_SYMS_STRIPPED,"IMAGE_FILE_LOCAL_SYMS_STRIPPED");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (1<<8)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_AGGRESIVE_WS_TRIM,"IMAGE_FILE_AGGRESIVE_WS_TRIM");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (2<<8)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_LARGE_ADDRESS_AWARE,"IMAGE_FILE_LARGE_ADDRESS_AWARE");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (8<<8)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_BYTES_REVERSED_LO,"IMAGE_FILE_BYTES_REVERSED_LO");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (1<<16)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_32BIT_MACHINE,"IMAGE_FILE_32BIT_MACHINE");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (2<<16)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_DEBUG_STRIPPED,"IMAGE_FILE_DEBUG_STRIPPED");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (4<<16)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP,"IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (8<<16)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_NET_RUN_FROM_SWAP,"IMAGE_FILE_NET_RUN_FROM_SWAP");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (1<<24)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_SYSTEM,"IMAGE_FILE_SYSTEM");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (2<<24)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_DLL,"IMAGE_FILE_DLL");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (4<<24)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_UP_SYSTEM_ONLY,"IMAGE_FILE_UP_SYSTEM_ONLY");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
                if( (temp & (8<<24)) != 0)
                {
                    sprintf(a,"\n%*s %04x \t\t%s",WIDTH-9,"",IMAGE_FILE_BYTES_REVERSED_HI,"IMAGE_FILE_BYTES_REVERSED_HI");
                    strncat(buf,a,strlen(a));
                    memset(a,0,sizeof(a));
                }
            }
            printf("%s\n",buf);
        }
        else
        {
            sprintf(buf,"[%08X]\t%s : 0x%08X", offset,pcszFld[i],*((LPDWORD)pIter) );
            // TimeDateStamp
            if(i==2)
            {
                SYSTEMTIME st;
                FILETIME ft;
                ULARGE_INTEGER li;

                memset(&st,0x00,sizeof(st));
                st.wYear=1970, st.wMonth=1, st.wDay=1, st.wHour=9;
                SystemTimeToFileTime(&st,&ft);
                li.HighPart=ft.dwHighDateTime;
                li.LowPart=ft.dwLowDateTime;
                li.QuadPart += ((unsigned __int64)(*((LPDWORD)pIter)) * 10000000L);
                ft.dwHighDateTime=li.HighPart;
                ft.dwLowDateTime=li.LowPart;
                FileTimeToSystemTime(&ft,&st);

                BYTE time[128]={0,};
                sprintf(time,"\t%04d/%02d/%02d-%02d:%02d:%02d",
                        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
                strncat(buf,time,sizeof(time));
            }
            printf("%s\n",buf);
        }

        pIter+=anSize[i];
        offset+=anSize[i];
    }

    return offset;
}

DWORD ParseOptionalHdr(DWORD offset)
{
    LPCSTR pcszFld[] =
	{
		"Magic                  ", "LinkerVersion          ", "SizeOfCode             ", 
		"SizeOfInitializedData  ", "SizeOfUninitializedData", "AddressOfEntryPoint    ", 
		"BaseOfCode             ", "BaseOfData             ", "ImageBase              ", 
		"SectionAlignment       ", "FileAlignment          ", "OperatingSystemVersion ", 
		"ImageVersion           ", "SubsystemVersion       ", "Win32VersionValue      ", 
		"SizeOfImage            ", "SizeOfHeaders          ", "CheckSum               ", 
		"Subsystem              ", "DllCharacteristics     ", "SizeOfStackReserve     ", 
		"SizeOfStackCommit      ", "SizeOfHeapReserve      ", "SizeOfHeapCommit       ", 
		"LoaderFlags            ", "NumberOfRvaAndSizes    "
	};

	INT anSize[] = 
	{
		sizeof(WORD) , sizeof(WORD) , sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), 
		sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), 
		sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), 
		sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(WORD ), sizeof(WORD ), 
		sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), 
		sizeof(DWORD)
	};

    BYTE buf[128]={0,};
    LPBYTE pIter=m_pImgView+offset;
    INT cnt=sizeof(pcszFld)/sizeof(LPCSTR);

    sprintf(buf,"[%08X] IMAGE_OPTIONAL_HEADER",offset);
    printf("%s\n",buf);
    for(INT i=0; i<cnt;i++)
    {
        memset(buf,0,sizeof(buf));
        if(i==1)
        {
            sprintf(buf,"[%08X] %s 0x%02X, 0x%02X(%d.%d)",
                    offset, pcszFld[i], *pIter, *(pIter+1),
                    *pIter, *(pIter+1));
        }
        else
        {
            if(i==11 || i==12 || i==13)
            {
                sprintf(buf,"[%08X] %s 0x%04X, 0x%04X(%d.%d)",
                    offset, pcszFld[i], *((LPWORD)pIter),*((LPWORD)pIter+1),
                    *((LPWORD)pIter),*((LPWORD)pIter+1));
            }
            else
            {
                if(anSize[i]==sizeof(WORD))
                {
                    sprintf(buf,"[%08X] %s 0x%04X",
                        offset,pcszFld[i],*((LPWORD)pIter));
                }
                else
                {
                    sprintf(buf,"[%08X] %s 0x%08X",
                        offset,pcszFld[i],*((LPDWORD)pIter));
                }
            }
        }
        printf("%s\n",buf);
        pIter+=anSize[i];
        offset+=anSize[i];
    }
    printf("\n\n");


    offset=ParseDataDir(offset);

    return offset;
}

DWORD ParseDataDir(DWORD offset)
{
    LPCSTR pcszFld[] =
	{
		"IMAGE_DIRECTORY_ENTRY_EXPORT        ",  //  0, Export Directory
		"IMAGE_DIRECTORY_ENTRY_IMPORT        ",  //  1, Import Directory
		"IMAGE_DIRECTORY_ENTRY_RESOURCE      ",  //  2, Resource Directory
		"IMAGE_DIRECTORY_ENTRY_EXCEPTION     ",  //  3, Exception Directory
		"IMAGE_DIRECTORY_ENTRY_SECURITY      ",  //  4, Security Directory
		"IMAGE_DIRECTORY_ENTRY_BASERELOC     ",  //  5, Base Relocation Table
		"IMAGE_DIRECTORY_ENTRY_DEBUG         ",  //  6, Debug Directory
		"IMAGE_DIRECTORY_ENTRY_ARCHITECTURE  ",  //  7, Architecture Specific Data
		"IMAGE_DIRECTORY_ENTRY_GLOBALPTR     ",  //  8, RVA of GP
		"IMAGE_DIRECTORY_ENTRY_TLS           ",  //  9, TLS Directory
		"IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   ",  // 10, Load Configuration Directory
		"IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  ",  // 11, Bound Import Directory in headers
		"IMAGE_DIRECTORY_ENTRY_IAT           ",  // 12, Import Address Table
		"IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  ",	 // 13, Delay Load Import Descriptors
		"IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR",  // 14, COM Runtime descriptor
		"IMAGE_DIRECTORY_ENTRY_NULL          "   // 15, NULL
	};

    BYTE buf[128]={0,};
    LPBYTE pIter=m_pImgView+offset;
    sprintf(buf,"[%08X] IMAGE_DATA_DIRECTORY",offset);
    printf("%s\n",buf);
    for(INT i=0;i<IMAGE_NUMBEROF_DIRECTORY_ENTRIES;i++)
    {
        memset(buf,0,sizeof(buf));
        PIMAGE_DATA_DIRECTORY pIDD=(PIMAGE_DATA_DIRECTORY)pIter;
        BOOLEAN bIsNULL=!(pIDD->Size || pIDD->VirtualAddress);

        printf("[%08X] %s->[%c]\n",offset,pcszFld[i], bIsNULL ? 'X': 'O');
        sprintf(buf,"[%08X] VirtualAddress\t0x%08X\n[%08X] Size            \t0x%08X",
                     offset,pIDD->VirtualAddress,
                     offset+sizeof(pIDD->VirtualAddress), pIDD->Size);
        printf("%s\n",buf);

        offset+=sizeof(IMAGE_DATA_DIRECTORY);
        pIter+=sizeof(IMAGE_DATA_DIRECTORY);
    }


    return offset;
}

DWORD ParseSectionHdr(DWORD offset, INT secCnt)
{
  	LPCSTR pcszFld[] =
	{
		"VirtualSize            ", "VirtualAddress         ", "SizeOfRawData          ", 
		"PointerToRawData       ", "PointerToRelocations   ", "PointerToLinenumbers   ", 
		"NumberOfRelocations    ", "NumberOfLinenumbers    ", "Characteristics        "
	};

	INT anSize[] = 
	{
		sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), 
		sizeof(DWORD), sizeof(DWORD), sizeof(WORD ), sizeof(WORD ), sizeof(DWORD)
	};  

    // secCnt 만큼 루프를 돌면서 IMAGE_SECTION_HEADER 테이블의 각 엔트리 해석
    // secCnt 값은 IMAGE_FILE_HEADER의 NumberOfSections 필드에 지정되어 있음.

    BYTE buf[128]={0,};
    BYTE name[9]={0,};
    LPBYTE pIter=m_pImgView+offset;

    sprintf(buf,"[%08X] IMAGE_SECTION_HEADER TABLE",offset);
    fprintf(stdout,"%s\n",buf);
    for(INT i=0;i<secCnt;i++)
    {
        memset(name,0,sizeof(name));
        memcpy(name,pIter,IMAGE_SIZEOF_SHORT_NAME);
        printf("[%08X] %-8s[%02d]\n",offset,name,i);
        
        pIter+=IMAGE_SIZEOF_SHORT_NAME;
        offset+=IMAGE_SIZEOF_SHORT_NAME;

        INT cnt=sizeof(pcszFld)/sizeof(LPCSTR);
        for(INT i=0;i<cnt;i++)
        {
            memset(buf,0,sizeof(buf));
            if(anSize[i]== sizeof(WORD))
            {
                sprintf(buf,"[%08X] %s 0x%04X",offset, pcszFld[i],*((LPWORD)pIter));
            }
            else
            {
                sprintf(buf,"[%08X] %s 0x%08X",offset,pcszFld[i],*((LPDWORD)pIter));
            }
            printf("%s\n",buf);

            pIter+=anSize[i];
            offset+=anSize[i];
        }
    }


    return offset;
}