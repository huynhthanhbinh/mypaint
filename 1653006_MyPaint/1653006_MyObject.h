#ifndef _MY_OBJECT_H_
#define _MY_OBJECT_H_

#include "stdafx.h"
#include "1653006_MyPaint.h"

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
