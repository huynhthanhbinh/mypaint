#include "stdafx.h"
#include "1653006_MyObject.h"

void MyLine::draw(HWND hWnd) {
	HDC hdc = GetDC(hWnd);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	HPEN hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
	SelectObject(hdc, hPen);
	
	MoveToEx(hdc, pos.x1, pos.y1, NULL);
	LineTo(hdc, pos.x2, pos.y2);
	ReleaseDC(hWnd, hdc);
}
void MyRectangle::draw(HWND hWnd) {
	HDC hdc = GetDC(hWnd);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	HPEN hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
	SelectObject(hdc, hPen);

	MoveToEx(hdc, pos.x1, pos.y1, NULL);
	Rectangle(hdc, pos.x1, pos.y1, pos.x2, pos.y2);
	ReleaseDC(hWnd, hdc);
}
void MyEllipse::draw(HWND hWnd) {
	HDC hdc = GetDC(hWnd);
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	HPEN hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
	SelectObject(hdc, hPen);

	MoveToEx(hdc, pos.x1, pos.y1, NULL);
	Ellipse(hdc, pos.x1, pos.y1, pos.x2, pos.y2);
	ReleaseDC(hWnd, hdc);
}
void MyText::draw(HWND hWnd) {

}


void OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	/*RECT rect; GetClientRect(hWnd, &rect);*/
	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	//SelectObject(hdc, hBrush);


	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	HPEN hPen = CreatePen(PS_SOLID, 2, data->rgbColor);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // for NULL BRUSH OBJECT !!!!!


	for (unsigned int i = 0; i < data->page.line.size(); i++) {
		MoveToEx(hdc, data->page.line[i].x1, data->page.line[i].y1, NULL);
		LineTo(hdc, data->page.line[i].x2, data->page.line[i].y2);
	}
	for (unsigned int i = 0; i < data->page.rectangle.size(); i++) {
		//MoveToEx(hdc, data->page.rectangle[i].x1, data->page.rectangle[i].y1, NULL);
		Rectangle(hdc, data->page.rectangle[i].x1, data->page.rectangle[i].y1, data->page.rectangle[i].x2, data->page.rectangle[i].y2);
	}
	for (unsigned int i = 0; i < data->page.ellipse.size(); i++) {
		//MoveToEx(hdc, data->page.ellipse[i].x1, data->page.ellipse[i].y1, NULL);
		Ellipse(hdc, data->page.ellipse[i].x1, data->page.ellipse[i].y1, data->page.ellipse[i].x2, data->page.ellipse[i].y2);
	}

	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);
}
void OnLButtonUp(Position pos, HWND hWnd, int mode) {
	CHILD_WND_DATA * data = (CHILD_WND_DATA *)GetWindowLongPtr(hWnd, 0);
	WCHAR s[100];
	switch (mode) {
	case LINE:
		if (!checkSamePoint(pos))
			data->page.line.push_back(pos);
		break;
	case RECTANGLE:
		if (!checkSamePoint(pos))
			data->page.rectangle.push_back(pos);
		break;
	case ELLIPSE:
		if (!checkSamePoint(pos))
			data->page.ellipse.push_back(pos);
		break;
	}
	wsprintf(s, L"\n\n\nnLine: %d \nnRectangle: %d \nnEllipse: %d\n\n\n",
		data->page.line.size(), data->page.rectangle.size(), data->page.ellipse.size());
	OutputDebugString(s);
	return;
}
void OnLButtonDown(HWND hWnd, LPARAM lParam, Position& pos) {
	// Muốn xài các hàm Win API về đồ họa phải khai báo HDC trước (WM_PAINT: khai báo sẵn)
	HDC hdc;           // Handle of Device Context
	hdc = GetDC(hWnd); // ...

	pos.x1 = pos.x2 = LOWORD(lParam);
	pos.y1 = pos.y2 = HIWORD(lParam);

	ReleaseDC(hWnd, hdc);
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
		return true;
	case RECTANGLE:
		Rectangle(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		return true;
	case ELLIPSE:
		Ellipse(dc, pos.x1, pos.y1, pos.x2, pos.y2);
		return true;
	} return false;
}
bool checkSamePoint(Position pos) { // leak memory !!! 
	if (pos.x1 == pos.x2 && pos.y1 == pos.y2)
		return true;
	return false;
}