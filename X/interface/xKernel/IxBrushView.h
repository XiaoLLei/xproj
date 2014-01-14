#pragma once

[
    object,
    uuid("79831E87-2377-4214-B3DE-4E5843926DEF"),
    pointer_default(unique)
]
__interface IxBrushView : IUnknown
{
    HRESULT GetColor(LPCOLORREF lpClr);
    HRESULT SetColor(COLORREF clr);
};