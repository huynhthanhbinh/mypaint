// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MY_PAINT_H_
#define _MY_PAINT_H_

#include "stdafx.h"
#include <vector>

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
void onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool Toolbar_Exist);

void ShowNotice(HWND hWnd, const WCHAR* MenuCaption);
void OnChooseColors(HWND hWnd);
void OnChooseFonts(HWND hWnd);


#endif // !_MY_PAINT_H_