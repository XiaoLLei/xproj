#pragma once

namespace util
{
    HRESULT GetService(REFIID iid, void** ppOut);

    CStringW GetModuleDir(HMODULE  hModule);

    HWND GetCanvasWnd(IElement* pUIObj);
}