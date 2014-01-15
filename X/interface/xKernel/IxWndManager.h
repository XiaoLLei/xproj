#pragma once

#include "IxWnd.h"

[
    object,
    uuid("49AE78E5-3029-4c51-AD77-8F0E1B4AF5EA"),
    pointer_default(unique)
]
__interface IxWndManager : IUnknown
{
    HRESULT AddWnd(IxWnd* pWnd);
    HRESULT RemoveWnd(IxWnd* pWnd);
};