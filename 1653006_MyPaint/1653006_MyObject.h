// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#ifndef _MY_OBJECT_H_
#define _MY_OBJECT_H_

#include "stdafx.h"
#include <fstream>
#include <vector>

struct Position {
	int x1, y1, x2, y2;
};

struct MYPAINT_OBJ {
	int type;
	Position pos;
	COLORREF rgbColor;
	LOGFONT logFont;
	WCHAR str[MAX_LOADSTRING];
};

class Object {
public:
	int type;
	Position pos;
	COLORREF rgbColor = RGB(0, 0, 0);
	virtual void draw(HWND hWnd, HDC hdc) = 0;
	virtual void save(fstream& f) = 0;
	virtual void open(fstream& f) = 0;
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
	void save(fstream& f);
	void open(fstream& f);
};

class MyRectangle : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
};

class MyEllipse : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
};

class MyText : public Object {
public:
	LOGFONT logFont;
	WCHAR str[MAX_LOADSTRING];
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
};

void OnPaint(HWND hWnd);
void onLButtonDownText(HWND hWnd, HWND& hEdit, Position& pos);
void OnLButtonDown(HWND hWnd, HWND& hEdit, LPARAM lParam, Position& pos, int mode, bool& mouse_down, int& i);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode, bool mouse_down);
void OnLButtonUp(HINSTANCE hInst, HWND& hEdit, HWND hWnd, Position pos, int mode, bool& mouse_down);
bool drawObject(HWND hWnd, HDC dc, Position& pos, int mode);
bool checkSamePoint(Position pos);
bool clearObjArray(HWND hWndClient);

void OnOpen(HWND hWnd);
void OnSave(HWND hWnd);
void saveFile(vector <Object*>  arrObject, LPTSTR szFile);
void openFile(vector <Object*>& arrObject, LPTSTR szFile);

double getDistance(POINT pt1, POINT pt2);
bool isObject(Position pos, LPARAM lParam, int type);
void onSelect(HWND hWnd, LPARAM lParam, int& i);

void deleteObject(vector <Object*> &arrObj, int i);

#endif // !_MY_OBJECT_H_
