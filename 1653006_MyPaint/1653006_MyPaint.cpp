// 1653006_MyPaint.cpp : Defines the entry point for the application.
// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#define _CRT_SECURE_DEPRECATE_MEMORY

#include "stdafx.h"
#include <shellapi.h> // Command Line Parameters Library
#include "1653006_MyPaint.h"
#include "1653006_MyObject.h"
#include "1653006_MyToolbar.h"

//#define IDT_TIMER 1653006

// Global Variables:
HINSTANCE hInst;	// current instance

WCHAR szTitle[MAX_LOADSTRING];                      // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];                // the main window class name
WCHAR szDrawWindowClass[MAX_LOADSTRING] = L"Draw";	// class draw
WCHAR szDrawTitle[MAX_LOADSTRING];					// Title for draw

HWND hFrameWnd;
HWND hToolBarWnd;
HWND hEdit = NULL;
HWND hwndMDIClient = NULL;
HWND hColorbar = NULL;
HWND hStatusbar = NULL;

HCURSOR cross = LoadCursor(hInst, IDC_CROSS);
HCURSOR arrow = LoadCursor(hInst, IDC_ARROW);
HCURSOR nesw  = LoadCursor(hInst, IDC_SIZENESW);
HCURSOR nwse  = LoadCursor(hInst, IDC_SIZENWSE);
HCURSOR sall  = LoadCursor(hInst, IDC_SIZEALL);

LPWSTR *szArgList = NULL;

int nArg   = 0;
int nChild = 0;   // number of child window
int wMode  = CASCADE;
int mode   = LINE;// default draw mode is LINE 
int sMode  = -1;  // select mode (check whether mode = RESIZE)
int i      = -1;  // Object[i] is being selected
int prev_i = -1;  // move Object mode select

