// 1653006
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


void createColorbar(HINSTANCE hInst, HWND hWnd, HWND& hColorbar)
{
	hColorbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | CCS_VERT, 
		0, 0, 0, 0,
		hWnd, NULL, HINST_COMMCTRL, NULL);

	SendMessage(hColorbar, TB_SETMAXTEXTROWS, 0, 0); // for button tool-tips
	SendMessage(hColorbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	
	TBBUTTON tbButton[] =
	{
	{ 30, 0, TBSTATE_ENABLED | TBSTATE_WRAP, TBSTYLE_SEP, 0, 0 }, // seperator 
	{ 0, ID_DRAW_COLOR,	TBSTATE_ENABLED | TBSTATE_WRAP, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Choose Colors" },
	{ 1, ID_DRAW_FONT,	TBSTATE_ENABLED | TBSTATE_WRAP, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Choose Fonts" }
	};

	TBADDBITMAP	tbBitmap[] =
	{
	{ hInst, IDB_COLORS },
	{ hInst, IDB_FONTS }
	};


	int idx = (int)
	SendMessage(hColorbar, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[0]);
	SendMessage(hColorbar, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[1]);

	tbButton[1].iBitmap += idx;
	tbButton[2].iBitmap += idx;

	SendMessage(hColorbar, TB_ADDBUTTONS, sizeof(tbButton) / sizeof(TBBUTTON), (LPARAM)&tbButton);
}
void createToolbar(HWND hWnd, HWND& hToolBarWnd, bool& Toolbar_Exist)
{
	// loading Common Control DLL
	InitCommonControls();

	TBBUTTON tbButtons[] =
	{
		// Zero-based Bitmap image, ID of command, Button state, Button style, 
		// ...App data, Zero-based string (Button's label)
	{ -1, 0,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{ 10, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
	{ STD_FILENEW,	ID_FILE_NEW,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"New (Ctrl + N)"},
	{ STD_FILEOPEN,	ID_FILE_OPEN,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Open (Ctrl + O)" },
	{ STD_FILESAVE,	ID_FILE_SAVE,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Save (Ctrl + S)" },
	{ STD_PRINT,    ID_FILE_PRINT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Print (Ctrl + P)" }
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

	SendMessage(hToolBarWnd, TB_SETMAXTEXTROWS, 0, 0); // for button tool-tips

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
void viewToolbar(HWND hWnd, HWND hToolBarWnd, HWND hwndMDIClient)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	int vFlag = GetMenuState(GetMenu(hWnd), ID_TOOLBAR_VIEWHIDE, MF_BYCOMMAND) & MF_CHECKED;

	if (vFlag) // Hide Toolbar
	{
		ShowWindow(hToolBarWnd, SW_HIDE);
		vFlag = MF_UNCHECKED;

		MoveWindow(hToolBarWnd, rect.left, rect.top, rect.right, rect.bottom, TRUE);
		MoveWindow(hwndMDIClient, rect.left, rect.top, rect.right, rect.bottom, TRUE);
	}
	else // Show Toolbar
	{
		MoveWindow(hwndMDIClient, rect.left, rect.top + 28, rect.right, rect.bottom - 28, TRUE);
		MoveWindow(hToolBarWnd, rect.left, rect.top + 2, rect.right, rect.bottom - 2, TRUE);
		
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
		{ 20, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ STD_CUT, ID_EDIT_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Cut (Ctrl + X)" },
		{ STD_COPY,	ID_EDIT_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Copy (Ctrl + C)" },
		{ STD_PASTE, ID_EDIT_PASTE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Paste (Ctrl + P)" },
		{ STD_DELETE, ID_EDIT_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Delete (Del)" },
		{ 20, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ STD_UNDO, ID_EDIT_UNDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Undo (Ctrl + Z)" },
		{ STD_REDOW, ID_EDIT_REDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Redo (Ctrl + Y)" },
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
		{ 20, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator 
		{ 0, ID_DRAW_COLOR,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Choose Colors" },
		{ 1, ID_DRAW_FONT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, (INT_PTR)L"Choose Fonts" }
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
		{ 20, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator 
		{ 0, ID_DRAW_LINE          , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Line" },
		{ 1, ID_DRAW_ELLIPSE       , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Ellipse" },
		{ 2, ID_DRAW_RECTANGLE     , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Rectangle" },
		{ 3, ID_DRAW_SELECTOBJECT  , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Select Object" },
		{ 4, ID_DRAW_TEXT          , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Insert Text" }
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
void addWindowlBar(HINSTANCE hInst, HWND hToolBarWnd, bool Toolbar_Exist) {
	static bool exist = false;
	if (exist == false && Toolbar_Exist == true) {
		TBBUTTON tbButtons[] =
		{
		{ 20, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator 
		{ 0, ID_WINDOW_CASCADE   , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Cascade" },
		{ 1, ID_WINDOW_VERTICAL  , TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Tile Vertical" },
		{ 2, ID_WINDOW_HORIZONTAL, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_CHECKGROUP, 0,0, 0, (INT_PTR)L"Tile Horizontal" },
		{ 20, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator 
		{ 3, ID_WINDOW_CLOSEALL  , TBSTATE_ENABLED, TBSTYLE_BUTTON                     , 0,0, 0, (INT_PTR)L"Close All Child Windows" },
		};

		tbButtons[1].fsState |= TBSTATE_CHECKED; // Set Cascade button default when create

		TBADDBITMAP	tbBitmap[] =
		{
		{ hInst, IDB_WINDOW_CASCADE },
		{ hInst, IDB_WINDOW_VERTICAL },
		{ hInst, IDB_WINDOW_HORIZONTAL },
		{ hInst, IDB_WINDOW_CLOSEALL },
		};


		// Add bitmap to Image-list of ToolBar
		int idx = (int)
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[0]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[1]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[2]);
		SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)1, (LPARAM)(LPTBADDBITMAP)&tbBitmap[3]);


		// identify the bitmap index of each button
		tbButtons[1].iBitmap += idx;
		tbButtons[2].iBitmap += idx;
		tbButtons[3].iBitmap += idx;
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
void CheckMenuWindow(HWND hWnd, UINT MenuItemID) { // Huỳnh Thanh Bình
	HMENU hMenu = GetSubMenu(GetMenu(hWnd), menuPos_Window);

	for (UINT i = ID_WINDOW_CASCADE; i <= ID_WINDOW_HORIZONTAL; ++i) {
		CheckMenuItem(hMenu, i, MF_UNCHECKED | MF_BYCOMMAND);
	} CheckMenuItem(hMenu, MenuItemID, MF_CHECKED | MF_BYCOMMAND);
}
void CheckToolbarWindow(HWND hToolBarWnd, UINT MenuItemID) {
	for (UINT i = ID_WINDOW_CASCADE; i <= ID_WINDOW_HORIZONTAL; ++i) {
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


void enableCommand(HWND hFrameWnd, HWND hToolBarWnd, int mode) {
	HMENU hPopup = GetMenu(hFrameWnd);
	EnableMenuItem(hPopup, menuPos_Edit, MF_ENABLED | MF_BYPOSITION);
	EnableMenuItem(hPopup, menuPos_Draw, MF_ENABLED | MF_BYPOSITION);
	EnableMenuItem(hPopup, menuPos_Window, MF_ENABLED | MF_BYPOSITION);

	switch (mode) {
	case LINE:
		CheckMenuDraw(hFrameWnd, ID_DRAW_LINE);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_LINE);
		break;
	case ELLIPSE:
		CheckMenuDraw(hFrameWnd, ID_DRAW_ELLIPSE);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_ELLIPSE);
		break;
	case RECTANGLE:
		CheckMenuDraw(hFrameWnd, ID_DRAW_RECTANGLE);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_RECTANGLE);
		break;
	case INSERTTEXT:
		CheckMenuDraw(hFrameWnd, ID_DRAW_TEXT);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_TEXT);
		break;
	case SELECT:
		CheckMenuDraw(hFrameWnd, ID_DRAW_SELECTOBJECT);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_SELECTOBJECT);
		break;
	}


	CheckMenuWindow(hFrameWnd, ID_WINDOW_CASCADE);
	CheckToolbarWindow(hToolBarWnd, ID_WINDOW_CASCADE);

	SendMessage(hToolBarWnd, TB_SETSTATE, ID_FILE_PRINT     , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_FILE_SAVE      , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_CUT       , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_COPY      , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_PASTE     , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_DELETE    , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_DRAW_COLOR     , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_DRAW_FONT      , TBSTATE_ENABLED);
	SendMessage(hToolBarWnd, TB_SETSTATE, ID_WINDOW_CLOSEALL, TBSTATE_ENABLED);
}
void disableCommand(HWND hFrameWnd, HWND hToolBarWnd) {
	HMENU hPopup = GetMenu(hFrameWnd);
	EnableMenuItem(hPopup, menuPos_Edit, MF_GRAYED | MF_BYPOSITION);
	EnableMenuItem(hPopup, menuPos_Draw, MF_GRAYED | MF_BYPOSITION);
	EnableMenuItem(hPopup, menuPos_Window, MF_GRAYED | MF_BYPOSITION);
	DrawMenuBar(hFrameWnd);

	for (UINT i = ID_FILE_SAVE; i <= ID_WINDOW_CLOSEALL; ++i)
		SendMessage(hToolBarWnd, TB_SETSTATE, i, TBSTATE_INDETERMINATE);
}
