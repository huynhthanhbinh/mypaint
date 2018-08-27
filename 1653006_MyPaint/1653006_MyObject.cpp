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
	HDC mainDC = BeginPaint(hWnd, &ps);
	HDC backbufferDC = CreateCompatibleDC(mainDC);

	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right;
	int height = rect.bottom;

	HBITMAP backbuffer = CreateCompatibleBitmap(mainDC, width, height);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

	int savedDC = SaveDC(backbufferDC);
	SelectObject(backbufferDC, backbuffer);
	FillRect(backbufferDC, &rect, hBrush);


	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	for (unsigned int i = 0; i < data->arrObject.size(); i++) {
		data->arrObject[i]->draw(hWnd, backbufferDC);
	}

	BitBlt(mainDC, 0, 0, width, height, backbufferDC, 0, 0, SRCCOPY);
	RestoreDC(backbufferDC, savedDC);

	DeleteObject(backbuffer);
	DeleteObject(hBrush);
	DeleteDC(backbufferDC);

	EndPaint(hWnd, &ps);
	ReleaseDC(hWnd, mainDC);
}
void OnLButtonDown(HWND hWnd, HWND& hEdit, LPARAM lParam, Position& pos, int mode, bool& mouse_down, int& i, int& sMode) {
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
	if (mode == SELECT) onSelect(hWnd, lParam, i, sMode);

	pos.x1 = pos.x2 = LOWORD(lParam);
	pos.y1 = pos.y2 = HIWORD(lParam);

	mouse_down = true;
}
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode, bool mouse_down, int i) {
	//if ((wParam & MK_LBUTTON) == MK_LBUTTON) {
	if (mouse_down == true) {
		HDC hdc = GetDC(hWnd);
		HDC backbuffDC = CreateCompatibleDC(hdc);

		RECT rect;
		GetClientRect(hWnd, &rect);
		int width = rect.right;
		int height = rect.bottom;

		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);

		HBITMAP backbuffer = CreateCompatibleBitmap(hdc, width, height);
		HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));


		int savedDC = SaveDC(backbuffDC);
		SelectObject(backbuffDC, backbuffer);
		FillRect(backbuffDC, &rect, hBrush);

		for (unsigned int i = 0; i < data->arrObject.size(); i++) {
			data->arrObject[i]->draw(hWnd, backbuffDC);
		}
		
		HPEN hPen;
		if (mode == INSERTTEXT) hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
		else                    hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
		SelectObject(backbuffDC, hPen);

		// Vẽ đường thẳng cũ 
		//drawObject(hWnd, lParam, backbuffDC, pos, mode, data, i);

		pos.x2 = LOWORD(lParam);
		pos.y2 = HIWORD(lParam);

		// Vẽ đường thẳng mới 
		drawObject(hWnd, lParam, backbuffDC, pos, mode, data, i);

		SelectObject(backbuffDC, backbuffer);
		BitBlt(hdc, 0, 0, width, height, backbuffDC, 0, 0, SRCCOPY);
		RestoreDC(backbuffDC, savedDC);


		DeleteObject(backbuffer);
		DeleteObject(hBrush);
		DeleteObject(hPen);

		DeleteDC(backbuffDC);
		ReleaseDC(hWnd, hdc);
	}
}
void OnLButtonUp(HINSTANCE hInst, HWND& hEdit, HWND hWnd, Position pos, int mode, bool& mouse_down) {
	if (mouse_down == false) return;

	ClipCursor(NULL); //release the mouse cursor
	ReleaseCapture(); //release the mouse capture

	mouse_down = false;

	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	//WCHAR s[100];
	switch (mode) {
	case LINE:
		if (!checkSamePoint(pos)) {
			MyLine *l = new MyLine;
			l->pos = pos;
			l->type = LINE;
			l->rgbColor = data->rgbColor;

			Work redo;
			createRedo(redo, l, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(l);

			data->saved = false;
		}
		break;
	case RECTANGLE:
		if (!checkSamePoint(pos)) {
			MyRectangle * r = new MyRectangle;
			r->pos = pos;
			r->type = RECTANGLE;
			r->rgbColor = data->rgbColor;

			Work redo;
			createRedo(redo, r, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(r);
			
			data->saved = false;
		}
		break;
	case ELLIPSE:
		if (!checkSamePoint(pos)) {
			MyEllipse * e = new MyEllipse;
			e->pos = pos;
			e->type = ELLIPSE;
			e->rgbColor = data->rgbColor;

			Work redo;
			createRedo(redo, e, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(e);

			data->saved = false;
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
	//wsprintf(s, L"\nNumbers of object: %d\n", data->arrObject.size()); OutputDebugString(s);
	return;
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
	if (!data->arrObject.empty()) data->arrObject.clear();
	if (!data->arrUndo.empty())   data->arrUndo.clear();
	if (!data->arrRedo.empty())   data->arrRedo.clear();
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


			Work redo;
			createRedo(redo, t, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(t);

			data->saved = false;

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
void onSelect(HWND hWnd, LPARAM lParam, int& i, int& sMode)  {
	CHILD_WND_DATA* data = (CHILD_WND_DATA*)GetWindowLongPtr(hWnd, 0);
	static bool prev = false;

	if (prev == true) {
		RECT rect;
		GetClientRect(hWnd, &rect);
		InvalidateRect(hWnd, &rect, TRUE);
		UpdateWindow(hWnd);
		prev = false;
	}

	if (sMode > -1) {
		prev = true;  return;
	}

	for (i = data->arrObject.size() - 1; i >= 0; i--) {
		if (isObject(data->arrObject[i]->pos, lParam, data->arrObject[i]->type)) {
			/*WCHAR mess[MAX_LOADSTRING];
			wsprintf(mess, L"\nObject No. %d\n", i);
			OutputDebugString(mess);*/

			drawFrame(hWnd, data, i);
			
			// change cursor to IDC_SIZEALL
			sMode = MOVE;
			HCURSOR sall = LoadCursor(NULL, IDC_SIZEALL);
			SetCursor(sall);
			DestroyCursor(sall);

			prev = true;
			break;
		}
	}
}


void deleteObject(HWND hwndMDIClient, int mode, int& i) {
	if (mode == SELECT && i != -1) {
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);

		if (data == NULL) return;

		Work redo;
		redo.id = DELETE;

		for (unsigned int j = i; j < data->arrObject.size() - 1; j++) {
			swap(data->arrObject[j], data->arrObject[j + 1]);
		} 
		
		swap(data->arrObject[data->arrObject.size() - 1], redo.obj);
		data->arrRedo.push_back(redo);

		data->arrObject.pop_back();

		InvalidateRect(current, NULL, TRUE);
		i = -1;

		HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);
		SetCursor(arrow);
		DestroyCursor(arrow);
	}
}
void copyObject(HWND hwndMDIClient, int mode, int i) {
	if (mode == SELECT && i != -1) {

		/*WCHAR x[128];
		wsprintf(x, L"\n\nCopy: i = %d\n\n", i);
		OutputDebugString(x);*/

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

			Work redo;
			createRedo(redo, l, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(l);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		} 
		else if (hRectangle) {
			MyRectangle* p = (MyRectangle*)GlobalLock(hRectangle);
			MyRectangle* r = new MyRectangle;
			CopyMemory(r, p, sizeof(MyRectangle));
			GlobalUnlock(hRectangle);

			Work redo;
			createRedo(redo, r, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(r);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		} 
		else if (hEllipse) {
			MyEllipse* p = (MyEllipse*)GlobalLock(hEllipse);
			MyEllipse* e = new MyEllipse;
			CopyMemory(e, p, sizeof(MyEllipse));
			GlobalUnlock(hEllipse);

			Work redo;
			createRedo(redo, e, data);
			data->arrRedo.push_back(redo);

			data->arrObject.push_back(e);

			InvalidateRect(current, NULL, TRUE); 
			CloseClipboard(); return;
		}
		else if (hText) {
			MyText* p = (MyText*)GlobalLock(hText);
			MyText* t = new MyText;
			CopyMemory(t, p, sizeof(MyText));
			GlobalUnlock(hText);

			Work redo;
			createRedo(redo, t, data);
			data->arrRedo.push_back(redo);

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

			Work redo;
			createRedo(redo, t, data);
			data->arrRedo.push_back(redo);

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
	
	/*WCHAR x[128];
	wsprintf(x, L"\n\nCut: i = %d\n\n", i);
	OutputDebugString(x);*/

	copyObject(hwndMDIClient, mode, i);
	deleteObject(hwndMDIClient, mode, i);
}
void mousemoveObject(HWND hWnd, HWND activated, LPARAM lParam, Position& pos, bool mouse_down, int i, int& prev_i, int& sMode) {
	// prev_i = -1 when lbutton is up !!!
	if (i != -1) {
		if (hWnd != activated) return; // vital - very important !!! 
		// ex: copy object from activated to another child window !! 
		
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
		if (data == NULL || !(data->arrObject.size() > 0)) { 
			sMode = -1; 
			return; 
		}

	/*	WCHAR xx[128];
		wsprintf(xx, L"\nhwnd = %d, activated = %d, vector size = %d, i = %d\n", 
			hWnd, activated, data->arrObject.size(), i);
		OutputDebugString(xx);*/

		Object* obj = data->arrObject[i];

		static Position xpos;
		Position p = obj->pos;


		if (p.x1 > p.x2) swap(p.x1, p.x2);
		if (p.y1 > p.y2) swap(p.y1, p.y2);


		if (prev_i == -1 && mouse_down == false) sMode_convert(sMode, x, y, p, obj);

		if (mouse_down == true) { // object is being chosen , check mode is move
			if (prev_i == -1) { // 1st click select object --> then move
				xpos = obj->pos;

				Work redo;
				redo.id = CHANGE;
				
				switch (obj->type) {
				case LINE: {
					redo.cur = new MyLine;
					CopyMemory(redo.cur, obj, sizeof(MyLine));
				} break;
				
				case RECTANGLE: {
					redo.cur = new MyRectangle;
					CopyMemory(redo.cur, obj, sizeof(MyRectangle));
				} break;

				case ELLIPSE: {
					redo.cur = new MyEllipse;
					CopyMemory(redo.cur, obj, sizeof(MyEllipse));
				} break;

				case INSERTTEXT: {
					redo.cur = new MyText;
					CopyMemory(redo.cur, obj, sizeof(MyText));
				} break;

				}

				redo.cur->pos = xpos;
				data->arrRedo.push_back(redo);
			}

			RECT rect;

			if (sMode == MOVE) {
				pos.x2 = x;
				pos.y2 = y;

				int dx = pos.x2 - pos.x1;
				int dy = pos.y2 - pos.y1;

				obj->pos.x1 = xpos.x1 + dx;
				obj->pos.x2 = xpos.x2 + dx;
				obj->pos.y1 = xpos.y1 + dy;
				obj->pos.y2 = xpos.y2 + dy;

				data->arrRedo.back().obj = obj;

				paintRect(hWnd, p, rect, 20);
				prev_i = i; 
				return;
			}

			if (obj->type == INSERTTEXT) return; // resize not use with object TEXT

			paintRect(hWnd, p, rect, 20);
			static POINT center; // center point to compare and resize !!!! 

			switch (sMode) {
				case RESIZE_1: {
					HCURSOR c = LoadCursor(NULL, IDC_SIZENWSE); SetCursor(c); DestroyCursor(c);
					if (prev_i == -1) { 
						center.x = p.x2; center.y = p.y2; 
					}

					if (x <= center.x) {
						if (y <= center.y) { p.x1 = x; p.y1 = y; }
						else               sMode = RESIZE_3;
					}
					else {
						if (y <= center.y) sMode = RESIZE_2;
						else               sMode = RESIZE_4;
					}
				} break;
				case RESIZE_2: {
					HCURSOR c = LoadCursor(NULL, IDC_SIZENESW); SetCursor(c); DestroyCursor(c);
					if (prev_i == -1) { center.x = p.x1; center.y = p.y2; }

					if (x >= center.x) {
						if (y <= center.y) { p.x1 = x; p.y1 = y; }
						else               sMode = RESIZE_4;
					}
					else {
						if (y <= center.y) sMode = RESIZE_1;
						else               sMode = RESIZE_3;
					}
				} break;
				case RESIZE_3: {
					HCURSOR c = LoadCursor(NULL, IDC_SIZENESW); SetCursor(c); DestroyCursor(c);
					if (prev_i == -1) { center.x = p.x2; center.y = p.y1; }

					if (x <= center.x) {
						if (y > center.y) { p.x1 = x; p.y1 = y; }
						else               sMode = RESIZE_1;
					}
					else {
						if (y <= center.y) sMode = RESIZE_2;
						else               sMode = RESIZE_4;
					}
				} break;
				case RESIZE_4: {
					HCURSOR c = LoadCursor(NULL, IDC_SIZENWSE); SetCursor(c); DestroyCursor(c);
					if (prev_i == -1) { center.x = p.x1; center.y = p.y1; }

					if (x >= center.x) {
						if (y > center.y) { p.x1 = x; p.y1 = y; }
						else               sMode = RESIZE_2;
					}
					else {
						if (y <= center.y) sMode = RESIZE_1;
						else               sMode = RESIZE_3;
					}
				} break;
			}

			p.x2 = center.x;
			p.y2 = center.y;
			obj->pos = p;

			data->arrRedo.back().obj = obj;

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
	HDC hdc = GetDC(hWnd);
	SetBkMode(hdc, TRANSPARENT);
	HPEN hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));

	if (data->arrObject[i]->type != LINE) {
		if (p.x1 > p.x2) swap(p.x1, p.x2);
		if (p.y1 > p.y2) swap(p.y1, p.y2);

		Rectangle(hdc, p.x1 - 8, p.y1 - 8, p.x1 + 2, p.y1 + 2);
		Rectangle(hdc, p.x1 - 8, p.y2 - 2, p.x1 + 2, p.y2 + 8);
		Rectangle(hdc, p.x2 - 2, p.y1 - 8, p.x2 + 8, p.y1 + 2);
		Rectangle(hdc, p.x2 - 2, p.y2 - 2, p.x2 + 8, p.y2 + 8);

		SelectObject(hdc, hPen);
		SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!
		Rectangle(hdc, p.x1 - 3, p.y1 - 3, p.x2 + 3, p.y2 + 3);
	}
	else { // obj-type is LINE
		if (((double)(p.x1-p.x2) / (p.y1-p.y2)) >= 0) {
			if (p.x1 > p.x2) swap(p.x1, p.x2);
			if (p.y1 > p.y2) swap(p.y1, p.y2);
			Rectangle(hdc, p.x1 - 6, p.y1 - 6, p.x1 + 4, p.y1 + 4);
			Rectangle(hdc, p.x2 - 4, p.y2 - 4, p.x2 + 6, p.y2 + 6);
		}
		else { 
			if (p.x1 < p.x2) swap(p.x1, p.x2);
			if (p.y1 > p.y2) swap(p.y1, p.y2);
			Rectangle(hdc, p.x2 - 6, p.y2 - 4, p.x2 + 4, p.y2 + 6);
			Rectangle(hdc, p.x1 - 4, p.y1 - 6, p.x1 + 6, p.y1 + 4);
		}
	}

	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}
void sMode_convert(int& sMode, int x, int y, Position p, Object* obj) {
	
	switch (obj->type) {

		case LINE: {
			Position* pos = &obj->pos;

			if (((double)(pos->x1 - pos->x2) / (pos->y1 - pos->y2)) >= 0) {
				if (x >= p.x1 - 6 && x <= p.x1) {
					if (y >= p.y1 - 6 && y <= p.y1)      sMode = RESIZE_1; // top-left square
					else                                 sMode = -1;
				}
				else if (x >= p.x2 && x <= p.x2 + 6) {
					if (y >= p.y2 && y <= p.y2 + 6)      sMode = RESIZE_4; // bot-right square
					else                                 sMode = -1;
				}
				else if (x > p.x1 && x < p.x2) {
					if (isObject(*pos, MAKELPARAM(x,y), LINE)) sMode = MOVE;     // inside the object
					else                                       sMode = -1;
				}
				else                                     sMode = -1;
			}

			else {
				if (x >= p.x1 - 6 && x <= p.x1) {
					if (y >= p.y2 && y <= p.y2 + 6)      sMode = RESIZE_3; // bot-left square
					else                                 sMode = -1;
				}
				else if (x >= p.x2 && x <= p.x2 + 6) {
					if (y >= p.y1 - 6 && y <= p.y1)      sMode = RESIZE_2; // top-right square
					else                                 sMode = -1;
				}
				else if (x > p.x1 && x < p.x2) {
					if (isObject(*pos, MAKELPARAM(x, y), LINE)) sMode = MOVE;     // inside the object
					else                                        sMode = -1;
				}
				else                                     sMode = -1;
			}
		} break;

		case INSERTTEXT: {
			if (x > p.x1 && x < p.x2) {
				if (y > p.y1 && y < p.y2)            sMode = MOVE;     // inside the object
				else                                 sMode = -1;
			}
			else                                     sMode = -1;
		} break;

		default: { // Ellipse & Rectangle
			if (x >= p.x1 - 6 && x <= p.x1) {
				if (y >= p.y1 - 6 && y <= p.y1)      sMode = RESIZE_1; // top-left square
				else if (y >= p.y2 && y <= p.y2 + 6) sMode = RESIZE_3; // bot-left square
				else                                 sMode = -1;
			}
			else if (x >= p.x2 && x <= p.x2 + 6) {
				if (y >= p.y1 - 6 && y <= p.y1)      sMode = RESIZE_2; // top-right square
				else if (y >= p.y2 && y <= p.y2 + 6) sMode = RESIZE_4; // bot-right square
				else                                 sMode = -1;
			}
			else if (x > p.x1 && x < p.x2) {
				if (y > p.y1 && y < p.y2)            sMode = MOVE;     // inside the object
				else                                 sMode = -1;
			}
			else                                     sMode = -1;

		} break;
	}
}


void createRedo(Work& redo, Object* obj, CHILD_WND_DATA* data) {
	redo.id = INSERT;

	switch (obj->type) {
	case LINE:       redo.obj = obj;      break;
	case ELLIPSE:    redo.obj = obj;      break;
	case RECTANGLE:  redo.obj = obj;      break;
	case INSERTTEXT: redo.obj = obj;      break;
	} 

	if (!data->arrUndo.empty()) data->arrUndo.clear();
}
void doUndo(HWND hwndMDIClient, int mode) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
	if (data != NULL) {
		if (data->arrRedo.size() > 0) {
			Work undo = data->arrRedo.back();

			switch (undo.id) {

			case INSERT: { // -> remove object 
				data->arrObject.pop_back();
				undo.id = DELETE;

				if (mode != SELECT) break;
				HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);
				SetCursor(arrow);
				DestroyCursor(arrow);
			} break;

			case DELETE: { // -> insert object
				Object* xObj = NULL;
				xObj = undo.obj;
				data->arrObject.push_back(xObj);
				undo.id = INSERT;
			} break;

			case CHANGE: { // -> return to previous state
				
				for (int i = 0; i < data->arrObject.size(); i++) {
					if (data->arrObject[i] == undo.obj) {
						swap(undo.cur, undo.obj); 
						swap(undo.obj, data->arrObject[i]); 
						break;
					}
				}

				if (mode != SELECT) break;
				HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);
				SetCursor(arrow);
				DestroyCursor(arrow);
			} break;

			}

			data->arrUndo.push_back(undo);
			data->arrRedo.pop_back();
			InvalidateRect(current, NULL, TRUE);
		}
	}
}
void doRedo(HWND hwndMDIClient, int mode) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
	if (data != NULL) {
		if (data->arrUndo.size() > 0) {
			Work redo = data->arrUndo.back();

			switch (redo.id) {

			case INSERT: { // -> remove object 
				data->arrObject.pop_back();
				redo.id = DELETE;

				if (mode != SELECT) break;
				HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);
				SetCursor(arrow);
				DestroyCursor(arrow);
			} break;

			case DELETE: { // -> insert object
				Object* xObj = NULL;
				xObj = redo.obj;
				data->arrObject.push_back(xObj);
				redo.id = INSERT;
			} break;

			case CHANGE: { // -> return to previous state
				for (int i = 0; i < data->arrObject.size(); i++) {
					if (data->arrObject[i] == redo.obj) {
						swap(redo.cur, redo.obj);
						swap(redo.obj, data->arrObject[i]);
						break;
					}
				}

				if (mode != SELECT) break;
				HCURSOR arrow = LoadCursor(NULL, IDC_ARROW);
				SetCursor(arrow);
				DestroyCursor(arrow);
			} break;

			}

			data->arrRedo.push_back(redo);
			data->arrUndo.pop_back();
			InvalidateRect(current, NULL, TRUE);
		}
	}
}

void checkUndoRedo(HWND hFrameWnd, HWND hWnd, HWND hToolBarWnd) {
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	HMENU hMenu = GetSubMenu(GetMenu(hFrameWnd), menuPos_Edit);

	/*WCHAR x[128];
	wsprintf(x, L"\n\narrUndo.size:  %d\narrRedo.size(): %d\n\n", data->arrUndo.size() > 0, data->arrRedo.size());
	OutputDebugString(x);*/

	// UNDO
	if (data->arrRedo.size() > 0) { // can be Undo !!!
		SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_UNDO, TBSTATE_ENABLED);
		EnableMenuItem(hMenu, ID_EDIT_UNDO, MF_ENABLED | MF_BYCOMMAND);
	}
	else {
		SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_UNDO, TBSTATE_INDETERMINATE);
		EnableMenuItem(hMenu, ID_EDIT_UNDO, MF_GRAYED | MF_BYCOMMAND);
	}

	// REDO
	if (data->arrUndo.size() > 0) { // can be redo !!!
		SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_REDO, TBSTATE_ENABLED);
		EnableMenuItem(hMenu, ID_EDIT_REDO, MF_ENABLED | MF_BYCOMMAND);
	}
	else {
		SendMessage(hToolBarWnd, TB_SETSTATE, ID_EDIT_REDO, TBSTATE_INDETERMINATE);
		EnableMenuItem(hMenu, ID_EDIT_REDO, MF_GRAYED | MF_BYCOMMAND);
	}
}