// Status bar:
WCHAR currentChild[100];
RECT  currentRect;
POINT currentPoint;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	szArgList = CommandLineToArgvW(GetCommandLine(), &nArg);

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
	
	//LocalFree(szArgList);
	GlobalFree(szArgList);
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
	wcex.hCursor        = NULL;
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

   RECT rect;
   GetWindowRect(GetDesktopWindow(), &rect);

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      rect.right / 2 - 500, rect.bottom / 2 - 360, 1000, 720, nullptr, nullptr, hInstance, nullptr);

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
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDOK));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // lấy 2 byte thấp của WordParam --> cho biết ID của control;
		case IDOK:
			EndDialog(hDlg, NULL);
			break;
		case IDCLOSE: // Remove close button !!!
					  //In the dialog resource editor, set the "System menu" property to False.
			break;
		}
		return (INT_PTR)TRUE;
	} return (INT_PTR)FALSE;
}
INT_PTR CALLBACK AboutMeDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDOK));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // lấy 2 byte thấp của WordParam --> cho biết ID của control;
		case IDOK:
			EndDialog(hDlg, NULL);
			break;
		case IDCLOSE: // Remove close button !!!
					  //In the dialog resource editor, set the "System menu" property to False.
			break;
		}
		return (INT_PTR)TRUE;
	} return (INT_PTR)FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  window = 0;
	static bool Toolbar_Exist = false;
	switch (message)
	{
	case WM_CREATE: 
		onCreate(hWnd, Toolbar_Exist);
		return 0;
	case WM_COMMAND:
		onCommand(hWnd, message, wParam, lParam, Toolbar_Exist);
		break;
	case WM_NOTIFY:
		ToolbarNotifyHandle(hInst, lParam);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_SIZE: { // Update the size of MDI client window
		UINT w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);

		int vFlag = GetMenuState(GetMenu(hWnd), ID_TOOLBAR_VIEWHIDE, MF_BYCOMMAND) & MF_CHECKED;
		int cFlag = GetMenuState(GetMenu(hWnd), ID_TOOLBAR_COLORBAR, MF_BYCOMMAND) & MF_CHECKED;

		if (vFlag) { // Show Toolbar 
			if (cFlag) { // Show Toolbar, Show Colorbar
				MoveWindow(hToolBarWnd, 28, 2, w - 28, h - 2, TRUE);
				MoveWindow(hwndMDIClient, 28, 28, w - 28, h - 50, TRUE);
			}
			else { // Show Toolbar, Hide Colorbar
				MoveWindow(hToolBarWnd, 0, 2, w, h - 2, TRUE);
				MoveWindow(hwndMDIClient, 0, 28, w, h - 50, TRUE);
			}
		}
		else { // Hide Toolbar
			if (cFlag) { // Hide Toolbar, Show Colorbar
				MoveWindow(hToolBarWnd, 28, 0, w - 28, h, TRUE);
				MoveWindow(hwndMDIClient, 28, 0, w - 28, h - 22, TRUE);
			}
			else { // Hide Toolbar, Hide Colorbar
				MoveWindow(hToolBarWnd, 0, 0, w, h, TRUE);
				MoveWindow(hwndMDIClient, 0, 0, w, h - 22, TRUE);
			}
		}


		OnStatusbarSize(hWnd, w);

		i = -1; prev_i = -1;
	} break;
	case WM_CLOSE: {
		TCHAR msg[128] = L"You are about to close MyPaint. Are you sure ? :( \n";
		if (MessageBox(hWnd, msg, L"EXIT NOTICE !!!", MB_YESNO | MB_ICONASTERISK) == IDYES) {
			DestroyWindow(hWnd);
		} return 0;
	}
	case WM_GETMINMAXINFO: {
		MINMAXINFO *p = (MINMAXINFO*)lParam;
		p->ptMinTrackSize.x = 850;
		p->ptMinTrackSize.y = 700;
		//p->ptMaxTrackSize.x = bmpObj.bmWidth + 20;
		//p->ptMaxTrackSize.y = bmpObj.bmHeight + 60;
	} break;
	case WM_DESTROY:
		DeleteObject(cross);
		DeleteObject(arrow);
		DeleteObject(nesw);
		DeleteObject(nwse);
		DeleteObject(sall);

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
		SetFocus(GetDlgItem(hDlg, IDOK));
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_DEMO) 
		{
			ShellExecute(
				NULL, L"open", 
				L"www.youtube.com/watch?v=LrWAlX8KABo", 
				NULL, NULL, SW_SHOWNORMAL);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
LRESULT CALLBACK DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static Position pos;
	static bool     exist = false;
	static bool     mouse_down = false;
	static HWND     activated = NULL;
	static HWND     deactivated = NULL;

	switch (message) {
	case WM_MDIACTIVATE: {
		activated = (HWND)lParam;
		deactivated = (HWND)wParam;
		InvalidateRect(deactivated, NULL, TRUE);
		i = -1;
		sMode = -1;
		prev_i = -1;

		if (nChild > 0) {
			WCHAR temp[100];
			WCHAR str[128];
			wcscpy(str, L"Child Window Active:    ");
			GetWindowText(activated, temp, 100); 
			wcscpy(str, wcscat(str, temp));
			SendMessage(hStatusbar, SB_SETTEXT, 0, (LPARAM)str);
			GetClientRect(hWnd, &currentRect);
			wsprintf(str, L"Page Size:    %d x %d", currentRect.right - 1, currentRect.bottom - 1);
			SendMessage(hStatusbar, SB_SETTEXT, 1 | SBT_POPOUT, (LPARAM)str);
		}
		else {
			SendMessage(hStatusbar, SB_SETTEXT, 0, (LPARAM)L"Child Window Active:    ");
			SendMessage(hStatusbar, SB_SETTEXT, 1 | SBT_POPOUT, (LPARAM)L"Page Size:    0 x 0");
			SendMessage(hStatusbar, SB_SETTEXT, 2 | SBT_POPOUT, (LPARAM)L"x =    ");
			SendMessage(hStatusbar, SB_SETTEXT, 3 | SBT_POPOUT, (LPARAM)L"y =    ");
		}

		if (activated != 0) checkUndoRedo(hFrameWnd, activated, hToolBarWnd);
	}	break;
	case WM_CREATE: {
		//SetTimer(hWnd,             // handle to main window 
		//	IDT_TIMER,             // timer identifier 
		//	1,                   // 0.1-second interval 
		//	(TIMERPROC)NULL);      // no timer callback 

		if (nChild == 0) enableCommand(hFrameWnd, hToolBarWnd, mode);

		nChild++;
		initChildWindow(hWnd, 0);
		ZeroMemory(&pos, sizeof(pos)); // Init pos !!!! vital !!!!
		exist = true;

		checkUndoRedo(hFrameWnd, hWnd, hToolBarWnd);
	}	break;
	case WM_DESTROY:
		nChild--;

		if (nChild == 0) {
			SendMessage(hStatusbar, SB_SETTEXT, 0, (LPARAM)L"Child Window Active:    ");
			SendMessage(hStatusbar, SB_SETTEXT, 1 | SBT_POPOUT, (LPARAM)L"Page Size:  0 x 0");
			SendMessage(hStatusbar, SB_SETTEXT, 2 | SBT_POPOUT, (LPARAM)L"x =    ");
			SendMessage(hStatusbar, SB_SETTEXT, 3 | SBT_POPOUT, (LPARAM)L"y =    ");

			disableCommand(hFrameWnd, hToolBarWnd);
		}

		clearObjArray(hWnd);

		//KillTimer(hWnd, IDT_TIMER);
		break;
	case WM_SIZE:
		i = -1; prev_i = -1;

		WCHAR str[128];
		GetClientRect(hWnd, &currentRect);
		wsprintf(str, L"Page Size:    %d x %d", currentRect.right - 1, currentRect.bottom - 1);
		SendMessage(hStatusbar, SB_SETTEXT, 1 | SBT_POPOUT, (LPARAM)str);
		break;
	case WM_CLOSE: {
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);

		if (data->saved == false) {
			TCHAR msg[128] = L"You haven't saved your current drawing !\nDo you want to save it ?\n";
			if (MessageBox(hWnd, msg, L"SAVING NOTICE !!!", MB_YESNO | MB_ICONASTERISK) == IDYES) {
				if (OnSave(hFrameWnd, hwndMDIClient)) 
					DestroyWindow(hWnd);
				else return 0;
			} 
			else {
				DestroyWindow(hWnd);
			}
			return 0;
		}
	} break;
	case WM_PAINT: 
		OnPaint(hWnd);
		break;
	case WM_LBUTTONDOWN: {
		OnLButtonDown(hWnd, hEdit, lParam, pos, mode, mouse_down, i, sMode);
	} break;
	case WM_MOUSEMOVE: {
		if (mode != SELECT)
			OnMouseMove(hWnd, wParam, lParam, pos, mode, mouse_down, i);
		else
			mousemoveObject(hWnd, activated, lParam, pos, mouse_down, i, prev_i, sMode);

		currentPoint.x = LOWORD(lParam);
		currentPoint.y = HIWORD(lParam);

		WCHAR str[128];
		wsprintf(str, L"x =    %d", currentPoint.x);
		SendMessage(hStatusbar, SB_SETTEXT, 2 | SBT_POPOUT, (LPARAM)str);
		wsprintf(str, L"y =    %d", currentPoint.y);
		SendMessage(hStatusbar, SB_SETTEXT, 3 | SBT_POPOUT, (LPARAM)str);

	}	break;
	case WM_LBUTTONUP: {
		OnLButtonUp(hInst, hEdit, hWnd, pos, mode, mouse_down);
		checkUndoRedo(hFrameWnd, hWnd, hToolBarWnd);

		if (mode == SELECT && prev_i != -1) {
			CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
			drawFrame(hWnd, data, prev_i);
		} prev_i = -1; 

		if (sMode > 0) sMode = -1; // change cursor to arrow 
	} break;
	case WM_CTLCOLOREDIT: {
		CHILD_WND_DATA* data = (CHILD_WND_DATA*)GetWindowLongPtr(hWnd, 0);
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, data->rgbColor);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
	} break;
	case WM_SETCURSOR: {
		if (LOWORD(lParam) == HTCLIENT) {
			if (mode != SELECT) SetCursor(cross);
			else {
				switch (sMode) {
				case MOVE:
					SetCursor(sall); break;
				case RESIZE_1:
					SetCursor(nwse); break;
				case RESIZE_2:
					SetCursor(nesw); break;
				case RESIZE_3:
					SetCursor(nesw); break;
				case RESIZE_4:
					SetCursor(nwse); break;
				default: 
					SetCursor(arrow); break;
				}
			}               
		}
	} break;
	case WM_TIMER:
		//switch (wParam) {
		//case IDT_TIMER:
		//	//InvalidateRect(hWnd, NULL, FALSE);
		//	//UpdateWindow(hWnd);
		//	return 0;
		//}
		break;

	case WM_ERASEBKGND:
		return 1;
		break;

	default: return DefMDIChildProc(hWnd, message, wParam, lParam);
	} return DefMDIChildProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK MDICloseProc(HWND hChildwnd, LPARAM lParam)
{
	SendMessage(hwndMDIClient, WM_MDIDESTROY, (WPARAM)hChildwnd, 0l);
	return 1;
}


