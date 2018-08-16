// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MY_TOOLBAR_H_
#define _MY_TOOLBAR_H_

#include "stdafx.h"

// TOOLBAR
void createToolbar(HWND hWnd, HWND& hToolBarWnd, bool& Toolbar_Exist);
void ToolbarNotifyHandle(HINSTANCE hInst, LPARAM lParam);
void ToolbarStyle(HWND hToolBarWnd, int tbStyle);
void viewToolbar(HWND hWnd, HWND hToolBarWnd);
void addEditToolbar(HWND hToolBarWnd, bool Toolbar_Exist);
void addFontsNColors(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist);
void addDrawToolBar(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist);
void addWindowlBar(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist);


void CheckMenuDraw(HWND hWnd, UINT MenuItemID);
void CheckToolbarDraw(HWND hToolBarWnd, UINT MenuItemID);
void CheckMenuWindow(HWND hWnd, UINT MenuItemID);
void CheckToolbarWindow(HWND hToolBarWnd, UINT MenuItemID);
void checkModeChange(bool& mode_change, HWND hwndMDIClient, int& i);
void changeToolbarStye(HWND hWnd, HWND hToolbarWnd, int tbStyle);
void changeMode(int& mode, int new_mode, UINT MenuItemID, HWND hWnd, HWND hToolbarWnd, HWND hwndMDIClient, bool& mode_change, int& i);


void enableCommand(HWND hFrameWnd, HWND hToolBarWnd, int mode);
void disableCommand(HWND hFrameWnd, HWND hToolBarWnd);

#endif // _MY_TOOLBAR_H_
