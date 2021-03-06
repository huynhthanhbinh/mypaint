// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MY_PAINT_H_
#define _MY_PAINT_H_

#include "stdafx.h"
#include "1653006_MyObject.h"

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WelcomeDlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutMeDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	MDICloseProc(HWND hChildwnd, LPARAM lParam);


void onCreate(HWND hWnd, bool& Toolbar_Exist);
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist);

void ShowNotice(HWND hWnd, const WCHAR* MenuCaption);

#endif // !_MY_PAINT_H_