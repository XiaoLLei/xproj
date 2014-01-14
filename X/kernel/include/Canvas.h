#pragma once
#include "xKernel/IxCanvas.h"

class CxCanvas : public IxCanvas
{
public:
    CxCanvas();
    virtual ~CxCanvas();

public:
    // interface of IxCanvas
    HRESULT Create(HDC hdc, SIZE sz);
    HRESULT FillSolidRect(RECT rc, COLORREF clr);

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