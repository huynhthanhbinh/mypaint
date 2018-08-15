﻿// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#include "1653006_MyToolbar.h"
#include "stdafx.h"

#define IMAGE_WIDTH			18
#define IMAGE_HEIGHT		18
#define BUTTON_WIDTH		0
#define BUTTON_HEIGHT		0
#define TOOL_TIP_MAX_LEN	32

// Toolbar
// define new buttons
// 1st: ID của bitmap (có sẵn) / số thứ tự trong mảng (bitmap add thêm)
// 2nd: ID Menu Item
// 3rd: state trạng thái : enable, disable,...
// 4th: kiểu của item: button, seperator, ...
// 5th: 0
// 6th: 0
void createToolbar(HWND hWnd, HWND& hToolBarWnd, bool& Toolbar_Exist)
{
	// loading Common Control DLL
	InitCommonControls();

	TBBUTTON tbButtons[] =
	{
		// Zero-based Bitmap image, ID of command, Button state, Button style, 
		// ...App data, Zero-based string (Button's label)
	{ STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{ STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{ STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{ STD_PRINT,NULL/*ID_FILE_PRINT*/,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};

	// create a toolbar
	hToolBarWnd = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT,
		ID_TOOLBAR,
		sizeof(tbButtons) / sizeof(TBBUTTON),
		HINST_COMMCTRL,
		0,
		tbButtons,
		sizeof(tbButtons) / sizeof(TBBUTTON),
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		IMAGE_WIDTH,
		IMAGE_HEIGHT,
		sizeof(TBBUTTON));

	CheckMenuItem(GetSubMenu(GetMenu(hWnd), menuPos_Toolbar), ID_TOOLBAR_VIEWHIDE, MF_CHECKED | MF_BYCOMMAND);
	Toolbar_Exist = true;
}
void ToolbarNotifyHandle(HINSTANCE hInst, LPARAM lParam)
{
	LPTOOLTIPTEXT   lpToolTipText;
	TCHAR			szToolTipText[TOOL_TIP_MAX_LEN]; 	// ToolTipText, loaded from Stringtable resource

														// lParam: address of TOOLTIPTEXT struct
	lpToolTipText = (LPTOOLTIPTEXT)lParam;

	if (lpToolTipText->hdr.code == TTN_NEEDTEXT)
	{
		// hdr.iFrom: ID cua ToolBar button -> ID cua ToolTipText string
		LoadString(hInst, (UINT)lpToolTipText->hdr.idFrom, szToolTipText, TOOL_TIP_MAX_LEN);

		lpToolTipText->lpszText = szToolTipText;
	}
}
void ToolbarStyle(HWND hToolBarWnd, int tbStyle)
{
	ShowWindow(hToolBarWnd, SW_HIDE);
	SendMessage(hToolBarWnd, TB_SETSTYLE, (WPARAM)0, (LPARAM)(DWORD)tbStyle | CCS_TOP);
	ShowWindow(hToolBarWnd, SW_SHOW);
}
void viewToolbar(HWND hWnd, HWND hToolBarWnd)
{
	int vFlag = GetMenuState(GetMenu(hWnd), ID_TOOLBAR_VIEWHIDE, MF_BYCOMMAND) & MF_CHECKED;

	if (vFlag)
	{
		ShowWindow(hToolBarWnd, SW_HIDE);
		vFlag = MF_UNCHECKED;
	}
	else
	{
		ShowWindow(hToolBarWnd, SW_SHOW);
		vFlag = MF_CHECKED;
	}

	CheckMenuItem(GetSubMenu(GetMenu(hWnd), menuPos_Toolbar), ID_TOOLBAR_VIEWHIDE, vFlag | MF_BYCOMMAND);
}
void addEditToolbar(HWND hToolBarWnd, bool Toolbar_Exist)
{
	static bool exist = false;
	if (exist == false && Toolbar_Exist == true) {
		TBBUTTON tbButtons[] =
		{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ STD_CUT, ID_EDIT_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_COPY,	ID_EDIT_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_PASTE, ID_EDIT_PASTE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_DELETE, ID_EDIT_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
		};

		SendMessage(hToolBarWnd, TB_ADDBUTTONS,
			(WPARAM) sizeof(tbButtons) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&tbButtons);

		exist = true;
	}
}
void addFontsNColors(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist)
{
	static bool exist = false;
	if (exist == false && Toolbar_Exist == true) {
		TBBUTTON tbButtons[] =
		{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator 
		{ 0, ID_DRAW_COLOR,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 1, ID_DRAW_FONT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
		};

		TBADDBITMAP	tbBitmap[] =
		{
		{ hInst, IDB_COLORS },
		{ hInst, IDB_FONTS }
		};

		// Add bitmap to Image-list of ToolBar
		int idx = (int)
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[0]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[1]);

		// identify the bitmap index of each button
		tbButtons[1].iBitmap += idx;
		tbButtons[2].iBitmap += idx;

		// add buttons to toolbar
		SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(tbButtons) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&tbButtons);
		exist = true;
	}
}
void addDrawToolBar(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist) {
	static bool exist = false;
	if (exist == false && Toolbar_Exist == true) {
		TBBUTTON tbButtons[] =
		{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator 
		{ 0, ID_DRAW_LINE          , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0 },
		{ 1, ID_DRAW_ELLIPSE       , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0 },
		{ 2, ID_DRAW_RECTANGLE     , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0 },
		{ 3, ID_DRAW_SELECTOBJECT  , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0 },
		{ 4, ID_DRAW_TEXT          , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0 }
		};

		/* The same: for example: button draw select object

		tbButtons[4].iBitmap   = 3;
		tbButtons[4].idCommand = IDM_DRAW_SELECT_OBJECT;
		tbButtons[4].fsState   = TBSTATE_ENABLED;
		tbButtons[4].fsStyle   = TBSTYLE_BUTTON | TBSTYLE_CHECK | TBSTYLE_GROUP;
		tbButtons[4].dwData    = 0;
		tbButtons[4].iString   = 0;

		// TBSTYLE_CHECKGROUP = TBSTYLE_CHECK | TBSTYLE_GROUP !!!
		*/

		tbButtons[1].fsState |= TBSTATE_CHECKED; // Set Line button default when create

		TBADDBITMAP	tbBitmap[] =
		{
		{ hInst, IDB_LINE },
		{ hInst, IDB_ELLIPSE },
		{ hInst, IDB_RECTANGLE },
		{ hInst, IDB_SELECT },
		{ hInst, IDB_TEXT }
		};


		// Add bitmap to Image-list of ToolBar
		int idx = (int)
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[0]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[1]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[2]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[3]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[4]);

		// identify the bitmap index of each button
		tbButtons[1].iBitmap += idx;
		tbButtons[2].iBitmap += idx;
		tbButtons[3].iBitmap += idx;
		tbButtons[4].iBitmap += idx;
		tbButtons[5].iBitmap += idx;


		// add buttons to toolbar
		SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(tbButtons) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&tbButtons);

		exist = true;
	} 
}
void ShowNotice(HWND hWnd, const WCHAR* MenuCaption) { // Huỳnh Thanh Bình
	WCHAR mess[40] = L"Ban vua chon menu ";
	wcscat_s(mess, MenuCaption);
	MessageBox(hWnd, mess, L"NOTICE", MB_OK);
}
void addViewColor() {
	

	
}


