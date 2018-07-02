#ifndef _MYPAINT_H_
#define _MYPAINT_H_

#include "resource.h"
#include <CommCtrl.h>
#include <commdlg.h>
#include "stdafx.h"
#include <vector>

#pragma comment(lib,"ComCtl32.Lib") // searches first in the current working directory 
#pragma comment(lib,"ComDlg32.Lib") // and then in the path specified in the LIB environment variable.


using namespace std;

// define size of ...
#define MAX_LOADSTRING		100
#define IMAGE_WIDTH			18
#define IMAGE_HEIGHT		18
#define BUTTON_WIDTH		0
#define BUTTON_HEIGHT		0
#define TOOL_TIP_MAX_LEN	32

// define mode 
#define LINE                1
#define ELLIPSE             2
#define RECTANGLE           3
#define SELECT              4
#define INSERTTEXT          5

struct Position {
	int x1, y1, x2, y2;
};
class Page {
public:
	HWND handle;
	vector <Position> line;
	vector <Position> ellipse;
	vector <Position> rectangle;
	//vector for text ???

	~Page() {
		line.clear();
		ellipse.clear();
		rectangle.clear();
		//vector for text ???
	}
};
struct CHILD_WND_DATA {
	BYTE wndType;
	HWND hWnd;
	COLORREF rgbColor = NULL;
	LOGFONT logFont;

	Page page;
};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WelcomeDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	MDICloseProc(HWND hChildwnd, LPARAM lParam);


HWND handle_of_page();
void initFrameWindow(HWND hWnd);
void initChildWindow(HWND hWnd, int nType);
void onNewDrawWnd(HWND hWnd);
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist);
bool drawObject(HDC dc, Position& pos);
void ShowNotice(HWND hWnd, const WCHAR* MenuCaption);
void CheckMenuDraw(HWND hWnd, UINT MenuItemID);
void CheckToolbarDraw(HWND hWnd, UINT MenuItemID);
void createToolbar(HWND hWnd, bool& Toolbar_Exist);
void ToolbarNotifyHandle(LPARAM	lParam);
void ToolbarStyle(int tbStyle);
void viewToolbar(HWND hWnd);
void addEditToolbar(bool Toolbar_Exist);
void addFontsNColors(bool Toolbar_Exist);
void addDrawToolBar(bool Toolbar_Exist);
void OnChooseColors(HWND hWnd);
void OnChooseFonts(HWND hWnd);
void OnPaint(HWND hWnd);
void OnLButtonUp(Position pos, HWND hWnd);
void OnLButtonDown(HWND hWnd, LPARAM lParam, Position& pos);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos);


#endif // !_MYPAINT_H_