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
void MyLine::copy(HWND hWnd) {
	int nLineFormatID = RegisterClipboardFormat(L"myLine");
	HGLOBAL hgbMem = GlobalAlloc(GHND, sizeof(MyLine));
	MyLine * l = (MyLine*)GlobalLock(hgbMem);
	
	//ZeroMemory(&l, sizeof(MyLine));
	CopyMemory(l, this, sizeof(MyLine));

	GlobalUnlock(hgbMem);
	if (OpenClipboard(hWnd)) {
		EmptyClipboard();
		SetClipboardData(nLineFormatID, hgbMem);
		CloseClipboard();
	}
}
void MyRectangle::copy(HWND hWnd) {
	int nRectangleFormatID = RegisterClipboardFormat(L"myRectangle");
	HGLOBAL hgbMem = GlobalAlloc(GHND, sizeof(MyRectangle));
	MyRectangle * r = (MyRectangle*)GlobalLock(hgbMem);

	//ZeroMemory(&r, sizeof(MyRectangle));
	CopyMemory(r, this, sizeof(MyRectangle));

	GlobalUnlock(hgbMem);
	if (OpenClipboard(hWnd)) {
		EmptyClipboard();
		SetClipboardData(nRectangleFormatID, hgbMem);
		CloseClipboard();
	}
}
void MyEllipse::copy(HWND hWnd) {
	int nEllipseFormatID = RegisterClipboardFormat(L"myEllipse");
	HGLOBAL hgbMem = GlobalAlloc(GHND, sizeof(MyEllipse));
	MyEllipse * e = (MyEllipse*)GlobalLock(hgbMem);

	//ZeroMemory(&e, sizeof(MyEllipse));
	CopyMemory(e, this, sizeof(MyEllipse));

	GlobalUnlock(hgbMem);
	if (OpenClipboard(hWnd)) {
		EmptyClipboard();
		SetClipboardData(nEllipseFormatID, hgbMem);
		CloseClipboard();
	}
}
void MyText::copy(HWND hWnd) {
	int nTextFormatID = RegisterClipboardFormat(L"myText");
	HGLOBAL hgbMem = GlobalAlloc(GHND, sizeof(MyText));
	MyText * t = (MyText*)GlobalLock(hgbMem);

	//ZeroMemory(&t, sizeof(MyText));
	CopyMemory(t, this, sizeof(MyText));

	GlobalUnlock(hgbMem);
	if (OpenClipboard(hWnd)) {
		EmptyClipboard();
		SetClipboardData(nTextFormatID, hgbMem);
		CloseClipboard();
	}
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
void OnLButtonDown(HWND hWnd, HWND& hEdit, LPARAM lParam, Position& pos, int mode, bool& mouse_down, int& i) {
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

	if (mode == INSERTTEXT) onLButtonDownText(hWnd, hEdit, pos);
	if (mode == SELECT) onSelect(hWnd, lParam, i);

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
			HDC hdc = GetDC(hWnd);
			SIZE size;
			HFONT hFont = CreateFontIndirect(&data->logFont);
			SelectObject(hdc, hFont);
			GetTextExtentPoint32(hdc, str, wcslen(str), &size);

			if (pos.x2 < pos.x1) swap(pos.x2, pos.x1);
			if (pos.y2 < pos.y1) swap(pos.y2, pos.y1);
			pos.x2 = pos.x1 + size.cx;
			pos.y2 = pos.y1 + size.cy;
		
			MyText* t = new MyText;
			wcscpy(t->str, str);
			t->type = INSERTTEXT;
			t->rgbColor = data->rgbColor;
			t->logFont = data->logFont;
			t->pos = pos;
			data->arrObject.push_back(t);

			RECT r; GetWindowRect(hEdit, &r);
			MapWindowPoints(hEdit, hWnd, (LPPOINT)&r, 2);
			t->draw(hWnd, hdc);

			DeleteObject(hFont);
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
bool isObject(Position pos, LPARAM lParam, int type)
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
	case RECTANGLE: 
	case INSERTTEXT: {
		if (pt1.x > pt2.x) swap(pt1.x, pt2.x);
		if (pt1.y > pt2.y) swap(pt1.y, pt2.y);

		if ((pt1.x <= pt3.x && pt3.x <= pt2.x)
			&& (pt1.y <= pt3.y && pt3.y <= pt2.y))
			return true;
	} break;
	} return false;
}
void onSelect(HWND hWnd, LPARAM lParam, int& i)  {
	CHILD_WND_DATA* data = (CHILD_WND_DATA*)GetWindowLongPtr(hWnd, 0);
	static bool prev = false;

	if (prev == true) {
		RECT rect;
		GetClientRect(hWnd, &rect);
		InvalidateRect(hWnd, &rect, TRUE);
		UpdateWindow(hWnd);
		prev = false;
	}

	for (i = data->arrObject.size() - 1; i >= 0; i--) {
		if (isObject(data->arrObject[i]->pos, lParam, data->arrObject[i]->type)) {
			
			WCHAR mess[MAX_LOADSTRING];
			wsprintf(mess, L"\n\nObject: %d\n\n", i);
			//MessageBox(NULL, mess, L"NOTICE", MB_OK);
			OutputDebugString(mess);

			HDC hdc = GetDC(hWnd);
			SetBkMode(hdc, TRANSPARENT);


			Position pos = data->arrObject[i]->pos;
			if (pos.x1 > pos.x2) swap(pos.x1, pos.x2);
			if (pos.y1 > pos.y2) swap(pos.y1, pos.y2);

			HPEN hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));

			Rectangle(hdc, pos.x1 - 6, pos.y1 - 6, pos.x1 + 2, pos.y1 + 2);
			Rectangle(hdc, pos.x1 - 6, pos.y2 - 2, pos.x1 + 2, pos.y2 + 6);
			Rectangle(hdc, pos.x2 - 2, pos.y1 - 6, pos.x2 + 6, pos.y1 + 2);
			Rectangle(hdc, pos.x2 - 2, pos.y2 - 2, pos.x2 + 6, pos.y2 + 6);

			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!

			SelectObject(hdc, hPen);
			Rectangle(hdc,
				pos.x1 - 3,
				pos.y1 - 3,
				pos.x2 + 3,
				pos.y2 + 3);
			
			DeleteObject(hPen);
			ReleaseDC(hWnd, hdc);
			prev = true;
			break;
		}
	}
}
void deleteObject(HWND hwndMDIClient, int mode, int& i) {
	if (mode == SELECT && i != -1) {
		//MessageBox(NULL, L"EDIT DELETE", L"NOTICE", MB_OK);
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);

		for (unsigned int j = i; j < data->arrObject.size() - 1; j++) {
			swap(data->arrObject[j], data->arrObject[j + 1]);
		} delete data->arrObject[data->arrObject.size() - 1];
		data->arrObject.pop_back();

		InvalidateRect(current, NULL, TRUE);
		i = -1;
	}
}
void copyObject(HWND hwndMDIClient, int mode, int i) {
	if (mode == SELECT && i != -1) {
		//MessageBox(NULL, L"EDIT COPY", L"NOTICE", MB_OK);
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
		if (data != NULL) data->arrObject[i]->copy(current);
	}
}


