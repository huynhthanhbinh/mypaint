#ifndef _MY_TOOLBAR_H_
#define _MY_TOOLBAR_H_

#include "stdafx.h"

// TOOLBAR
void CheckMenuDraw(HWND hWnd, UINT MenuItemID);
void CheckToolbarDraw(HWND hToolBarWnd, UINT MenuItemID);
void createToolbar(HWND hWnd, HWND& hToolBarWnd, bool& Toolbar_Exist);
void ToolbarNotifyHandle(HINSTANCE hInst, LPARAM lParam);
void ToolbarStyle(HWND hToolBarWnd, int tbStyle);
void viewToolbar(HWND hWnd, HWND hToolBarWnd);
void addEditToolbar(HWND hToolBarWnd, bool Toolbar_Exist);
void addFontsNColors(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist);
void addDrawToolBar(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist);

#endif // _MY_TOOLBAR_H_