void saveBitmap(HWND hWnd, LPWSTR szFile) {
	HDC hdc = GetDC(hWnd);
	HDC backbuffDC = CreateCompatibleDC(hdc);

	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right;
	int height = rect.bottom;

	HBITMAP backbuffer = CreateCompatibleBitmap(hdc, width, height);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

	int savedDC = SaveDC(backbuffDC);
	SelectObject(backbuffDC, backbuffer);
	FillRect(backbuffDC, &rect, hBrush);


	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	for (unsigned int i = 0; i < data->arrObject.size(); i++) {
		data->arrObject[i]->draw(hWnd, backbuffDC);
	}

	BitBlt(hdc, 0, 0, width, height, backbuffDC, 0, 0, SRCCOPY);
	RestoreDC(backbuffDC, savedDC);

	BITMAP bmpScreen;

	DWORD dwBmpSize;
	DWORD dwSizeofDIB;
	DWORD dwBytesWritten = 0;

	HANDLE hFile;
	HANDLE hDIB;
	char *lpbitmap;

	SetStretchBltMode(hdc, HALFTONE); //This is the best stretch mode

	GetObject(backbuffer, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	hDIB = GlobalAlloc(GHND, dwBmpSize);
	lpbitmap = (char *)GlobalLock(hDIB);

	GetDIBits(hdc, backbuffer, 0,
		(UINT)bmpScreen.bmHeight,
		lpbitmap, (BITMAPINFO *)&bi, DIB_RGB_COLORS);


	hFile = CreateFile(szFile,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = dwSizeofDIB;
	bmfHeader.bfType = 0x4D42; //BM   

	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	GlobalUnlock(hDIB);
	GlobalFree(hDIB);
	CloseHandle(hFile);

	DeleteObject(backbuffer);
	DeleteObject(hBrush);
	DeleteDC(backbuffDC);
	ReleaseDC(hWnd, hdc);
}
void saveFile(vector <Object*>  arrObject, LPTSTR szFile) {
	fstream f;
	f.open(szFile, ios::trunc | ios::binary | ios::out);
	if (f.is_open()) {
		int arr_size = (int)arrObject.size();
		f.write((char*)&arr_size, sizeof(int));
		for (unsigned int i = 0; i < arrObject.size(); i++) {
			arrObject[i]->save(f);
		}
	} f.close();
}
void openFile(vector <Object*>& arrObject, LPTSTR szFile) {
	fstream f;
	f.open(szFile, ios::binary | ios::in);
	if (f.is_open()) {
		int arr_size;
		//WCHAR s[MAX_LOADSTRING];
		f.read((char*)&arr_size, sizeof(int));
		for (int i = 0; i < arr_size; i++) {
			Object * obj;
			int type;
			f.read((char*)&type, sizeof(int));

			switch (type) {
			case LINE:
				obj = new MyLine;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				/*wsprintf(s, L"\nType = %d, x1 = %d, y1 = %d, x2 = %d, y2 = %d, R = %d, G = %d, B = %d\n",
					obj->type, obj->pos.x1, obj->pos.y1, obj->pos.x2, obj->pos.y2,
					GetRValue(obj->rgbColor), GetGValue(obj->rgbColor), GetBValue(obj->rgbColor));
				OutputDebugString(s);*/
				break;
			case RECTANGLE:
				obj = new MyRectangle;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				/*wsprintf(s, L"\nType = %d, x1 = %d, y1 = %d, x2 = %d, y2 = %d, R = %d, G = %d, B = %d\n",
					obj->type, obj->pos.x1, obj->pos.y1, obj->pos.x2, obj->pos.y2,
					GetRValue(obj->rgbColor), GetGValue(obj->rgbColor), GetBValue(obj->rgbColor));
				OutputDebugString(s);*/
				break;
			case ELLIPSE:
				obj = new MyEllipse;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				/*wsprintf(s, L"\nType = %d, x1 = %d, y1 = %d, x2 = %d, y2 = %d, R = %d, G = %d, B = %d\n",
					obj->type, obj->pos.x1, obj->pos.y1, obj->pos.x2, obj->pos.y2,
					GetRValue(obj->rgbColor), GetGValue(obj->rgbColor), GetBValue(obj->rgbColor));
				OutputDebugString(s);*/
				break;
			case INSERTTEXT:
				obj = new MyText;
				obj->type = type;
				obj->open(f);
				arrObject.push_back(obj);
				break;
			}
		}
		/*wsprintf(s, L"\nCREATED: Numbers of object: %d\n\n\n", arrObject.size());
		OutputDebugString(s);*/
	} f.close();
}
void OnOpen(HWND hWnd, HWND hwndMDIClient, WCHAR* szDrawTitle, WCHAR* szDrawWindowClass) {
	OPENFILENAME ofn; // CTDL dùng cho dialog open
	TCHAR szFile[256];
	TCHAR szFilter[] = TEXT("Draw file (.drw)\0 * .drw\0");

	//HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);

	szFile[0] = '\0';
	// Khởi tạo struct
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; // handle của window cha
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile; // chuỗi tên file trả về
	ofn.nMaxFile = sizeof(szFile);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn)) {
		//... // xử lý mở file
		vector <Object*> arrObject;
		WCHAR FileTitle[MAX_LOADSTRING];
		openFile(arrObject, ofn.lpstrFile);
		onNewDrawWnd(hWnd, hwndMDIClient, szDrawTitle, szDrawWindowClass);
		GetFileTitle(ofn.lpstrFile, FileTitle, (WORD)wcslen(FileTitle));
		HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
		SetWindowText(current, FileTitle);
		CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
		data->arrObject = arrObject;
		arrObject.clear();

		data->saved = true;
		data->exist = true;
		wcscpy(data->path, ofn.lpstrFile);
	}
	else
		;//ErrorHandler();
}
bool OnSave(HWND hWnd, HWND hwndMDIClient) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);
	
	if (data->exist == true)  {
		if (data->saved == false) {
			saveFile(data->arrObject, data->path);
			MessageBox(hWnd, L"Successfully Save File !", L"SAVE FILE NOTICE", MB_OK);

			data->saved = true;
			return true;
		}
		else return true;
	}

	OPENFILENAME ofn; // CTDL dùng cho dialog save
	TCHAR szFile[256];
	TCHAR szFilter[] = TEXT("Draw file (.drw)\0 * .drw\0");

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; // handle của window cha
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile; // chuỗi tên file trả về
	ofn.nMaxFile = sizeof(szFile);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"drw";
	GetWindowText(current, szFile, MAX_LOADSTRING); // Get title of current child window
													//int x = GetFileTitle(ofn.lpstrFile, ofn.lpstrFileTitle, sizeof(ofn.lpstrFile));
	if (GetSaveFileName(&ofn)) {
		saveFile(data->arrObject, ofn.lpstrFile);
		MessageBox(hWnd, L"Successfully Save File !", L"SAVE FILE NOTICE", MB_OK);
			
		data->saved = true;
		data->exist = true;
		wcscpy(data->path, ofn.lpstrFile);

		WCHAR FileTitle[MAX_LOADSTRING];
		GetFileTitle(ofn.lpstrFile, FileTitle, (WORD)wcslen(FileTitle));
		SetWindowText(current, FileTitle);
		return true;
	}
	else return false;//ErrorHandler();
}
bool OnPrint(HWND hWnd, HWND hwndMDIClient) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);

	OPENFILENAME ofn; // CTDL dùng cho dialog save
	TCHAR szFile[256];
	TCHAR szFilter[] = TEXT("Bitmap (.bmp)\0 * .bmp\0");

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; // handle của window cha
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile; // chuỗi tên file trả về
	ofn.nMaxFile = sizeof(szFile);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"bmp";
	GetWindowText(current, szFile, MAX_LOADSTRING); // Get title of current child window

	if (GetSaveFileName(&ofn)) {
		saveBitmap(current, ofn.lpstrFile);
		MessageBox(hWnd, L"Successfully print Bitmap !", L"PRINT BITMAP NOTICE", MB_OK);
		return true;
	}
	else return false;//ErrorHandler();
}
void OnChooseColors(HWND hWnd, HWND hwndMDIClient) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);

	CHOOSECOLOR cc; // CTDL dùng cho dialog ChooseColor
	COLORREF acrCustClr[16]; // Các màu do user định nghĩa
	COLORREF rgbCurrent = RGB(0, 0, 0); // màu được chọn default
										// Khởi tạo struct
	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd; // handle của window cha
	cc.lpCustColors = (LPDWORD)acrCustClr;
	if (data != NULL)
		cc.rgbResult = data->rgbColor; // trả về màu được chọn
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	if (ChooseColor(&cc))
	{
		if (data != NULL) {
			//// xử lý màu được chọn, vd. tạo brush
			data->rgbColor = cc.rgbResult;
		}
	}
	else;//ErrorHandler();
}
void OnChooseFonts(HWND hWnd, HWND hwndMDIClient) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);


	CHOOSEFONT cf;

	//Khởi tạo struct
	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd; // handle của window cha

	if (data != NULL) {
		cf.rgbColors = data->rgbColor;
		cf.lpLogFont = &data->logFont;
	}

	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
	if (ChooseFont(&cf)) {
		if (data != NULL) {
			data->rgbColor = cf.rgbColors;
		}
	}
	else
		;//ErrorHandler();
}



