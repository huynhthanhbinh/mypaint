// 1653006_MyPaint.cpp : Defines the entry point for the application.
// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#include "stdafx.h"
#include "1653006_MyPaint.h"
#include "1653006_MyObject.h"
#include "1653006_MyToolbar.h"

// Global Variables:
int mode = LINE;

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

WCHAR szDrawWindowClass[MAX_LOADSTRING] = L"Draw";	// class draw
WCHAR szDrawTitle[MAX_LOADSTRING];					// Title for draw

HWND hFrameWnd;
HWND hToolBarWnd;
HWND hwndMDIClient = NULL;


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
	wcex.hCursor		= LoadCursor(nullptr, IDC_CROSS);
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
	case WM_CREATE: {
		DialogBox(hInst, MAKEINTRESOURCE(IDD_WELCOME), hWnd, WelcomeDlgProc);
		initFrameWindow(hWnd);
		createToolbar(hWnd, hToolBarWnd, Toolbar_Exist);
		addDrawToolBar(hInst, hToolBarWnd, Toolbar_Exist);
		addFontsNColors(hInst, hToolBarWnd, Toolbar_Exist);
		HMENU hMenu = GetSubMenu(GetMenu(hWnd), 2);
		CheckMenuItem(hMenu, ID_TOOLBAR_DRAWTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		CheckMenuItem(hMenu, ID_TOOLBAR_FONTS_COLORS, MF_CHECKED | MF_BYCOMMAND);
		return 0;
	}
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
	case WM_SIZE: // Update the size of MDI client window
		UINT w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hwndMDIClient, 0, 28, w, h - 28, TRUE);
		break;
	case WM_CLOSE: {
		TCHAR msg[128] = L"Ban co chac muon thoat khoi ung dung khong ?\n";
		if (MessageBox(hWnd, msg, L"EXIT NOTICE !!!", MB_YESNO) == IDYES) {
			DestroyWindow(hWnd);
		} return 0;
	}
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
LRESULT CALLBACK DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static Position pos;
	static bool exist = false;

	switch (message)
	{
	case WM_CREATE:
		initChildWindow(hWnd, 0);
		exist = true;
		break;
	case WM_DESTROY:
		clearObjArray(hWnd);
		break;
	case WM_CLOSE:
		break;
	case WM_SIZE:
		break;
	case WM_PAINT: 
		OnPaint(hWnd);
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(hWnd, lParam, pos);
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(hWnd, wParam, lParam, pos, mode);
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(pos, hWnd, mode);
		break;

	default: return DefMDIChildProc(hWnd, message, wParam, lParam);
	} return DefMDIChildProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK MDICloseProc(HWND hChildwnd, LPARAM lParam)
{
	SendMessage(hwndMDIClient, WM_MDIDESTROY, (WPARAM)hChildwnd, 0l);
	return 1;
}



void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist)
{
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
		onNewDrawWnd(hWnd);
		break;
	case ID_FILE_OPEN: {
		vector <Object*> arrObject;
		OnOpen(hWnd, arrObject);
		onNewDrawWnd(hWnd);
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		CHILD_WND_DATA * wndData = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
		wndData->arrObject = arrObject;
		arrObject.clear();
		//SendMessage(current, WM_PAINT, NULL, NULL);
		break;
	}
	case ID_FILE_SAVE:
		OnSave(hWnd);
		break;
	case ID_DRAW_LINE:
		mode = LINE;
		CheckMenuDraw(hWnd, ID_DRAW_LINE); 
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_LINE);
		//ShowNotice(hWnd, L"Draw Line");
		break;
	case ID_DRAW_RECTANGLE:
		mode = RECTANGLE;
		CheckMenuDraw(hWnd, ID_DRAW_RECTANGLE);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_RECTANGLE);
		//ShowNotice(hWnd, L"Draw Rectangle");
		break;
	case ID_DRAW_ELLIPSE:
		mode = ELLIPSE;
		CheckMenuDraw(hWnd, ID_DRAW_ELLIPSE);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_ELLIPSE);
		//ShowNotice(hWnd, L"Draw Ellipse");
		break;
	case ID_DRAW_TEXT:
		mode = INSERTTEXT;
		CheckMenuDraw(hWnd, ID_DRAW_TEXT);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_TEXT);
		//ShowNotice(hWnd, L"Insert Text");
		break;
	case ID_DRAW_SELECTOBJECT:
		mode = SELECT;
		CheckMenuDraw(hWnd, ID_DRAW_SELECTOBJECT);
		CheckToolbarDraw(hToolBarWnd, ID_DRAW_SELECTOBJECT);
		//ShowNotice(hWnd, L"Select Object");
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
		addEditToolbar(hToolBarWnd, Toolbar_Exist);
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_TOOLBAR_EDITTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_FONTS_COLORS:
		addFontsNColors(hInst, hToolBarWnd, Toolbar_Exist);
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_TOOLBAR_FONTS_COLORS, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_DRAWTOOLBAR:
		addDrawToolBar(hInst, hToolBarWnd, Toolbar_Exist);
		CheckMenuItem(GetSubMenu(GetMenu(hWnd), 2), ID_TOOLBAR_DRAWTOOLBAR, MF_CHECKED | MF_BYCOMMAND);
		break;
	case ID_TOOLBAR_FLAT:
	{
		ToolbarStyle(hToolBarWnd, TBSTYLE_FLAT);
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
		ToolbarStyle(hToolBarWnd, TBSTYLE_TRANSPARENT);
		break;
	}
	case ID_TOOLBAR_VIEWHIDE:
		viewToolbar(hWnd, hToolBarWnd);
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
	wndData = (CHILD_WND_DATA*)
		VirtualAlloc(NULL, sizeof(CHILD_WND_DATA), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	//wndData = new CHILD_WND_DATA;
	wndData->wndType = nType;
	wndData->hWnd = hWnd; 
	wndData->rgbColor = RGB(0, 0, 0);

	WCHAR s[100]; wsprintf(s, L"\n\n\nHWND = %d\n\n\n", wndData->hWnd); OutputDebugString(s);

	SetLastError(0);
	if (SetWindowLongPtr(hWnd, 0, (LONG_PTR)wndData) == 0)

		if (GetLastError() != 0)
		{
			//int a = 0;
		}

}


