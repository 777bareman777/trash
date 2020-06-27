#pragma once

typedef void(*FNCHANGESTYLE)(LONG_PTR*, LONG_PTR*);
void SetWordWrap(LONG_PTR* style, LONG_PTR* exStyle);
HWND ReplaceEditControl(HWND h, CONST INT idc, FNCHANGESTYLE fnchange);