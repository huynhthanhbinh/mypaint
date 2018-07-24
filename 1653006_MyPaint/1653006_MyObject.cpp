﻿// 1653006
// Huỳnh Thanh Bình
// 16CLC1

#include "stdafx.h"
#include "1653006_MyObject.h"

void MyLine::draw(HWND hWnd, HDC hdc) {
	HPEN hPen = CreatePen(PS_SOLID, 2, rgbColor);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!

	MoveToEx(hdc, pos.x1, pos.y1, NULL);
	LineTo(hdc, pos.x2, pos.y2);
	DeleteObject(hPen);
}
void MyRectangle::draw(HWND hWnd, HDC hdc) {
	HPEN hPen = CreatePen(PS_SOLID, 2, rgbColor);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!

	MoveToEx(hdc, pos.x1, pos.y1, NULL);
	Rectangle(hdc, pos.x1, pos.y1, pos.x2, pos.y2);
	DeleteObject(hPen);
}
void MyEllipse::draw(HWND hWnd, HDC hdc) {
	HPEN hPen = CreatePen(PS_SOLID, 2, rgbColor);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!

	MoveToEx(hdc, pos.x1, pos.y1, NULL);
	Ellipse(hdc, pos.x1, pos.y1, pos.x2, pos.y2);
	DeleteObject(hPen);
}
void MyText::draw(HWND hWnd, HDC hdc) {
	HFONT hFont = CreateFontIndirect(&logFont);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, rgbColor);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, pos.x1, pos.y1, str, wcslen(str));
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!
	Rectangle(hdc, pos.x1, pos.y1, pos.x2, pos.y2);
	DeleteObject(hFont);
}
void MyLine::save(fstream& f) {
	//f << type << pos.x1 << pos.y1 << pos.x2 << pos.y2 << rgbColor << endl;
	f.write((char*)&type    , sizeof(int));
	f.write((char*)&pos.x1  , sizeof(int));
	f.write((char*)&pos.y1  , sizeof(int));
	f.write((char*)&pos.x2  , sizeof(int));
	f.write((char*)&pos.y2  , sizeof(int));
	f.write((char*)&rgbColor, sizeof(rgbColor));
}
void MyRectangle::save(fstream& f) {
	//f << type << pos.x1 << pos.y1 << pos.x2 << pos.y2 << rgbColor << endl;
	f.write((char*)&type, sizeof(int));
	f.write((char*)&pos.x1, sizeof(int));
	f.write((char*)&pos.y1, sizeof(int));
	f.write((char*)&pos.x2, sizeof(int));
	f.write((char*)&pos.y2, sizeof(int));
	f.write((char*)&rgbColor, sizeof(rgbColor));
}
void MyEllipse::save(fstream& f) {
	//f << type << pos.x1 << pos.y1 << pos.x2 << pos.y2 << rgbColor << endl;
	f.write((char*)&type, sizeof(int));
	f.write((char*)&pos.x1, sizeof(int));
	f.write((char*)&pos.y1, sizeof(int));
	f.write((char*)&pos.x2, sizeof(int));
	f.write((char*)&pos.y2, sizeof(int));
	f.write((char*)&rgbColor, sizeof(rgbColor));
}
void MyText::save(fstream& f) {
	f.write((char*)&type, sizeof(int));
	f.write((char*)&pos.x1, sizeof(int));
	f.write((char*)&pos.y1, sizeof(int));
	f.write((char*)&pos.x2, sizeof(int));
	f.write((char*)&pos.y2, sizeof(int));
	f.write((char*)&rgbColor, sizeof(rgbColor));
	f.write((char*)&logFont, sizeof(logFont));
	f.write((char*)&str, sizeof(str));
}
void MyLine::open(fstream& f) {
	f.read((char*)&pos.x1, sizeof(int));
	f.read((char*)&pos.y1, sizeof(int));
	f.read((char*)&pos.x2, sizeof(int));
	f.read((char*)&pos.y2, sizeof(int));
	f.read((char*)&rgbColor, sizeof(rgbColor));
}
void MyRectangle::open(fstream& f) {
	f.read((char*)&pos.x1, sizeof(int));
	f.read((char*)&pos.y1, sizeof(int));
	f.read((char*)&pos.x2, sizeof(int));
	f.read((char*)&pos.y2, sizeof(int));
	f.read((char*)&rgbColor, sizeof(rgbColor));
}
void MyEllipse::open(fstream& f) {
	f.read((char*)&pos.x1, sizeof(int));
	f.read((char*)&pos.y1, sizeof(int));
	f.read((char*)&pos.x2, sizeof(int));
	f.read((char*)&pos.y2, sizeof(int));
	f.read((char*)&rgbColor, sizeof(rgbColor));
}
void MyText::open(fstream& f) {
	f.read((char*)&pos.x1, sizeof(int));
	f.read((char*)&pos.y1, sizeof(int));
	f.read((char*)&pos.x2, sizeof(int));
	f.read((char*)&pos.y2, sizeof(int));
	f.read((char*)&rgbColor, sizeof(rgbColor));
	f.read((char*)&logFont, sizeof(logFont));
	f.read((char*)&str, sizeof(str));
}


void OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	for (unsigned int i = 0; i < data->arrObject.size(); i++) {
		data->arrObject[i]->draw(hWnd, hdc);
	}

	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);
}
void OnLButtonUp(HINSTANCE hInst, HWND& hEdit, HWND hWnd, Position pos, int mode, bool& mouse_down) {
	ClipCursor(NULL); //release the mouse cursor
	ReleaseCapture(); //release the mouse capture
	mouse_down = false;

	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	WCHAR s[100];
	switch (mode) {
	case LINE:
		if (!checkSamePoint(pos)) {
			MyLine *l = new MyLine; 
			l->pos = pos;
			l->type = LINE;
			l->rgbColor = data->rgbColor;
			data->arrObject.push_back(l);
		}
		break;
	case RECTANGLE:
		if (!checkSamePoint(pos)) {
			MyRectangle * r = new MyRectangle;
			r->pos = pos;
			r->type = RECTANGLE;
			r->rgbColor = data->rgbColor;
			data->arrObject.push_back(r);
		}
		break;
	case ELLIPSE:
		if (!checkSamePoint(pos)) {
			MyEllipse * e = new MyEllipse;
			e->pos = pos;
			e->type = ELLIPSE;
			e->rgbColor = data->rgbColor;
			data->arrObject.push_back(e);
		}
		break;
	case INSERTTEXT: {
		Position tpos = pos;
		if (pos.x2 < pos.x1) swap(tpos.x2, tpos.x1);
		if (pos.y2 < pos.y1) swap(tpos.y2, tpos.y1);

		hEdit = CreateWindowEx(
			WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			tpos.x1, tpos.y1, tpos.x2 - tpos.x1, tpos.y2 - tpos.y1, hWnd, nullptr, hInst, nullptr);
		
		HFONT hFont = CreateFont(
			data->logFont.lfHeight, data->logFont.lfWidth, 
			data->logFont.lfEscapement, data->logFont.lfOrientation, 
			data->logFont.lfWeight, data->logFont.lfItalic, data->logFont.lfUnderline,
			data->logFont.lfStrikeOut, data->logFont.lfCharSet, 
			data->logFont.lfOutPrecision, data->logFont.lfClipPrecision, data->logFont.lfQuality,
			data->logFont.lfPitchAndFamily, data->logFont.lfFaceName);


		SendMessage(hEdit, WM_SETFONT, WPARAM(hFont), TRUE);
		SetFocus(hEdit);
		ShowWindow(hEdit, SW_NORMAL);
		} break;
	}
	wsprintf(s, L"\n\n\nNumbers of object: %d\n\n\n", data->arrObject.size()); OutputDebugString(s);
	return;
}
void OnLButtonDown(HWND hWnd, HWND& hEdit, LPARAM lParam, Position& pos, int mode, bool& mouse_down) {
	SetCapture(hWnd); // Capture mouse input
	RECT rect;
	POINT upperleft, lowerright;
	GetClientRect(hWnd, &rect);
	upperleft.x = rect.left;
	upperleft.y = rect.top;
	lowerright.x = rect.right + 1;
	lowerright.y = rect.bottom + 1;
	ClientToScreen(hWnd, &upperleft);
	ClientToScreen(hWnd, &lowerright);
	SetRect(&rect, upperleft.x, upperleft.y, lowerright.x, lowerright.y);
	ClipCursor(&rect);

	if (mode == INSERTTEXT) {
		onLButtonDownText(hWnd, hEdit, pos);
	}
	if (mode == SELECT) {
		CHILD_WND_DATA* data = (CHILD_WND_DATA*)GetWindowLongPtr(hWnd, 0);
		for (int i = data->arrObject.size() - 1; i >= 0; i--) {
			if (onSelect(data->arrObject[i]->pos, lParam, data->arrObject[i]->type)) {
				WCHAR mess[MAX_LOADSTRING];
				HDC hdc = GetDC(hWnd);
				wsprintf(mess, L"object: %d", i);
				MessageBox(hWnd, mess, L"NOTICE", MB_OK);
				ReleaseDC(hWnd, hdc);
				break;
			}
		}
	}

	pos.x1 = pos.x2 = LOWORD(lParam);
	pos.y1 = pos.y2 = HIWORD(lParam);

	mouse_down = true;

	//MessageBox(NULL, L"LBUTTON DOWN", L"NOTICE", MB_OK);
}
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode, bool mouse_down) {
	//if ((wParam & MK_LBUTTON) == MK_LBUTTON) {
	if (mouse_down == true) {
		HDC hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);

		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
		HPEN hPen;
		if (mode == INSERTTEXT ) hPen = CreatePen(PS_SOLID, 1, data->rgbColor);
		else hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
		SelectObject(hdc, hPen);

		// Vẽ đường thẳng cũ 
		drawObject(hWnd, hdc, pos, mode);

		// Cập nhật điểm mới !!!
		pos.x2 = LOWORD(lParam);
		pos.y2 = HIWORD(lParam);

		// Vẽ đường thẳng mới (do mode NOT_XOR)
		drawObject(hWnd, hdc, pos, mode);

		DeleteObject(hPen);
		ReleaseDC(hWnd, hdc);
	}
}
bool drawObject(HWND hWnd, HDC dc, Position& pos, int mode) {
	switch (mode) {
	case LINE:
		MoveToEx(dc, pos.x1, pos.y1, NULL);
		LineTo(dc, pos.x2, pos.y2);
		return true;
	case RECTANGLE:
		Rectangle(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		return true;
	case ELLIPSE:
		Ellipse(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		return true;
	case INSERTTEXT:
		Rectangle(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		return true;
	} return false;
}
bool checkSamePoint(Position pos) { // leak memory !!! 
	if (pos.x1 == pos.x2 && pos.y1 == pos.y2)
		return true;
	return false;
}
bool clearObjArray(HWND hWndClient) {
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWndClient, 0);
	data->arrObject.clear();
	return true;
}
void onLButtonDownText(HWND hWnd, HWND& hEdit, Position& pos) {
	CHILD_WND_DATA* data = (CHILD_WND_DATA*)GetWindowLongPtr(hWnd, 0);

	if (hEdit != NULL) {
		int size = GetWindowTextLength(hEdit) + 1; // + 1: "\0" kí tự kết thúc chuỗi 
		WCHAR* str = new WCHAR[size];

		if (GetWindowText(hEdit, str, size)) {
			MyText* t = new MyText;
			wcscpy(t->str, str);
			t->type = INSERTTEXT;
			t->rgbColor = data->rgbColor;
			t->logFont = data->logFont;
			if (pos.x2 < pos.x1) swap(pos.x2, pos.x1);
			if (pos.y2 < pos.y1) swap(pos.y2, pos.y1);
			
			t->pos = pos;
			data->arrObject.push_back(t);

			RECT r; GetWindowRect(hEdit, &r);
			MapWindowPoints(hEdit, hWnd, (LPPOINT)&r, 2); // map point wm_paint
			//InvalidateRect(hEdit, &r, TRUE);
		
			HDC hdc = GetDC(hWnd);
			t->draw(hWnd, hdc);
			
			ReleaseDC(hWnd, hdc);
			DestroyWindow(hEdit);
			hEdit = NULL;
		} delete[] str;
		DestroyWindow(hEdit);
	}
}

double getDistance(POINT pt1, POINT pt2) {
	return (sqrt(pow((pt1.x - pt2.x), 2) + pow((pt1.y - pt2.y), 2)));
}
bool onSelect(Position pos, LPARAM lParam, int type)
{
	POINT pt1 = { pos.x1, pos.y1 };
	POINT pt2 = { pos.x2, pos.y2 };
	POINT pt3;
	pt3.x = LOWORD(lParam);
	pt3.y = HIWORD(lParam);
	switch (type) {
	case LINE: {
		double d = getDistance(pt3, pt1) + getDistance(pt3, pt2);
		if (d >= getDistance(pt1, pt2) - 0.2 // xấp xỉ, nằm ngoài đoạn
			&& d <= getDistance(pt1, pt2) + 0.2) // xấp xỉ, nằm trong đoạn
			return true;
	} break;
	case ELLIPSE:
	case RECTANGLE: {
		if (pt1.x > pt2.x) swap(pt1.x, pt2.x);
		if (pt1.y > pt2.y) swap(pt1.y, pt2.y);

		if ((pt1.x <= pt3.x && pt3.x <= pt2.x)
			&& (pt1.y <= pt3.y && pt3.y <= pt2.y))
			return true;
	} break;
	case INSERTTEXT:
		break;

	} return false;
}