void CheckMenuDraw(HWND hWnd, UINT MenuItemID) { // Huỳnh Thanh Bình
	HMENU hMenu = GetSubMenu(GetMenu(hWnd), menuPos_Draw);

	for (UINT i = ID_DRAW_LINE; i <= ID_DRAW_SELECTOBJECT; ++i) {
		CheckMenuItem(hMenu, i, MF_UNCHECKED | MF_BYCOMMAND);
	} CheckMenuItem(hMenu, MenuItemID, MF_CHECKED | MF_BYCOMMAND);
}
void CheckToolbarDraw(HWND hToolBarWnd, UINT MenuItemID) {
	for (UINT i = ID_DRAW_LINE; i <= ID_DRAW_SELECTOBJECT; ++i) {
		SendMessage(hToolBarWnd, TB_SETSTATE, i, TBSTATE_ENABLED);
	} SendMessage(hToolBarWnd, TB_SETSTATE, MenuItemID, TBSTATE_ENABLED | TBSTATE_CHECKED);
}
void checkModeChange(bool& mode_change, HWND hwndMDIClient, int& i) {
	if (mode_change == true) { // fix bug prev mode is select -> still have cover frame
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		InvalidateRect(current, NULL, TRUE);
		i = -1; // fix bug prev mode is select --> still unselect (i != -1)
		mode_change = false;
	}
}
void changeMode(int& mode, int new_mode, UINT MenuItemID, HWND hWnd, HWND hToolbarWnd, HWND hwndMDIClient, bool& mode_change,  int& i) {
	mode = new_mode;

	if (mode == SELECT) mode_change = true;
	else	            checkModeChange(mode_change, hwndMDIClient, i);

	CheckMenuDraw(hWnd, MenuItemID);
	CheckToolbarDraw(hToolbarWnd, MenuItemID);
}
void changeToolbarStye(HWND hWnd, HWND hToolbarWnd, int tbStyle) {
	ToolbarStyle(hToolbarWnd, tbStyle);
	HMENU hMenu = GetSubMenu(GetMenu(hWnd), menuPos_Toolbar);

	if (tbStyle == TBSTYLE_FLAT) {
		CheckMenuItem(hMenu, ID_TOOLBAR_FLAT, MF_CHECKED | MF_BYCOMMAND);
		CheckMenuItem(hMenu, ID_TOOLBAR_TRANSPARENT, MF_UNCHECKED | MF_BYCOMMAND);
		return;
	}
	else {
		CheckMenuItem(hMenu, ID_TOOLBAR_FLAT, MF_UNCHECKED | MF_BYCOMMAND);
		CheckMenuItem(hMenu, ID_TOOLBAR_TRANSPARENT, MF_CHECKED | MF_BYCOMMAND);
		return;
	}
}
