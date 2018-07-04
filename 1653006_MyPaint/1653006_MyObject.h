#ifndef _MY_OBJECT_H_
#define _MY_OBJECT_H_

#include "stdafx.h"
#include <vector>

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
	COLORREF rgbColor = RGB(0, 0, 0);
	LOGFONT logFont;

	//vector <Object*> arrObject;

	Page page;
};

class Object {
public:
	int type;
	Position pos;
	COLORREF rgbColor = RGB(0, 0, 0);
	virtual void draw(HWND hWnd) = 0;
};

class MyLine : public Object {
public:
	void draw(HWND hWnd);
};

class MyRectangle : public Object {
public:
	void draw(HWND hWnd);
};

class MyEllipse : public Object {
public:
	void draw(HWND hWnd);
};

class MyText : public Object {
public:
	LOGFONT logFont;
	void draw(HWND hWnd);
};

void OnPaint(HWND hWnd);
void OnLButtonUp(Position pos, HWND hWnd, int mode);
void OnLButtonDown(HWND hWnd, LPARAM lParam, Position& pos);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode);
bool drawObject(HWND hWnd, HDC dc, Position& pos, int mode);
bool checkSamePoint(Position pos);

#endif // !_MY_OBJECT_H_
