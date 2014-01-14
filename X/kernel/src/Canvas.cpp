#include "stdafx.h"
#include "Canvas.h"

using namespace Gdiplus;

CxCanvas::CxCanvas()
    : m_szSize(0, 0)
    , m_hBitmap(NULL)
    , m_hOldBitmap(NULL)
    , m_hDC(NULL)
    , m_pvBits(NULL)
{}

CxCanvas::~CxCanvas()
{
    _destroy();
}

HRESULT CxCanvas::Create(HDC hdc, SIZE sz)
{
    if (m_szSize == sz)
    {
        return E_FAIL;
    }

    _destroy();

    m_hBitmap = _create_32bit_bitmap(hdc, sz);

    m_hDC = ::CreateCompatibleDC(hdc);

    m_hOldBitmap = (HBITMAP)::SelectObject(m_hDC, m_hBitmap);

    m_szSize = sz;

    return S_OK;
}

HRESULT CxCanvas::FillSolidRect(RECT rc, COLORREF clr)
{
    if (!m_hDC)
    {
        return E_FAIL;
    }

    Graphics oGraphics(m_hDC);

    SolidBrush oBrush(Color((LOBYTE(clr >> 16)), GetRValue(clr), GetGValue(clr), GetBValue(clr)));

    oGraphics.FillRectangle(&oBrush, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);

    return S_OK;
}

VOID CxCanvas::_destroy()
{
    if (m_hOldBitmap)
    {
        ::SelectObject(m_hDC, m_hOldBitmap);
        m_hOldBitmap = NULL;
    }

    if (m_hDC)
    {
        ::DeleteDC(m_hDC);
        m_hDC = NULL;
    }

    if (m_hBitmap)
    {
        ::DeleteObject(m_hBitmap);
        m_hBitmap = NULL;
    }

    m_pvBits = NULL;
    m_szSize.SetSize(0 ,0);
}

HBITMAP CxCanvas::_create_32bit_bitmap(HDC hdc, SIZE& sz)
{
    BITMAPINFOHEADER bih = {0};
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = sz.cx;
    bih.biHeight = sz.cy;
    bih.biPlanes = 1;
    bih.biBitCount = 32;
    bih.biCompression = BI_RGB;
    return ::CreateDIBSection(hdc, (PBITMAPINFO)&bih, DIB_RGB_COLORS, &m_pvBits, NULL, 0);
}