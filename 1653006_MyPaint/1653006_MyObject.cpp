// 1653006
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
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode, bool mouse_down, int i) {
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
		drawObject(hWnd, lParam, hdc, pos, mode, data, i);

		// Cập nhật điểm mới !!!
		pos.x2 = LOWORD(lParam);
		pos.y2 = HIWORD(lParam);

		// Vẽ đường thẳng mới (do mode NOT_XOR)
		drawObject(hWnd, lParam, hdc, pos, mode, data, i);

		DeleteObject(hPen);
		ReleaseDC(hWnd, hdc);
	}
}
bool drawObject(HWND hWnd, LPARAM lParam, HDC dc, Position pos, int mode, CHILD_WND_DATA* data, int i) {
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
			OutputDebugString(mess);

			drawFrame(hWnd, data, i);

			prev = true;
			break;
		}
	}
}


void deleteObject(HWND hwndMDIClient, int mode, int& i) {
	if (mode == SELECT && i != -1) {
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
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
		if (data != NULL) data->arrObject[i]->copy(current);
	}
}
void pasteObject(HWND hwndMDIClient, int mode, int i) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);

	if (data == NULL) return;

	if (OpenClipboard(hwndMDIClient)) {
		int nLineFormatID      = RegisterClipboardFormat(L"myLine");
		int nRectangleFormatID = RegisterClipboardFormat(L"myRectangle");
		int nEllipseFormatID   = RegisterClipboardFormat(L"myEllipse");
		int nTextFormatID      = RegisterClipboardFormat(L"myText");

		HGLOBAL hLine      = GetClipboardData(nLineFormatID);
		HGLOBAL hRectangle = GetClipboardData(nRectangleFormatID);
		HGLOBAL hEllipse   = GetClipboardData(nEllipseFormatID);
		HGLOBAL hText      = GetClipboardData(nTextFormatID);
		HGLOBAL hCFText    = GetClipboardData(CF_UNICODETEXT);

		if (hLine) {
			MyLine* p = (MyLine*)GlobalLock(hLine);
			MyLine* l = new MyLine;
			CopyMemory(l, p, sizeof(MyLine));
			GlobalUnlock(hLine);

			data->arrObject.push_back(l);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		} 
		else if (hRectangle) {
			MyRectangle* p = (MyRectangle*)GlobalLock(hRectangle);
			MyRectangle* r = new MyRectangle;
			CopyMemory(r, p, sizeof(MyRectangle));
			GlobalUnlock(hRectangle);

			data->arrObject.push_back(r);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		} 
		else if (hEllipse) {
			MyEllipse* p = (MyEllipse*)GlobalLock(hEllipse);
			MyEllipse* e = new MyEllipse;
			CopyMemory(e, p, sizeof(MyEllipse));
			GlobalUnlock(hEllipse);

			data->arrObject.push_back(e);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		}
		else if (hText) {
			MyText* p = (MyText*)GlobalLock(hText);
			MyText* t = new MyText;
			CopyMemory(t, p, sizeof(MyText));
			GlobalUnlock(hText);

			data->arrObject.push_back(t);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		} 
		else if (hCFText) {
			WCHAR* str = (WCHAR*)GlobalLock(hCFText);
			MyText* t = new MyText;

			CopyMemory(t->str, str, sizeof(t->str));

			SIZE size;
			HDC hdc = GetDC(current);
			HFONT hFont = CreateFontIndirect(&data->logFont);
			SelectObject(hdc, hFont);
			GetTextExtentPoint32(hdc, str, wcslen(str), &size);

			t->pos.x1 = 100;
			t->pos.y1 = 100;
			t->pos.x2 = t->pos.x1 + size.cx;
			t->pos.y2 = t->pos.y1 + size.cy;
			t->rgbColor = data->rgbColor;
			t->logFont = data->logFont;
			t->type = INSERTTEXT;
			GlobalUnlock(hCFText);

			data->arrObject.push_back(t);

			DeleteObject(hFont);
			ReleaseDC(current, hdc);
			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		} 
		else return;
	}
}
void cutObject(HWND hwndMDIClient, int mode, int& i) {
	copyObject(hwndMDIClient, mode, i);
	deleteObject(hwndMDIClient, mode, i);
}
void mousemoveObject(HWND hWnd, LPARAM lParam, Position& pos, bool mouse_down, int i, int& prev_i, int& sMode) {
	// prev_i = -1
	if (i != -1) {
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
		Object* obj = data->arrObject[i];

		Position p = obj->pos;
		if (p.x1 > p.x2) swap(p.x1, p.x2);
		if (p.y1 > p.y2) swap(p.y1, p.y2);

		
		if (x >= p.x1 - 6 && x <= p.x1 + 2) {
			if (y >= p.y1 - 6 && y <= p.y1 + 2) sMode = RESIZE_1;
			else if (y >= p.y2 - 2 && y <= p.y2 + 6) sMode = RESIZE_2;
			else sMode = -1;
		}
		else if (x >= p.x2 - 2 && x <= p.x2 + 6) {
			if (y >= p.y1 - 6 && y <= p.y1 + 2) sMode = RESIZE_2;
			else if (y >= p.y2 - 2 && y <= p.y2 + 6) sMode = RESIZE_1;
			else sMode = -1;
		}
		else sMode = -1;

		if (mouse_down == true) { // object is being chosen
			RECT rect;

			paintRect(hWnd, p, rect, 20);

			pos.x2 = x;
			pos.y2 = y;

			static Position xpos;
			if (prev_i == -1) xpos = data->arrObject[i]->pos; // 1st click select object --> then move

			int dx = pos.x2 - pos.x1;
			int dy = pos.y2 - pos.y1;

			obj->pos.x1 = xpos.x1 + dx;
			obj->pos.x2 = xpos.x2 + dx;
			obj->pos.y1 = xpos.y1 + dy;
			obj->pos.y2 = xpos.y2 + dy;

			paintRect(hWnd, p, rect, 20);
			prev_i = i;
		}
	}
}
void paintRect(HWND hWnd, Position tpos, RECT& rect, int x) {
	rect.left = tpos.x1 - x;
	rect.top = tpos.y1 - x;
	rect.right = tpos.x2 + x;
	rect.bottom = tpos.y2 + x;
	InvalidateRect(hWnd, &rect, TRUE);
}
void drawFrame(HWND hWnd, CHILD_WND_DATA* data, int i) {
	Position p = data->arrObject[i]->pos;
	if (p.x1 > p.x2) swap(p.x1, p.x2);
	if (p.y1 > p.y2) swap(p.y1, p.y2);

	HDC hdc = GetDC(hWnd);
	SetBkMode(hdc, TRANSPARENT);
	HPEN hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));

	Rectangle(hdc, p.x1 - 6, p.y1 - 6, p.x1 + 2, p.y1 + 2);
	Rectangle(hdc, p.x1 - 6, p.y2 - 2, p.x1 + 2, p.y2 + 6);
	Rectangle(hdc, p.x2 - 2, p.y1 - 6, p.x2 + 6, p.y1 + 2);
	Rectangle(hdc, p.x2 - 2, p.y2 - 2, p.x2 + 6, p.y2 + 6);

	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!
	Rectangle(hdc, p.x1 - 3, p.y1 - 3, p.x2 + 3, p.y2 + 3);

	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}
