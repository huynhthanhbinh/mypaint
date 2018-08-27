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

class Object {
public:
	int type;
	Position pos;
	COLORREF rgbColor = RGB(0, 0, 0);
	virtual void draw(HWND hWnd, HDC hdc) = 0;
	virtual void save(fstream& f) = 0;
	virtual void open(fstream& f) = 0;
	virtual void copy(HWND hWnd) = 0;
};

struct Work {
	int id;
	Object* obj = NULL;
	Object* cur = NULL; // use for CHANGE
};

struct CHILD_WND_DATA {
	BYTE wndType;
	HWND hWnd;
	COLORREF rgbColor = RGB(0, 0, 0);
	LOGFONT logFont;

	vector <Object*> arrObject;
	vector <Work> arrUndo;
	vector <Work> arrRedo;

	bool saved = false;
	bool exist = false;
	WCHAR path[MAX_PATH];
};

class MyLine : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
	void copy(HWND hWnd);
};

class MyRectangle : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
	void copy(HWND hWnd);
};

class MyEllipse : public Object {
public:
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
	void copy(HWND hWnd);
};

class MyText : public Object {
public:
	LOGFONT logFont;
	WCHAR str[MAX_LOADSTRING];
	void draw(HWND hWnd, HDC hdc);
	void save(fstream& f);
	void open(fstream& f);
	void copy(HWND hWnd);
};

void OnPaint(HWND hWnd);
void onLButtonDownText(HWND hWnd, HWND& hEdit, Position& pos);
void OnLButtonDown(HWND hWnd, HWND& hEdit, LPARAM lParam, Position& pos, int mode, bool& mouse_down, int& i, int& sMode);
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode, bool mouse_down, int i);
void OnLButtonUp(HINSTANCE hInst, HWND& hEdit, HWND hWnd, Position pos, int mode, bool& mouse_down);
bool drawObject(HWND hWnd, LPARAM lParam, HDC dc, Position pos, int mode, CHILD_WND_DATA* data, int i);
bool checkSamePoint(Position pos);
bool clearObjArray(HWND hWndClient);


double getDistance(POINT pt1, POINT pt2);
bool isObject(Position pos, LPARAM lParam, int type);
void onSelect(HWND hWnd, LPARAM lParam, int& i, int& sMode);

void cutObject(HWND hwndMDIClient, int mode, int& i);
void copyObject(HWND hwndMDIClient, int mode, int i);
void pasteObject(HWND hwndMDIClient, int mode, int i);
void deleteObject(HWND hwndMDIClient, int mode, int& i);


void mousemoveObject(HWND hWnd, HWND activated, LPARAM lParam, Position& pos, bool mouse_down, int i, int& prev_i, int& sMode);
void paintRect(HWND hWnd, Position tpos, RECT& rect, int x);
void drawFrame(HWND hWnd, CHILD_WND_DATA* data, int i);
void sMode_convert(int& sMode, int x, int y, Position p, Object* obj);


void doUndo(HWND hwndMDIClient, int mode);
void doRedo(HWND hwndMDIClient, int mode);
void createRedo(Work& undo, Object* obj, CHILD_WND_DATA* data);
void checkUndoRedo(HWND hFrameWnd, HWND hWnd, HWND hToolBarWnd);


void saveBitmap(HWND hWnd, LPWSTR szFile);
void OnChooseColors(HWND hWnd, HWND hwndMDIClient);
void OnChooseFonts(HWND hWnd, HWND hwndMDIClient);


void saveFile(vector <Object*>  arrObject, LPTSTR szFile);
void openFile(vector <Object*>& arrObject, LPTSTR szFile);
bool OnSave(HWND hWnd, HWND hwndMDIClient);
void OnOpen(HWND hWnd, HWND hwndMDIClient, WCHAR* szDrawTitle, WCHAR* szDrawWindowClass);


void initChildWindow(HWND hWnd, int nType);
void initFrameWindow(HWND hWnd, HWND& hFrameWnd, HWND& hwndMDIClient, HINSTANCE hInst);
void onNewDrawWnd(HWND hWnd, HWND& hwndMDIClient, WCHAR* szDrawTitle, WCHAR* szDrawWindowClass);


void changeColor(HWND hwndMDIClient, int r, int g, int b);

#endif // !_MY_OBJECT_H_
