#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <magnification.h>
#include "View.h"

// HWND h : Statusbar handle
int GetStatusbarHeight(HWND h)
{
	HDC hdc;
	TEXTMETRIC tm;
	int thick[3];
	int height = -1;

	if (h == NULL) {
		return height;
	}

	hdc = GetDC(h);
	GetTextMetrics(hdc, &tm);
	SendMessage(h, SB_GETBORDERS, 0, (LPARAM)&thick);
	height = tm.tmHeight + thick[0] + thick[1] + thick[2];
	return height;
}

void SetStatusbarPart(HWND h, int width)
{
	int arr[5];
	arr[0] = width - 550;
	arr[1] = width - 350;
	arr[2] = width - 300;
	arr[3] = width - 150;
	arr[4] = width;
	SendMessage(h, SB_SETPARTS, 5, (LPARAM)arr);
}

// HWND h : statusbar handle
// HWND h2 : edit handle
void SetStatusbarText(HWND h,HWND h2)
{
	TCHAR str[256];
	int col, line;
	line = GetCurrLine(h2) + 1;
	col = GetCurrCul(h2);
	swprintf_s(str, 256, TEXT("Ln %d, Col %d"), line,col);
	SendMessage(h, SB_SETTEXT, 1, (LPARAM)str);
	swprintf_s(str, 256, TEXT("Windows(CRLF)"));
	SendMessage(h, SB_SETTEXT, 3, (LPARAM)str);
	swprintf_s(str, 256, TEXT("UTF-16 LE"));
	SendMessage(h, SB_SETTEXT, 4, (LPARAM)str);
}

// HWND h : edit handle
int GetCurrLine(HWND h)
{
	int result = SendMessage(h, EM_LINEFROMCHAR, -1, 0);
	return result;
}

// HWND h : edit handle
int GetCurrCul(HWND h)
{
	int start = SendMessage(h, EM_LINEINDEX, GetCurrLine(h), 0);
	int end = SendMessage(h, EM_GETSEL, NULL, NULL);
	int result;

	if (start == 0) {
		result = LOWORD(end);
	}
	else {
		result = (-start) + LOWORD(end);
	}
	return result;
}