void onCreate(HWND hWnd, bool& Toolbar_Exist) {
	DialogBox(hInst, MAKEINTRESOURCE(IDD_WELCOME), hWnd, WelcomeDlgProc);
	initFrameWindow(hWnd, hFrameWnd, hwndMDIClient, hInst);

	createColorbar(hInst, hWnd, hColorbar);

	createToolbar(hWnd, hToolBarWnd, Toolbar_Exist);
	addEditToolbar(hToolBarWnd, Toolbar_Exist);
	addDrawToolBar(hInst, hToolBarWnd, Toolbar_Exist);
	addFontsNColors(hInst, hToolBarWnd, Toolbar_Exist);
	addWindowlBar(hInst, hToolBarWnd, Toolbar_Exist);

	wcscpy(currentChild, L"");
	currentRect.right = 0;
	currentRect.bottom = 0;
	currentPoint.x = 0;
	currentPoint.y = 0;
	
	OnCreateStatusbar(hInst, hWnd, hStatusbar);

	disableCommand(hFrameWnd, hToolBarWnd);

	HMENU hMenu = GetSubMenu(GetMenu(hWnd), menuPos_Toolbar);
	CheckMenuItem(hMenu, ID_TOOLBAR_FLAT, MF_CHECKED | MF_BYCOMMAND);
	CheckMenuItem(hMenu, ID_TOOLBAR_EDITTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
	CheckMenuItem(hMenu, ID_TOOLBAR_DRAWTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
	CheckMenuItem(hMenu, ID_TOOLBAR_FONTS_COLORS, MF_CHECKED | MF_BYCOMMAND);
	CheckMenuItem(hMenu, ID_TOOLBAR_COLORBAR, MF_CHECKED | MF_BYCOMMAND);

	hMenu = GetSubMenu(GetMenu(hWnd), menuPos_Window);
	CheckMenuItem(hMenu, ID_WINDOW_CASCADE, MF_CHECKED | MF_BYCOMMAND);

	if (szArgList != NULL) {
		for (int i = 0; i < nArg; i++) {
			if ((bool)wcsstr(szArgList[i], L".drw")) {
				vector <Object*> arrObject;
				WCHAR FileTitle[MAX_LOADSTRING];
				openFile(arrObject, szArgList[i]);
				onNewDrawWnd(hWnd, hwndMDIClient, szDrawTitle, szDrawWindowClass);
				GetFileTitle(szArgList[i], FileTitle, (WORD)wcslen(FileTitle));
				HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
				SetWindowText(current, FileTitle);
				CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
				data->arrObject = arrObject;
				arrObject.clear();

				data->saved = true;
				data->exist = true;
				wcscpy(data->path, szArgList[i]);

				WCHAR str[128];
				wcscpy(str, L"Child Window Active:    ");
				wcscpy(str, wcscat(str, FileTitle));
				SendMessage(hStatusbar, SB_SETTEXT, 0, (LPARAM)str);
				break;
			}
		}
	}
}
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist)
{
	static bool mode_change = false;
	
	int wmId = LOWORD(wParam);
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		WndProc(hWnd, WM_CLOSE, wParam, lParam);
		break;
	case ID_FILE_NEW:
		onNewDrawWnd(hWnd, hwndMDIClient, szDrawTitle, szDrawWindowClass);
		break;
	case ID_FILE_OPEN: 
		OnOpen(hWnd, hwndMDIClient, szDrawTitle, szDrawWindowClass);
		break; 
	case ID_FILE_SAVE:
		OnSave(hWnd, hwndMDIClient);
		break;
	case ID_FILE_PRINT:
		OnPrint(hWnd, hwndMDIClient);
		break;
	case ID_EDIT_CUT:
		cutObject(hwndMDIClient, mode, i); sMode = -1;
		break;
	case ID_EDIT_COPY:
		copyObject(hwndMDIClient, mode, i);
		break;
	case ID_EDIT_PASTE: {
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		pasteObject(hwndMDIClient, mode, i); sMode = -1;
		checkUndoRedo(hFrameWnd, current, hToolBarWnd);
	}	break;
	case ID_EDIT_DELETE: 
		deleteObject(hwndMDIClient, mode, i); sMode = -1;
		break;
	case ID_EDIT_UNDO: {
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		doUndo(hwndMDIClient, mode); i = -1; sMode = -1;
		checkUndoRedo(hFrameWnd, current, hToolBarWnd);
	}	break;
	case ID_EDIT_REDO: {
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		doRedo(hwndMDIClient, mode); i = -1; sMode = -1;
		checkUndoRedo(hFrameWnd, current, hToolBarWnd);
	}	break;
	case ID_DRAW_LINE:
		changeMode(mode, LINE, ID_DRAW_LINE, hWnd, hToolBarWnd, hwndMDIClient, mode_change, i);
		break;
	case ID_DRAW_RECTANGLE:
		changeMode(mode, RECTANGLE, ID_DRAW_RECTANGLE, hWnd, hToolBarWnd, hwndMDIClient, mode_change, i);
		break;
	case ID_DRAW_ELLIPSE:
		changeMode(mode, ELLIPSE, ID_DRAW_ELLIPSE, hWnd, hToolBarWnd, hwndMDIClient, mode_change, i);
		break;
	case ID_DRAW_TEXT:
		changeMode(mode, INSERTTEXT, ID_DRAW_TEXT, hWnd, hToolBarWnd, hwndMDIClient, mode_change, i);
		break;
	case ID_DRAW_SELECTOBJECT:
		changeMode(mode, SELECT, ID_DRAW_SELECTOBJECT, hWnd, hToolBarWnd, hwndMDIClient, mode_change, i);
		break;
	case ID_DRAW_FONT:
		OnChooseFonts(hWnd, hwndMDIClient);
		break;
	case ID_DRAW_COLOR:
		OnChooseColors(hWnd, hwndMDIClient);
		break;
	/*case ID_TOOLBAR_CREATE:
		doCreate_ToolBar(hWnd);
		break;*/
	case ID_TOOLBAR_EDITTOOLBAR:
		addEditToolbar(hToolBarWnd, Toolbar_Exist);
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), menuPos_Toolbar), ID_TOOLBAR_EDITTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_FONTS_COLORS:
		addFontsNColors(hInst, hToolBarWnd, Toolbar_Exist);
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), menuPos_Toolbar), ID_TOOLBAR_FONTS_COLORS, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_DRAWTOOLBAR:
		addDrawToolBar(hInst, hToolBarWnd, Toolbar_Exist);
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), menuPos_Toolbar), ID_TOOLBAR_DRAWTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_FLAT:
		changeToolbarStye(hWnd, hToolBarWnd, TBSTYLE_FLAT);
		break;
	case ID_TOOLBAR_TRANSPARENT:
		changeToolbarStye(hWnd, hToolBarWnd, TBSTYLE_TRANSPARENT);
		break;
	case ID_TOOLBAR_VIEWHIDE:
		viewToolbar(hWnd, hwndMDIClient, hToolBarWnd, hColorbar);
		InvalidateRect(hwndMDIClient, NULL, TRUE); 
		break;
	case ID_TOOLBAR_COLORBAR:
		viewColorbar(hWnd, hwndMDIClient, hToolBarWnd, hColorbar);
		InvalidateRect(hwndMDIClient, NULL, TRUE); 
		break;
	case ID_WINDOW_HORIZONTAL:
		SendMessage(hwndMDIClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);
		CheckMenuWindow(hWnd, ID_WINDOW_HORIZONTAL);
		CheckToolbarWindow(hToolBarWnd, ID_WINDOW_HORIZONTAL);
		wMode = HORIZONTAL;
		break;
	case ID_WINDOW_VERTICAL:
		SendMessage(hwndMDIClient, WM_MDITILE, MDITILE_VERTICAL, 0);
		CheckMenuWindow(hWnd, ID_WINDOW_VERTICAL);
		CheckToolbarWindow(hToolBarWnd, ID_WINDOW_VERTICAL);
		wMode = VERTICAL;
		break;
	case ID_WINDOW_CASCADE:
		SendMessage(hwndMDIClient, WM_MDICASCADE, 0, 0);
		CheckMenuWindow(hWnd, ID_WINDOW_CASCADE);
		CheckToolbarWindow(hToolBarWnd, ID_WINDOW_CASCADE);
		wMode = CASCADE;
		break;
	case ID_WINDOW_CLOSEALL:
		EnumChildWindows(hwndMDIClient, (WNDENUMPROC)MDICloseProc, 0L);
		break;
	case ID_COLOR_1: // 255,0,0
		changeColor(hwndMDIClient, 255, 0, 0);
		break;
	case ID_COLOR_2: // 255,0,255
		changeColor(hwndMDIClient, 255, 0, 255);
		break;
	case ID_COLOR_3: // 255,102,0
		changeColor(hwndMDIClient, 255, 102, 0);
		break;
	case ID_COLOR_4: // 255,204,153
		changeColor(hwndMDIClient, 255, 204, 153);
		break;
	case ID_COLOR_5: // 255,255,0
		changeColor(hwndMDIClient, 255, 255, 0);
		break;
	case ID_COLOR_6: // 153,255,153
		changeColor(hwndMDIClient, 153, 255, 153);
		break;
	case ID_COLOR_7: // 51,204,0
		changeColor(hwndMDIClient, 51, 204, 0);
		break;
	case ID_COLOR_8: // 0,102,51
		changeColor(hwndMDIClient, 0, 102, 51);
		break;
	case ID_COLOR_9: // 0,0,204
		changeColor(hwndMDIClient, 0, 0, 204);
		break;
	case ID_COLOR_10: // 0,0,51
		changeColor(hwndMDIClient, 0, 0, 51);
		break;
	case ID_COLOR_11: // 51,0,102
		changeColor(hwndMDIClient, 51, 0, 102);
		break;
	case ID_COLOR_12: // 102,51,153
		changeColor(hwndMDIClient, 102, 51, 153);
		break;
	case ID_COLOR_13: // 102,0,153
		changeColor(hwndMDIClient, 102, 0, 153);
		break;
	case ID_COLOR_14: // 153,153,255
		changeColor(hwndMDIClient, 153, 153, 255);
		break;
	case ID_COLOR_15: // 164,164,164
		changeColor(hwndMDIClient, 164, 164, 164);
		break;
	case ID_COLOR_16: // 140,140,140
		changeColor(hwndMDIClient, 140, 140, 140);
		break;
	case ID_COLOR_17: // 85,85,85
		changeColor(hwndMDIClient, 85, 85, 85);
		break;
	case ID_COLOR_18: // 41,41,41
		changeColor(hwndMDIClient, 41, 41, 41);
		break;
	case ID_COLOR_19: // 0,0,0
		changeColor(hwndMDIClient, 0, 0, 0);
		break;
	case ID_COLOR_20: // 255,255,255
		changeColor(hwndMDIClient, 255, 255, 255);
		break;
	case ID_HELP_ABOUTME:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTME), hWnd, AboutMeDlgProc);
		break;
	default:
		DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
	}
}
