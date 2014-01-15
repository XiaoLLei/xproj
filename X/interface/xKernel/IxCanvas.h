#pragma once

[
    object,
    uuid("283CDDB0-A5A5-41e0-ADF6-7825EA0024E8"),
    pointer_default(unique)
]
__interface IxCanvas : IUnknown
{
    HRESULT Create(HDC hdc, SIZE sz);
    HRESULT GetSize(LPSIZE lpszSize);

    HRESULT FillSolidRect(RECT rc, COLORREF clr);

    HRESULT PaintToDC(POINT ptSrc, HDC hdc, RECT rcDest);
    HRESULT BlendToDC(RECT rcSrc, HDC hdc, RECT rcDest, BYTE byAlpha);
};