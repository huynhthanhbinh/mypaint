// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MYPAINT_H_
#define _MYPAINT_H_

#include "stdafx.h"
#include <vector>

using namespace std;

// define size of ...
#define MAX_LOADSTRING		100

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
	//HWND handle;
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
	COLORREF rgbColor = RGB(0,0,0);
	LOGFONT logFont;

	Page page;
};

class Object {
public:
	int left, top, right, bottom;

};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WelcomeDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	MDICloseProc(HWND hChildwnd, LPARAM lParam);

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

void initFrameWindow(HWND hWnd);
void initChildWindow(HWND hWnd, int nType);
void onNewDrawWnd(HWND hWnd);
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist);
bool drawObject(HDC dc, Position& pos);
void ShowNotice(HWND hWnd, const WCHAR* MenuCaption);
void OnChooseColors(HWND hWnd);
void OnChooseFonts(HWND hWnd);
void OnPaint(HWND hWnd);
void OnLButtonUp(Position pos, HWND hWnd);
void OnLButtonDown(HWND hWnd, LPARAM lParam, Position& pos);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos);


#endif // !_MYPAINT_H_