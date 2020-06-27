#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include "file.h"


extern HWND g_hWndMain;
extern HWND g_hEdit;
extern TCHAR szTitle[MAX_PATH];



void ChangeCaption(TCHAR* Path)
{
	TCHAR Cap[MAX_PATH];
	_tcscpy_s(szTitle, MAX_PATH, Path);
	swprintf_s(Cap, MAX_PATH, TEXT("%s - NotePadClone"), Path);
	SetWindowText(g_hWndMain, Cap);
}

void ModifingCaption(TCHAR* Path)
{
	TCHAR Cap[MAX_PATH];
	swprintf_s(Cap, MAX_PATH, TEXT("*%s - NotePadClone"), Path);
	SetWindowText(g_hWndMain, Cap);
}

int ConfirmSave()
{
	int result = IDNO;
	TCHAR Mes[MAX_PATH];

	if (SendMessage(g_hEdit, EM_GETMODIFY, 0, 0) == TRUE) {
		swprintf_s(Mes, TEXT("변경 내용을 %s에 저장하시겠습니까?"), szTitle);
		result = MessageBox(g_hWndMain, Mes, TEXT("NotePadClone"), MB_YESNOCANCEL);
		if (result == IDCANCEL) {
			return IDCANCEL;
		}
		if (result == IDYES) {
			if (Save() == FALSE) {
				return IDCANCEL;
			}
			else {
				return IDYES;
			}
		}
	}
	return result;
}

BOOL Save()
{
	if (CompareStringOrdinal(szTitle, -1, TEXT("제목 없음.txt"), -1, FALSE) == CSTR_EQUAL) {
		return SaveAs();
	}
	else {
		return SaveToFile(szTitle);
	}
}

BOOL SaveAs()
{
	OPENFILENAME OFN;
	TCHAR lpstrFile[MAX_PATH] = TEXT("*.txt");
	TCHAR lpstrFileTitle[MAX_PATH] = TEXT("");
	memset(&OFN, 0, sizeof(OPENFILENAME));

	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWndMain;
	OFN.lpstrFilter = TEXT("텍스트 문서(*.txt)\0*.txt\0모든 파일(*.*)\0*.*\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = MAX_PATH;
	OFN.lpstrFileTitle = lpstrFileTitle;
	OFN.nMaxFileTitle = MAX_PATH;
	OFN.lpstrDefExt = TEXT("txt");
	if (GetSaveFileName(&OFN) == FALSE) {
		return FALSE;
	}
	ChangeCaption(OFN.lpstrFileTitle);
	return SaveToFile(OFN.lpstrFile);
}

BOOL SaveToFile(TCHAR* Path)
{
	HANDLE hFile;
	DWORD dwWritten;
	int length;
	TCHAR* buf;

	hFile = CreateFile(Path, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	length = GetWindowTextLength(g_hEdit);
	buf = (TCHAR*)malloc((length + 1) * sizeof(TCHAR));
	GetWindowText(g_hEdit, buf, length + 1);
	WriteFile(hFile, buf, sizeof(TCHAR) * length, &dwWritten, NULL);
	CloseHandle(hFile);
	free(buf);
	SendMessage(g_hEdit, EM_SETMODIFY, (WPARAM)FALSE, 0);

	return TRUE;
}

void Load()
{
	OPENFILENAME OFN;
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	HANDLE hFile;
	DWORD dwRead;
	DWORD size;
	TCHAR* buf;

	if (ConfirmSave() == IDCANCEL) {
		return;
	}

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWndMain;
	OFN.lpstrFilter = TEXT("텍스트 문서(*.txt)\0*.txt\0모든 파일(*.*)\0*.*\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = MAX_PATH;
	OFN.lpstrDefExt = TEXT("txt");
	if (GetOpenFileName(&OFN) == FALSE) {
		return;
	}

	hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(g_hWndMain, TEXT("파일을 열 수 없습니다"), TEXT("에러"), MB_OK);
		return;
	}

	size = GetFileSize(hFile, NULL);
	buf = (TCHAR*)malloc(sizeof(TCHAR) * (size + 1));
	memset(buf, 0, sizeof(TCHAR) * (size + 1));
	ReadFile(hFile, buf, sizeof(TCHAR) * size, &dwRead, NULL);
	CloseHandle(hFile);
	SetWindowText(g_hEdit, buf);
	free(buf);

	SendMessage(g_hEdit, EM_SETMODIFY, (WPARAM)FALSE, 0);
	ChangeCaption(OFN.lpstrFile);
}