void initFrameWindow(HWND hWnd, HWND& hFrameWnd, HWND& hwndMDIClient, HINSTANCE hInst) {
	hFrameWnd = hWnd;
	// create the MDI Client Window
	CLIENTCREATESTRUCT ccs;
	ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), menuPos_Window);
	ccs.idFirstChild = 50000;

	hwndMDIClient = CreateWindow(
		L"MDICLIENT",
		(LPCTSTR)NULL,
		WS_CHILD | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd,
		(HMENU)NULL,
		hInst,
		(LPVOID)&ccs);

	ShowWindow(hwndMDIClient, SW_SHOW);
}
void initChildWindow(HWND hWnd, int nType) {
	CHILD_WND_DATA *wndData;
	ZeroMemory(&wndData, sizeof(wndData));
	wndData = (CHILD_WND_DATA*)
		VirtualAlloc(NULL, sizeof(CHILD_WND_DATA), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	//wndData = new CHILD_WND_DATA;
	wndData->wndType = nType;
	wndData->hWnd = hWnd;
	wndData->rgbColor = RGB(0, 0, 0);
	wndData->saved = true;

	/*WCHAR s[100]; wsprintf(s, L"\n\n\nHWND = %d\n\n\n", wndData->hWnd); OutputDebugString(s);*/

	SetLastError(0);
	if (SetWindowLongPtr(hWnd, 0, (LONG_PTR)wndData) == 0)

		if (GetLastError() != 0)
		{
			//int a = 0;
		}
}
void onNewDrawWnd(HWND hWnd, HWND& hwndMDIClient, WCHAR* szDrawTitle, WCHAR* szDrawWindowClass) {
	static int i = 1;
	wsprintf(szDrawTitle, L"Noname-%d.drw", i);
	MDICREATESTRUCT mdiCreate;
	ZeroMemory(&mdiCreate, sizeof(MDICREATESTRUCT));
	mdiCreate.szClass = szDrawWindowClass;
	mdiCreate.szTitle = szDrawTitle;
	mdiCreate.x = CW_USEDEFAULT;
	mdiCreate.y = CW_USEDEFAULT;
	mdiCreate.cx = 800;
	mdiCreate.cy = 600;
	mdiCreate.style = 0;
	mdiCreate.lParam = NULL;
	SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiCreate);

	i++;
}


void changeColor(HWND hwndMDIClient, int r, int g, int b) {
	HWND current = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, NULL);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(current, 0);

	if (data != NULL) {
		data->rgbColor = RGB(r, g, b);
	}
}
