#include "stdafx.h"
#include "help.h"

namespace util
{
    HRESULT GetService(REFIID iid, void** ppOut)
    {
        CComPtr<IXuiLib> spLib;
        ::Util::Com::GetService(__uuidof(IXuiLib), (VOID**)&spLib);
        if (spLib)
            return spLib->GetService(iid, ppOut);
        return E_FAIL;
    }

    CStringW GetModuleDir(HMODULE  hModule)
    {
        WCHAR strFullPath[MAX_PATH] = {0};
        ::GetModuleFileName(hModule, strFullPath, MAX_PATH);
        strFullPath[MAX_PATH - 1] = L'\0';
        PathRemoveFileSpec(strFullPath);
        return CStringW(strFullPath);
    }

    HWND GetCanvasWnd(IElement* pUIObj)
    {
        HWND hWnd = NULL;

        CComQIPtr<IFrame> pFrame(pUIObj);
        if (pFrame)
        {
            CComPtr<IxDocument> spDoc;
            pFrame->GetDocument(&spDoc);
            if (spDoc)
            {
                CComPtr<IxCanvas> pCanvas;
                spDoc->GetCanvas(&pCanvas);
                if (pCanvas)
                    hWnd = pCanvas->GetHWnd();
            }
        }
        else
        {
            CComQIPtr<IxCanvas> pWin(pUIObj);
            if (pWin)
                hWnd = pWin->GetHWnd();
        }

        return hWnd;
    }
}