//void copyToClipboard(HWND hWnd) {
//	if (mode == SELECT_AREA) { // dữ liệu dạng chuẩn
//		HDC hdc = GetDC(hWnd);
//		HDC memSourceDC = CreateCompatibleDC(hdc);
//		SelectObject(memSourceDC, hBitmap);
//		HDC memDestDC = CreateCompatibleDC(hdc);
//		HBITMAP hCopyBitmap = CreateCompatibleBitmap(hdc, _x2 - _x1, _y2 - _y1);
//		SelectObject(memDestDC, hCopyBitmap);
//
//		BitBlt(memDestDC, 0, 0, _x2 - _x1, _y2 - _y1,
//			memSourceDC, _x1, _y1, SRCCOPY);
//
//		if (OpenClipboard(hWnd)) {
//			EmptyClipboard();
//			SetClipboardData(CF_BITMAP, hCopyBitmap);
//			CloseClipboard();
//		}
//
//		DeleteDC(memSourceDC);
//		DeleteDC(memDestDC);
//		DeleteObject(hCopyBitmap);
//		ReleaseDC(hWnd, hdc);
//	}
//	else { // dữ liêu dạng không chuản 
//		// copy the ellipse area object to clipboard 
//		int nEllipseFormatID = RegisterClipboardFormat(szEllipseFormat);
//		HGLOBAL hgbMem = GlobalAlloc(GHND, sizeof(ELLIPSE_OBJ));
//		ELLIPSE_OBJ * p = (ELLIPSE_OBJ*)GlobalLock(hgbMem);
//		p->x1 = _x1;
//		p->y1 = _y1;
//		p->x2 = _x2;
//		p->y2 = _y2;
//		GlobalUnlock(hgbMem);
//		if (OpenClipboard(hWnd)) {
//			EmptyClipboard();
//			SetClipboardData(nEllipseFormatID, hgbMem);
//			CloseClipboard();
//		}
//	}
//}

