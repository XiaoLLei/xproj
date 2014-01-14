#pragma once

[
    object,
    uuid("283CDDB0-A5A5-41e0-ADF6-7825EA0024E8"),
    pointer_default(unique)
]
__interface IxCanvas : IUnknown
{
    HRESULT Create(HDC hdc, SIZE sz);
    HRESULT FillSolidRect(RECT rc, COLORREF clr);
};