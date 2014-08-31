#include "stdafx.h"
#include "MsgWnd.h"

static wchar_t kClassName[] = _T("x_msg_wnd_");

ATOM CMsgWnd::s_atom = NULL;

CMsgWnd::CMsgWnd()
	: m_hWnd(NULL)
{
	if (!s_atom)
	{
		_register_class();
	}
}

CMsgWnd::~CMsgWnd()
{

}

BOOL CMsgWnd::Create()
{
	m_hWnd = CreateWindow(kClassName, L"", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, HWND_MESSAGE, NULL, NULL, NULL);

	return !!m_hWnd;
}

HWND CMsgWnd::GetHwnd()
{
	return m_hWnd;
}

ATOM CMsgWnd::_register_class()
{
	HINSTANCE hInst = (HINSTANCE)::GetModuleHandle(NULL);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= kClassName;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

LRESULT CMsgWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}