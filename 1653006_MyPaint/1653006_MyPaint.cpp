// 1653006_MyPaint.cpp : Defines the entry point for the application.
// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#include "stdafx.h"
#include "1653006_MyPaint.h"
#include <CommCtrl.h>
#include <commdlg.h>

#pragma comment(lib,"ComCtl32.Lib") // searches first in the current working directory 
#pragma comment(lib,"ComDlg32.Lib") // and then in the path specified in the LIB environment variable.

#define MAX_LOADSTRING		100
#define IMAGE_WIDTH			18
#define IMAGE_HEIGHT		18
#define BUTTON_WIDTH		0
#define BUTTON_HEIGHT		0
#define TOOL_TIP_MAX_LEN	32

struct CHILD_WND_DATA {
	BYTE wndType;
	HWND hWnd;
	COLORREF rgbColor = NULL;
	LOGFONT logFont;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

WCHAR szDrawWindowClass[MAX_LOADSTRING] = L"Draw";	// class draw
WCHAR szDrawTitle[MAX_LOADSTRING];					// Title for draw

HWND hFrameWnd;
HWND hToolBarWnd;
HWND hwndMDIClient = NULL;
//COLORREF rgbCurrentColor = RGB(0, 0, 0);

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
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void ShowNotice(HWND hWnd, const WCHAR* MenuCaption);
void CheckMenuDraw(HWND hWnd, UINT MenuItemID);
void CheckToolbarDraw(HWND hWnd, UINT MenuItemID);


bool Toolbar_Exist = false;
void createToolbar(HWND hWnd);
void ToolbarNotifyHandle(LPARAM	lParam);
void ToolbarStyle(int tbStyle);
void viewToolbar(HWND hWnd);
void addEditToolbar();
void addFontsNColors();
void addDrawToolBar();

void OnChooseColors(HWND hWnd);
void OnChooseFonts(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1653006MYPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1653006MYPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		if (!TranslateMDISysAccel(hwndMDIClient, &msg) 
			&& !TranslateAccelerator(hFrameWnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1653006MYPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	RegisterClassExW(&wcex);

	// Draw child window
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= DrawWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 8;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName  = szDrawWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	RegisterClassExW(&wcex);

    return 1;
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
INT_PTR CALLBACK WelcomeDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // lấy 2 byte thấp của WordParam --> cho biết ID của control;
		case IDOK:
			EndDialog(hDlg, NULL); 
			break;
		}
		return (INT_PTR)TRUE;
	} return (INT_PTR)FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: {
		DialogBox(hInst, MAKEINTRESOURCE(IDD_WELCOME), hWnd, WelcomeDlgProc);
		initFrameWindow(hWnd);
		createToolbar(hWnd);
		addDrawToolBar();
		HMENU hMenu = GetSubMenu(GetMenu(hWnd), 2);
		CheckMenuItem(hMenu, ID_TOOLBAR_DRAWTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		return 0;
	}
	case WM_COMMAND:
		onCommand(hWnd, message, wParam, lParam);
		break;
	case WM_NOTIFY:
		ToolbarNotifyHandle(lParam);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_SIZE: // Update the size of MDI client window
		UINT w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hwndMDIClient, 0, 28, w, h - 28, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
	case WM_INITDIALOG: {
		//HBITMAP MyPaint = LoadBitmap(hInst, L"Button_Colors.bmp");
		//SendDlgItemMessage(hDlg, IDC_ABOUT, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)MyPaint);
		return (INT_PTR)TRUE;
	}
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
LRESULT CALLBACK DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		initChildWindow(hWnd, 1);
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		break;
	case WM_SIZE:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK MDICloseProc(HWND hChildwnd, LPARAM lParam)
{
	SendMessage(hwndMDIClient, WM_MDIDESTROY, (WPARAM)hChildwnd, 0l);
	return 1;
}


void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_FILE_NEW:
		onNewDrawWnd(hWnd);
		break;
	case ID_FILE_OPEN:
		ShowNotice(hWnd, L"Open");
		break;
	case ID_FILE_SAVE:
		ShowNotice(hWnd, L"Save");
		break;
	case ID_DRAW_LINE:
		CheckMenuDraw(hWnd, ID_DRAW_LINE); 
		CheckToolbarDraw(hWnd, ID_DRAW_LINE);
		ShowNotice(hWnd, L"Draw Line");
		break;
	case ID_DRAW_RECTANGLE:
		CheckMenuDraw(hWnd, ID_DRAW_RECTANGLE);
		CheckToolbarDraw(hWnd, ID_DRAW_RECTANGLE);
		ShowNotice(hWnd, L"Draw Rectangle");
		break;
	case ID_DRAW_ELLIPSE:
		CheckMenuDraw(hWnd, ID_DRAW_ELLIPSE);
		CheckToolbarDraw(hWnd, ID_DRAW_ELLIPSE);
		ShowNotice(hWnd, L"Draw Ellipse");
		break;
	case ID_DRAW_TEXT:
		CheckMenuDraw(hWnd, ID_DRAW_TEXT);
		CheckToolbarDraw(hWnd, ID_DRAW_TEXT);
		ShowNotice(hWnd, L"Insert Text");
		break;
	case ID_DRAW_SELECTOBJECT:
		CheckMenuDraw(hWnd, ID_DRAW_SELECTOBJECT);
		CheckToolbarDraw(hWnd, ID_DRAW_SELECTOBJECT);
		ShowNotice(hWnd, L"Select Object");
		break;
	case ID_DRAW_FONT:
		OnChooseFonts(hWnd);
		break;
	case ID_DRAW_COLOR:
		OnChooseColors(hWnd);
		break;
	/*case ID_TOOLBAR_CREATE:
		doCreate_ToolBar(hWnd);
		break;*/
	case ID_TOOLBAR_EDITTOOLBAR:
		addEditToolbar();
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_TOOLBAR_EDITTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_FONTS_COLORS:
		addFontsNColors();
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_TOOLBAR_FONTS_COLORS, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_DRAWTOOLBAR:
		addDrawToolBar();
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_TOOLBAR_DRAWTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_FLAT:
	{
		ToolbarStyle(TBSTYLE_FLAT);
		HMENU hMenu = GetSubMenu(GetMenu(hWnd), 2);
		CheckMenuItem(hMenu, ID_TOOLBAR_FLAT, MF_CHECKED | MF_BYCOMMAND);
		CheckMenuItem(hMenu, ID_TOOLBAR_TRANSPARENT, MF_UNCHECKED | MF_BYCOMMAND);
		break;
	}
	case ID_TOOLBAR_TRANSPARENT:
	{
		HMENU hMenu = GetSubMenu(GetMenu(hWnd), 2);
		CheckMenuItem(hMenu, ID_TOOLBAR_FLAT, MF_UNCHECKED | MF_BYCOMMAND);
		CheckMenuItem(hMenu, ID_TOOLBAR_TRANSPARENT, MF_CHECKED | MF_BYCOMMAND);
		ToolbarStyle(TBSTYLE_TRANSPARENT);
		break;
	}
	case ID_TOOLBAR_VIEWHIDE:
		viewToolbar(hWnd);
		break;
	case ID_WINDOW_TILE:
		SendMessage(hwndMDIClient, WM_MDITILE, 0, 0);
		break;
	case ID_WINDOW_CASCADE:
		SendMessage(hwndMDIClient, WM_MDICASCADE, 0, 0);
		break;
	case ID_WINDOW_CLOSEALL:
		EnumChildWindows(hwndMDIClient, (WNDENUMPROC)MDICloseProc, 0L);
		break;
	default:
		DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
	}
}
void ShowNotice(HWND hWnd, const WCHAR* MenuCaption) { // Huỳnh Thanh Bình
	WCHAR mess[40] = L"Ban vua chon menu ";
	wcscat_s(mess, MenuCaption);
	MessageBox(hWnd, mess, L"NOTICE", MB_OK);
}
void CheckMenuDraw(HWND hWnd, UINT MenuItemID) { // Huỳnh Thanh Bình
	HMENU hMenu = GetSubMenu(GetMenu(hWnd), 1);

	for (UINT i = ID_DRAW_LINE; i <= ID_DRAW_SELECTOBJECT; ++i) {
		CheckMenuItem(hMenu, i, MF_UNCHECKED | MF_BYCOMMAND);
	} CheckMenuItem(hMenu, MenuItemID, MF_CHECKED | MF_BYCOMMAND);
}
void CheckToolbarDraw(HWND hWnd, UINT MenuItemID) {
	for (UINT i = ID_DRAW_LINE; i <= ID_DRAW_SELECTOBJECT; ++i) {
		SendMessage(hToolBarWnd, TB_SETSTATE, i, TBSTATE_ENABLED);
	} SendMessage(hToolBarWnd, TB_SETSTATE, MenuItemID, TBSTATE_ENABLED | TBSTATE_CHECKED);
}

// MDI
void initFrameWindow(HWND hWnd)
{
	hFrameWnd = hWnd;
	// create the MDI Client Window
	CLIENTCREATESTRUCT ccs;
	ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 3);
	ccs.idFirstChild = 50000;

