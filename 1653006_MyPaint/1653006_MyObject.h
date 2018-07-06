// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MY_OBJECT_H_
#define _MY_OBJECT_H_

#include "stdafx.h"
#include <vector>

struct Position {
	int x1, y1, x2, y2;
};

class Object {
public:
	int type;
	Position pos;
	COLORREF rgbColor = RGB(0, 0, 0);
	virtual void draw(HWND hWnd, HDC hdc) = 0;
};

struct CHILD_WND_DATA {
	BYTE wndType;
	HWND hWnd;
	COLORREF rgbColor = RGB(0, 0, 0);
	LOGFONT logFont;

	vector <Object*> arrObject;
};

class MyLine : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
};

class MyRectangle : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
};

class MyEllipse : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
};

class MyText : public Object {
public:
	LOGFONT logFont;
	void draw(HWND hWnd, HDC hdc);
};

void OnPaint(HWND hWnd);
void OnLButtonUp(Position pos, HWND hWnd, int mode);
void OnLButtonDown(HWND hWnd, LPARAM lParam, Position& pos);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode);
bool drawObject(HWND hWnd, HDC dc, Position& pos, int mode);
bool checkSamePoint(Position pos);
bool clearObjArray(HWND hWndClient);

#endif // !_MY_OBJECT_H_