void OnChooseColors(HWND hWnd) {
	CHOOSECOLOR cc; // CTDL dùng cho dialog ChooseColor
	COLORREF acrCustClr[16]; // Các màu do user định nghĩa
	COLORREF rgbCurrent = RGB(255, 0, 0); // màu được chọn default
									   // Khởi tạo struct
	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd; // handle của window cha
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent; // trả về màu được chọn
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	if (ChooseColor(&cc))
	{
		//// xử lý màu được chọn, vd. tạo brush
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
		if (data != NULL) {
			data->rgbColor = cc.rgbResult;
		}
	} else ;//ErrorHandler();
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
void OnOpen(HWND hWnd, vector <Object*>& arrObject) {
	OPENFILENAME ofn; // CTDL dùng cho dialog open
	TCHAR szFile[256];
	TCHAR szFilter[] = TEXT("Draw file(.drw)\0 * .drw\0\0Text file(.txt)\0 * .txt\0");

	//HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);

	szFile[0] = '\0';
	// Khởi tạo struct
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; // handle của window cha
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile; // chuỗi tên file trả về
	ofn.nMaxFile = sizeof(szFile);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn)) {
		//... // xử lý mở file
		openFile(arrObject, ofn.lpstrFile);
	}
	else
		;//ErrorHandler();
}
void OnSave(HWND hWnd) {
	OPENFILENAME ofn; // CTDL dùng cho dialog save
	TCHAR szFile[256];
	TCHAR szFilter[] = TEXT("Draw file(.drw)\0 * .drw\0\0Text file(.txt)\0 * .txt\0");

	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);


	//szFile[0] = '\0';
	// Khởi tạo struct
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; // handle của window cha
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile; // chuỗi tên file trả về
	ofn.nMaxFile = sizeof(szFile);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"drw";
	//GetWindowText(current, szFile, MAX_LOADSTRING); // Get title of current child window
	//int x = GetFileTitle(ofn.lpstrFile, ofn.lpstrFileTitle, sizeof(ofn.lpstrFile));
	if (GetSaveFileName(&ofn)) {
		//... // xử lý lưu file
		//GetFileTitle(ofn.lpstrFile, ofn.lpstrFileTitle, /*(WORD)*/(sizeof(ofn.lpstrFile)));
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
		saveFile(data, ofn.lpstrFile);
	}
	else ;//ErrorHandler();
}
void saveFile(CHILD_WND_DATA* data, LPTSTR szFile) {
	fstream f;
	f.open(szFile, ios::trunc | ios::binary | ios::out);
	if (f.is_open()) {
		int arr_size = (int)data->arrObject.size();
		f.write((char*)&arr_size, sizeof(int));
		for (unsigned int i = 0; i < data->arrObject.size(); i++) {
			data->arrObject[i]->save(f);
		} 
	} f.close();
}
void openFile(vector <Object*>& arrObject, LPTSTR szFile) {
	fstream f;
	f.open(szFile, ios::binary | ios::in);
	if (f.is_open()) {
		int arr_size;
		f.read((char*)&arr_size, sizeof(int));
		for (int i = 0; i < arr_size; i++) {
			Object * obj; WCHAR s[MAX_LOADSTRING];
			int type;
			f.read((char*)&type, sizeof(int));

			switch (type) {
			case LINE:
				obj = new MyLine;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				wsprintf(s, L"\nType = %d, x1 = %d, y1 = %d, x2 = %d, y2 = %d, R = %d, G = %d, B = %d\n",
					obj->type, obj->pos.x1, obj->pos.y1, obj->pos.x2, obj->pos.y2,
					GetRValue(obj->rgbColor), GetGValue(obj->rgbColor), GetBValue(obj->rgbColor));
				OutputDebugString(s);
				break;
			case RECTANGLE:
				obj = new MyRectangle;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				wsprintf(s, L"\nType = %d, x1 = %d, y1 = %d, x2 = %d, y2 = %d, R = %d, G = %d, B = %d\n",
					obj->type, obj->pos.x1, obj->pos.y1, obj->pos.x2, obj->pos.y2,
					GetRValue(obj->rgbColor), GetGValue(obj->rgbColor), GetBValue(obj->rgbColor));
				OutputDebugString(s);
				break;
			case ELLIPSE:
				obj = new MyEllipse;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				wsprintf(s, L"\nType = %d, x1 = %d, y1 = %d, x2 = %d, y2 = %d, R = %d, G = %d, B = %d\n",
					obj->type, obj->pos.x1, obj->pos.y1, obj->pos.x2, obj->pos.y2,
					GetRValue(obj->rgbColor), GetGValue(obj->rgbColor), GetBValue(obj->rgbColor));
				OutputDebugString(s);
				break;
			case INSERTTEXT:
				obj = new MyText;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				break;
			} 
		}
	} f.close();
}
