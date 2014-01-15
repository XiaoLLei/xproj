#pragma once

[
    object,
    uuid("A0644898-19C6-416e-BEF1-C74353021D3B"),
    pointer_default(unique)
]
__interface IxWndProc : IUnknown
{
    HRESULT ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* plRet, LPBOOL pbHandle);
};