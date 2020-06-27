#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <magnification.h>

#include "resource.h"
#include "Format.h"
#include "file.h"
#include "View.h"


// 매크로 상수
#define IDC_EDIT 10001



// 전역변수
HINSTANCE g_hInst;
HWND g_hWndMain;
HWND g_hEdit;
HWND g_hState;
HWND g_hMag;
TCHAR szTitle[MAX_PATH];
TCHAR szWindowClass[MAX_PATH];

BOOL bAutoline = TRUE;
BOOL bStatusbar = TRUE;



// 함수 정의 선언
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnSize(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnInitMenu(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);




int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_PATH);
	LoadString(hInstance, IDS_NOTEPADCLONE, szWindowClass, MAX_PATH);

	if (MyRegisterClass(hInstance)==FALSE){
		return FALSE;
	}

	if (!InitInstance(hInstance, nCmdShow)){
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	
	
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		if (!TranslateAccelerator(g_hWndMain, hAccelTable, &message)) {
			if (SendMessage(g_hEdit, EM_GETMODIFY, 0, 0) == TRUE) {
				ModifingCaption(szTitle);
				SetStatusbarText(g_hState, g_hEdit);
			}
			else {
				ChangeCaption(szTitle);
				SetStatusbarText(g_hState, g_hEdit);
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	return (int)message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClassEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.hIconSm = NULL;
	if (RegisterClassEx(&WndClassEx) == 0)
		return FALSE;

	return TRUE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance;
	TCHAR Mes[MAX_PATH] = TEXT(" - NotePadClone");
	_tcscat_s(szTitle, MAX_PATH, Mes);
	HWND hWnd = CreateWindowEx(0, 
		szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	if (!hWnd) {
		return FALSE;
	}
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_PATH);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_CREATE:
		return OnCreate(hWnd, wParam, lParam);
	case WM_COMMAND:
		return OnCommand(hWnd, wParam, lParam);
	case WM_PAINT:
		return OnPaint(hWnd, wParam, lParam);
	case WM_SIZE:
		return OnSize(hWnd, wParam, lParam);
	case WM_INITMENU:
		return OnInitMenu(hWnd, wParam, lParam);
	case WM_QUERYENDSESSION:
	case WM_CLOSE:
		if (ConfirmSave() == IDCANCEL) {
			return TRUE;
		}
		else {
			break;
		}
	case WM_DESTROY:
		return OnDestroy(hWnd, wParam, lParam);
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	INITCOMMONCONTROLSEX iccex;
	iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccex);

	g_hWndMain = hWnd;

	g_hEdit=CreateWindowEx(0, TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE
		 | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
		0,0,0,0, hWnd, (HMENU)IDC_EDIT, g_hInst, NULL);
	SendMessage(g_hEdit, EM_FMTLINES, (WPARAM)TRUE, 0);
	g_hState = CreateStatusWindow(WS_CHILD | WS_VISIBLE, TEXT(""), hWnd, 0);

	return 0;
}

LRESULT OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	/*MagUninitialize();*/

	PostQuitMessage(0);
	return 0;
}


LRESULT OnSize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int height = GetStatusbarHeight(g_hState);
	SendMessage(g_hState, WM_SIZE, wParam, lParam);
	MoveWindow(g_hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam)-height, TRUE);
	SetStatusbarPart(g_hState, LOWORD(lParam));
	return 0;
}

LRESULT OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);
	return 0;
}

