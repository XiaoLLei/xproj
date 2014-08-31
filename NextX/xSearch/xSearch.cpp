// xSearch.cpp : Implementation of WinMain


#include "stdafx.h"
#include "AutoDo.h"
#include "mainframe/mainframe.h"


// The module attribute causes WinMain to be automatically implemented for you
[ module(exe, uuid = "{9406B3FB-829B-4BBC-A14C-C8F2152BE90E}", 
    name = "xSearch", 
    helpstring = "xSearch 1.0 Type Library") ]
class CxSearchModule
{
public:
    // Override CAtlExeModuleT members
    HRESULT Run(int nShowCmd)
    {
        static const wchar_t kMutexName[] = _T("Global\\Yuer-xSearch-Start");

        HANDLE hMutex = ::CreateMutex(NULL, FALSE, kMutexName);
        if (GetLastError() == ERROR_ALREADY_EXISTS)  
        {
            ::CloseHandle(hMutex);
            return S_OK;
        }
        else
        {
            ::CloseHandle(hMutex);
        }

        CAutoDo oAuto;

        CMainFrame frame;
        frame.show();

        CComPtr<IServiceThreadMgr> pServiceThreadMgr;
        Util::Com::GetService(__uuidof(IServiceThreadMgr), (VOID **)&pServiceThreadMgr);
        if (pServiceThreadMgr)
            pServiceThreadMgr->RunUIMessageLoop();

        return S_OK;
    }
};

