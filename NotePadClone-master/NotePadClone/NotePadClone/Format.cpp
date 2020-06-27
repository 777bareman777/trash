#include <Windows.h>
#include "Format.h"

HWND ReplaceEditControl(HWND h, CONST INT idc, FNCHANGESTYLE fnchange)
{
	HWND hwnd;
	HWND prev;
	RECT rc;
	POINT pt = { 0,0 };
	HINSTANCE hInst;
	LONG_PTR style;
	LONG_PTR exStyle;
	TCHAR* buf;
	INT length;
	TCHAR scls[MAX_PATH];
	HFONT hFont;
	int focus;

	hwnd = GetDlgItem(h, idc);
	if (!IsWindow(hwnd)) return 0;

	prev = GetWindow(hwnd, GW_HWNDPREV);
	hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
	style = GetWindowLongPtr(hwnd, GWL_STYLE);
	exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
	focus = hwnd == GetFocus();
	hFont = (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);

	ClientToScreen(h, &pt);
	GetWindowRect(hwnd, &rc);
	GetClassName(hwnd, scls, sizeof(scls) / sizeof(scls[0]));
	length = GetWindowTextLength(hwnd);
	buf = (TCHAR*)malloc((length + 1) * sizeof(TCHAR));
	GetWindowText(hwnd, buf, length + 1);

	DestroyWindow(hwnd);
	fnchange(&style, &exStyle);

	hwnd = CreateWindowEx(exStyle, scls, NULL, style,
		rc.left - pt.x, rc.top - pt.y,
		rc.right - rc.left, rc.bottom - rc.top,
		h, (HMENU)idc, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hwnd, EM_FMTLINES, (WPARAM)TRUE, 0);
	SetWindowPos(hwnd, prev, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	SetWindowText(hwnd, buf);
	free(buf);
	if (focus) {
		SetFocus(hwnd);
	}

	return hwnd;
}

void SetWordWrap(LONG_PTR* style, LONG_PTR* exStyle)
{
	(*style) ^= (ES_AUTOHSCROLL | WS_HSCROLL);
}