	hwndMDIClient = CreateWindow(
		L"MDICLIENT",
		(LPCTSTR)NULL,
		WS_CHILD | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd,
		(HMENU)NULL,
		hInst,
		(LPVOID)&ccs);

	ShowWindow(hwndMDIClient, SW_SHOW);
}
void initChildWindow(HWND hWnd, int nType)
{
	CHILD_WND_DATA *wndData;
	wndData = (CHILD_WND_DATA*)VirtualAlloc(NULL, sizeof(CHILD_WND_DATA), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	//wndData = new CHILD_WND_DATA;
	wndData->wndType = nType;
	wndData->hWnd = hWnd;
	wndData->rgbColor = RGB(0, 0, 0);
	SetLastError(0);
	if (SetWindowLongPtr(hWnd, 0, (LONG_PTR)wndData) == 0)

		if (GetLastError() != 0)
		{
			//int a = 0;
		}

}
void onNewDrawWnd(HWND hWnd)
{
	static int i = 1;
	wsprintf(szDrawTitle, L"Noname-%d.drw", i);
	MDICREATESTRUCT mdiCreate;
	ZeroMemory(&mdiCreate, sizeof(MDICREATESTRUCT));
	mdiCreate.szClass = szDrawWindowClass;
	mdiCreate.szTitle = szDrawTitle;
	mdiCreate.x = CW_USEDEFAULT;
	mdiCreate.y = CW_USEDEFAULT;
	mdiCreate.cx = CW_USEDEFAULT;
	mdiCreate.cy = CW_USEDEFAULT;
	mdiCreate.style = 0;
	mdiCreate.lParam = NULL;
	SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiCreate);
	i++;
}

