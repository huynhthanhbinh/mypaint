// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MY_PAINT_H_
#define _MY_PAINT_H_

#include "stdafx.h"

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WelcomeDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	MDICloseProc(HWND hChildwnd, LPARAM lParam);



void initFrameWindow(HWND hWnd);
void initChildWindow(HWND hWnd, int nType);
void onNewDrawWnd(HWND hWnd);
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist);

void ShowNotice(HWND hWnd, const WCHAR* MenuCaption);
void OnChooseColors(HWND hWnd);
void OnChooseFonts(HWND hWnd);
void OnOpenFile(HWND hWnd);
void OnSaveFile(HWND hWnd);


#endif // !_MY_PAINT_H_