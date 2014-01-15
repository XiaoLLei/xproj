#pragma once
#include "xKernel/IxCanvas.h"

[
    default(IxCanvas),
    threading(free),
    uuid("9369E378-1679-44c4-A4C1-E1F32935F9B9"),
    coclass
]
class CxCanvas : public IxCanvas
{
public:
    CxCanvas();
    virtual ~CxCanvas();

public:
    // interface of IxCanvas
    HRESULT Create(HDC hdc, SIZE sz);
    HRESULT GetSize(LPSIZE lpszSize);
    HRESULT FillSolidRect(RECT rc, COLORREF clr);
    HRESULT PaintToDC(POINT ptSrc, HDC hdc, RECT rcDest);
    HRESULT BlendToDC(RECT rcSrc, HDC hdc, RECT rcDest, BYTE byAlpha);

protected:
    VOID    _destroy();
    HBITMAP _create_32bit_bitmap(HDC hdc, SIZE& sz);

protected:
    CSize       m_szSize;
    HBITMAP     m_hBitmap;
    HBITMAP     m_hOldBitmap;
    HDC         m_hDC;
    VOID*       m_pvBits;
};