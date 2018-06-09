// 1653006_MyPaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1653006_MyPaint.h"
#include <CommCtrl.h>

#define MAX_LOADSTRING		100
#define ID_TOOLBAR			1000	// ID of the toolbar
#define IMAGE_WIDTH			18
#define IMAGE_HEIGHT		17
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
HWND  hToolBarWnd;
HWND hwndMDIClient = NULL;
//COLORREF rgbCurrentColor = RGB(0, 0, 0);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
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

bool Toolbar_Exist = false;
void doCreate_ToolBar(HWND hWnd);
void doToolBar_NotifyHandle(LPARAM	lParam);
void doToolBar_AddSTDButton();
void doToolBar_AddUserButton();
void doToolBar_Style(int tbStyle);
void doView_ToolBar(HWND hWnd);

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653006MYPAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1653006MYPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	// Draw child window
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= DrawWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 8;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653006MYPAINT));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName  = szDrawWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		initFrameWindow(hWnd);
		doCreate_ToolBar(hWnd);
		return 0;
	case WM_COMMAND:
		onCommand(hWnd, message, wParam, lParam);
		break;
	case WM_NOTIFY:
		doToolBar_NotifyHandle(lParam);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_SIZE:
		UINT w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hwndMDIClient, 0, 28, w, h, TRUE);
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
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

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
		break;
	case ID_DRAW_RECTANGLE:
		CheckMenuDraw(hWnd, ID_DRAW_RECTANGLE);
		break;
	case ID_DRAW_ELLIPSE:
		CheckMenuDraw(hWnd, ID_DRAW_ELLIPSE);
		break;
	case ID_DRAW_TEXT:
		CheckMenuDraw(hWnd, ID_DRAW_TEXT);
		break;
	case ID_DRAW_SELECTOBJECT:
		CheckMenuDraw(hWnd, ID_DRAW_SELECTOBJECT);
		break;
	/*case ID_TOOLBAR_CREATE:
		doCreate_ToolBar(hWnd);
		break;*/
	case ID_TOOLBAR_ADDSTDBUTTON:
		doToolBar_AddSTDButton();
		break;
	case ID_TOOLBAR_ADDUSERBUTTON:
		doToolBar_AddUserButton();
		break;
	case ID_TOOLBAR_FLAT:
	{
		doToolBar_Style(TBSTYLE_FLAT);
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
		doToolBar_Style(TBSTYLE_TRANSPARENT);
		break;
	}
	case ID_TOOLBAR_VIEWHIDE:
		doView_ToolBar(hWnd);
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
void doCreate_ToolBar(HWND hWnd)
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
void doToolBar_NotifyHandle(LPARAM	lParam)
{
	LPTOOLTIPTEXT   lpToolTipText;
	TCHAR			szToolTipText[TOOL_TIP_MAX_LEN]; 	// ToolTipText, loaded from Stringtable resource

														// lParam: address of TOOLTIPTEXT struct
	lpToolTipText = (LPTOOLTIPTEXT)lParam;

	if (lpToolTipText->hdr.code == TTN_NEEDTEXT)
	{
		// hdr.iFrom: ID cua ToolBar button -> ID cua ToolTipText string
		LoadString(hInst, lpToolTipText->hdr.idFrom, szToolTipText, TOOL_TIP_MAX_LEN);

		lpToolTipText->lpszText = szToolTipText;
	}
}
void doToolBar_AddSTDButton()
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
void doToolBar_AddUserButton()
{
	static bool exist = false;
	if (exist == FALSE && Toolbar_Exist == TRUE) {
		// define new buttons
		TBBUTTON tbButtons[] =
		{
			// 1st: ID của bitmap (có sẵn) / số thứ tự trong mảng (bitmap add thêm)
			// 2nd: ID Menu Item
			// 3rd: state trạng thái : enable, disable,...
			// 4th: kiểu của item: button, seperator, ...
			// 5th: 0
			// 6th: 0
			{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // seperator {0,0,x,y,0,0}
			{ 0, IDM_ABOUT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 1, IDM_EXIT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
			{ 2, ID_DRAW_LINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0,0},
			{ 3, ID_DRAW_ELLIPSE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0,0},
			{ 4, ID_DRAW_RECTANGLE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0,0 },
			{ 5, ID_DRAW_SELECTOBJECT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0,0 },
			{ 6, ID_DRAW_TEXT          , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0,0 },
		};

		// structure contains the bitmap of user defined buttons. It contains 2 icons
		TBADDBITMAP	tbBitmap0 = { hInst, IDB_ABOUT_EXIT };
		TBADDBITMAP	tbBitmap1 = { hInst, IDB_LINE };
		TBADDBITMAP tbBitmap2 = { hInst, IDB_CIRCLE };
		TBADDBITMAP tbBitmap3 = { hInst, IDB_RECT_SELECT_TEXT };

		WCHAR msg[20];

		//// Add bitmap to Image-list of ToolBar
		int idx0 = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap0) / sizeof(TBADDBITMAP),
			(LPARAM)(LPTBADDBITMAP)&tbBitmap0); wsprintf(msg, L"idx0 = %d\n", idx0); OutputDebugString(msg);

		int idx1 = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap1) / sizeof(TBADDBITMAP),
			(LPARAM)(LPTBADDBITMAP)&tbBitmap1); wsprintf(msg, L"idx1 = %d\n", idx1); OutputDebugString(msg);

		int idx2 = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap2) / sizeof(TBADDBITMAP),
			(LPARAM)(LPTBADDBITMAP)&tbBitmap2); wsprintf(msg, L"idx2 = %d\n", idx2); OutputDebugString(msg);

		int idx3 = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap3) / sizeof(TBADDBITMAP),
			(LPARAM)(LPTBADDBITMAP)&tbBitmap3); wsprintf(msg, L"idx2 = %d\n", idx3); OutputDebugString(msg);

		
		//// identify the bitmap index of each button
		wsprintf(msg, L"%d\n", tbButtons[0].iBitmap); OutputDebugString(msg);
		tbButtons[0].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[0].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[1].iBitmap); OutputDebugString(msg);
		tbButtons[1].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[1].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[2].iBitmap); OutputDebugString(msg);
		tbButtons[2].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[2].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[3].iBitmap); OutputDebugString(msg);
		tbButtons[3].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[3].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[4].iBitmap); OutputDebugString(msg);
		tbButtons[4].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[4].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[5].iBitmap); OutputDebugString(msg);
		tbButtons[5].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[5].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[6].iBitmap); OutputDebugString(msg);
		tbButtons[6].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[6].iBitmap); OutputDebugString(msg);


		wsprintf(msg, L"%d\n", tbButtons[7].iBitmap); OutputDebugString(msg);
		tbButtons[7].iBitmap += idx0;
		wsprintf(msg, L"%d\n", tbButtons[7].iBitmap); OutputDebugString(msg);


		// add buttons to toolbar
		SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(tbButtons) / sizeof(TBBUTTON),
			(LPARAM)(LPTBBUTTON)&tbButtons);

		exist = true;
	}
}
void doToolBar_Style(int tbStyle)
{
	ShowWindow(hToolBarWnd, SW_HIDE);
	SendMessage(hToolBarWnd, TB_SETSTYLE, (WPARAM)0, (LPARAM)(DWORD)tbStyle | CCS_TOP);
	ShowWindow(hToolBarWnd, SW_SHOW);
}
void doView_ToolBar(HWND hWnd)
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