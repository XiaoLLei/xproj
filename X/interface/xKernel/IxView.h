#pragma once

[
    object,
    uuid("E93411C7-0E73-431b-AFE5-73D881A82C21"),
    pointer_default(unique)
]
__interface IxView : IUnknown
{
    HRESULT GetBoxRect(LPRECT lprcBox);
    HRESULT SetBoxRect(RECT rcBox);

    HRESULT GetSize(LPSIZE lpszSize);
    HRESULT SetSize(SIZE szSize);

    HRESULT GetPosition(LPPOINT pptPos);
    HRESULT SetPosition(POINT ptPos);

    HRESULT GetAlpha(LPBYTE pbyAlpha);
    HRESULT SetAlpha(BYTE byAlpha);

    HRESULT GetShowState(LPBOOL pbShow);
    HRESULT SetShowState(BOOL bShow);

    HRESULT GetVisibleState(LPBOOL pbVisible);

    HRESULT SetFocus();
    HRESULT GetFocusState(LPBOOL bFocus);
};