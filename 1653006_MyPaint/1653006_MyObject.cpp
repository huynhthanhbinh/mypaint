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

}


void OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	/*RECT rect; GetClientRect(hWnd, &rect);*/
	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	//SelectObject(hdc, hBrush);

	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	for (unsigned int i = 0; i < data->arrObject.size(); i++) {
		data->arrObject[i]->draw(hWnd, hdc);
	}

	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);
}
void OnLButtonUp(Position pos, HWND hWnd, int mode) {
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	WCHAR s[100];
	switch (mode) {
	case LINE:
		if (!checkSamePoint(pos)) {
			//data->page.line.push_back(pos);
			MyLine *l = new MyLine; 
			l->pos = pos;
			l->type = LINE;
			l->rgbColor = data->rgbColor;
			data->arrObject.push_back(l);
		}
		break;
	case RECTANGLE:
		if (!checkSamePoint(pos)) {
			//data->page.rectangle.push_back(pos);
			MyRectangle * r = new MyRectangle;
			r->pos = pos;
			r->type = RECTANGLE;
			r->rgbColor = data->rgbColor;
			data->arrObject.push_back(r);
		}
		break;
	case ELLIPSE:
		if (!checkSamePoint(pos)) {
			//data->page.ellipse.push_back(pos);
			MyEllipse * e = new MyEllipse;
			e->pos = pos;
			e->type = ELLIPSE;
			e->rgbColor = data->rgbColor;
			data->arrObject.push_back(e);
		}
		break;
	}
	wsprintf(s, L"\n\n\nNumbers of object: %d\n\n\n", data->arrObject.size()); OutputDebugString(s);
	return;
}
void OnLButtonDown(HWND hWnd, LPARAM lParam, Position& pos) {
	// Muốn xài các hàm Win API về đồ họa phải khai báo HDC trước (WM_PAINT: khai báo sẵn)
	//HDC hdc;           // Handle of Device Context
	//hdc = GetDC(hWnd); // ...

	pos.x1 = pos.x2 = LOWORD(lParam);
	pos.y1 = pos.y2 = HIWORD(lParam);

	//ReleaseDC(hWnd, hdc);
}
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam, Position& pos, int mode) {
	if ((wParam & MK_LBUTTON) == MK_LBUTTON) {
		HDC dc = GetDC(hWnd);
		SetROP2(dc, R2_NOTXORPEN);

		drawObject(hWnd, dc, pos, mode);

		// Cập nhật điểm mới !!!
		pos.x2 = LOWORD(lParam);
		pos.y2 = HIWORD(lParam);

		// Vẽ đường thẳng mới (do mode NOT_XOR)
		drawObject(hWnd, dc, pos, mode);

		ReleaseDC(hWnd, dc);
	}
}
bool drawObject(HWND hWnd, HDC dc, Position& pos, int mode) {
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	HPEN hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
	SelectObject(dc, hPen);

	MoveToEx(dc, pos.x1, pos.y1, NULL);
	switch (mode) {
	case LINE:
		LineTo(dc, pos.x2, pos.y2);
		DeleteObject(hPen);
		return true;
	case RECTANGLE:
		Rectangle(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		DeleteObject(hPen);
		return true;
	case ELLIPSE:
		Ellipse(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		DeleteObject(hPen);
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

