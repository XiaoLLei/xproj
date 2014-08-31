#pragma once

class CMsgWnd
{
public:
	CMsgWnd();
	~CMsgWnd();

	BOOL Create();
	HWND GetHwnd();

	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

private:
	ATOM _register_class();

private:
	HWND	m_hWnd;

	static	ATOM	s_atom;
};