LRESULT OnInitMenu(HWND hWnd, WPARAM wParam, LPARAM)
{
	if (SendMessage(g_hEdit, EM_CANUNDO, 0, 0) == TRUE) {
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_UNDO, MF_ENABLED | MF_BYCOMMAND);
	}
	else {
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_UNDO, MF_GRAYED | MF_BYCOMMAND);
	}

	DWORD Start, End;
	SendMessage(g_hEdit, EM_GETSEL, (WPARAM)&Start, (LPARAM)&End);
	if (Start != End) {
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_CUT, MF_ENABLED | MF_BYCOMMAND);
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_COPY, MF_ENABLED | MF_BYCOMMAND);
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_DEL, MF_ENABLED | MF_BYCOMMAND);
	}
	else {
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_CUT, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_COPY, MF_GRAYED | MF_BYCOMMAND);
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_DEL, MF_GRAYED | MF_BYCOMMAND);
	}

	if (IsClipboardFormatAvailable(CF_TEXT)) {
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_PASTE, MF_ENABLED | MF_BYCOMMAND);
	}
	else {
		EnableMenuItem(GetMenu(hWnd), IDM_EDIT_PASTE, MF_GRAYED | MF_BYCOMMAND);
	}


	if (bAutoline) {
		CheckMenuItem(GetMenu(hWnd), IDM_FORMAT_AUTOLINE, MF_CHECKED | MF_BYCOMMAND);
	}
	else {
		CheckMenuItem(GetMenu(hWnd), IDM_FORMAT_AUTOLINE, MF_UNCHECKED | MF_BYCOMMAND);
	}

	if (bStatusbar) {
		CheckMenuItem(GetMenu(hWnd), IDM_VIEW_STATUSBAR, MF_CHECKED | MF_BYCOMMAND);
	}
	else {
		CheckMenuItem(GetMenu(hWnd), IDM_VIEW_STATUSBAR, MF_UNCHECKED | MF_BYCOMMAND);
	}


	return 0;
}

LRESULT OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int id = LOWORD(wParam);

	switch (id)
	{
	case IDM_FORMAT_AUTOLINE:
		bAutoline = !bAutoline;
		if (bAutoline) {
			g_hEdit=ReplaceEditControl(hWnd, IDC_EDIT, SetWordWrap);
		}
		else {
			g_hEdit=ReplaceEditControl(hWnd, IDC_EDIT, SetWordWrap);
		}
		break;
	case IDM_VIEW_STATUSBAR:
		bStatusbar = !bStatusbar;
		if (bStatusbar) {

		}
		else {

		}
		break;


	case IDM_EDIT_UNDO:
		SendMessage(g_hEdit, EM_UNDO, 0, 0);
		break;
	case IDM_EDIT_CUT:
		SendMessage(g_hEdit, WM_CUT, 0, 0);
		break;
	case IDM_EDIT_COPY:
		SendMessage(g_hEdit, WM_COPY, 0, 0);
		break;
	case IDM_EDIT_PASTE:
		SendMessage(g_hEdit, WM_PASTE, 0, 0);
		break;
	case IDM_EDIT_DEL:
		SendMessage(g_hEdit, WM_CLEAR, 0, 0);
		break;
	case IDM_EDIT_SELALL:
		SendMessage(g_hEdit, EM_SETSEL, 0, -1);
		break;
	case IDM_EDIT_TIME:
		{
			SYSTEMTIME st;
			TCHAR text[128];
			GetLocalTime(&st);
			swprintf_s(text, 128, TEXT("%s %02d:%02d %d-%02d-%02d"),
				(st.wHour > 11) ? TEXT("오후") : TEXT("오전"), (st.wHour == 0 || st.wHour == 12) ? 12 : (st.wHour > 12) ? st.wHour - 12 : st.wHour,
				st.wMinute, st.wYear, st.wMonth, st.wDay);
			SendMessage(g_hEdit, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)text);
			break;
		}

		case IDM_FILE_NEW:
		if (ConfirmSave() == IDCANCEL) {
			break;
		}
		SetWindowText(g_hEdit, TEXT(""));
		TCHAR Mes[MAX_PATH];
		LoadString(g_hInst, IDS_APP_TITLE, Mes, MAX_PATH);
		ChangeCaption(Mes);
		break;


	case IDM_FILE_LOAD:
		Load();
		break;
	case IDM_FILE_SAVE:
		Save();
		break;
	case IDM_FILE_SAVEAS:
		SaveAs();
		break;
	case IDM_FILE_EXIT:
		DestroyWindow(hWnd);
		break;
	}
	return 0;
}