// Toolbar
// define new buttons
// 1st: ID của bitmap (có sẵn) / số thứ tự trong mảng (bitmap add thêm)
// 2nd: ID Menu Item
// 3rd: state trạng thái : enable, disable,...
// 4th: kiểu của item: button, seperator, ...
// 5th: 0
// 6th: 0
void createToolbar(HWND hWnd)
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

	CheckMenuItem(GetMenu(hWnd), ID_TOOLBAR_VIEWHIDE, MF_CHECKED | MF_BYCOMMAND);
	Toolbar_Exist = true;
}
void ToolbarNotifyHandle(LPARAM	lParam)
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
void ToolbarStyle(int tbStyle)
{
	ShowWindow(hToolBarWnd, SW_HIDE);
	SendMessage(hToolBarWnd, TB_SETSTYLE, (WPARAM)0, (LPARAM)(DWORD)tbStyle | CCS_TOP);
	ShowWindow(hToolBarWnd, SW_SHOW);
}
void viewToolbar(HWND hWnd)
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

	CheckMenuItem(GetMenu(hWnd), ID_TOOLBAR_VIEWHIDE, vFlag | MF_BYCOMMAND);
}
void addEditToolbar()
{
	static bool exist = false;
	if (exist == FALSE && Toolbar_Exist == TRUE) {
		TBBUTTON tbButtons[] =
		{
			{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
			{ STD_CUT, NULL/*ID_EDIT_CUT*/, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_COPY,	NULL/*ID_EDIT_COPY*/, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_PASTE, NULL/*ID_EDIT_PASTE*/,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ STD_DELETE, NULL/*ID_EDIT_DELETE*/, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
		};

		SendMessage(hToolBarWnd, TB_ADDBUTTONS,
			(WPARAM) sizeof(tbButtons) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&tbButtons);

		exist = true;
	}
}
void addFontsNColors()
{
	static bool exist = false;
	if (exist == FALSE && Toolbar_Exist == TRUE) {
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
void addDrawToolBar() {
	static bool exist = false;
	if (exist == FALSE && Toolbar_Exist == TRUE) {
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
void OnChooseColors(HWND hWnd) {
	CHOOSECOLOR cc; // CTDL dùng cho dialog ChooseColor
	COLORREF acrCustClr[16]; // Các màu do user định nghĩa
	DWORD rgbCurrent = RGB(255, 0, 0); // màu được chọn default
									   // Khởi tạo struct
	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd; // handle của window cha
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent; // trả về màu được chọn
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	if (ChooseColor(&cc))
	{
		// xử lý màu được chọn, vd. tạo brush
		HBRUSH hbrush;
		hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult;
	}
	else
		;//ErrorHandler();
}
void OnChooseFonts(HWND hWnd) {
	CHOOSEFONT cf; // CTDL dùng cho dialog ChooseFont
	LOGFONT lf; // CTDL font, lưu kết quả font được chọn
	/*HFONT hfNew, hfOld;*/


	// Khởi tạo struct
	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd; // handle của window cha
	cf.lpLogFont = &lf;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
	if (ChooseFont(&cf)) {
		// Xử lý font được chọn, vd. tạo font handle, dùng để
		/*TextOut
		hfNew = CreateFontIndirect(cf.lpLogFont);
		hfOld = SelectObject(hdc, hfNew);
		rgbPrev = SetTextColor(hdc, cf.rgbColors);
		TextOut(hdc, 50, 50,
			“This text uses selected font and color”, 38);
		……*/
	}
	else
		;//ErrorHandler();
}