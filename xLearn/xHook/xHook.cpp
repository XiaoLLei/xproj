// xHook.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "xHook.h"


// ���ǵ���������һ��ʾ��
//XHOOK_API int nxHook=0;

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� xHook.h
// CxHook::CxHook()
// {
// 	return;
// }


namespace xTest
{
    DWORD g_dwThreadId = 0;

    HHOOK g_hMouseHook = NULL;

}

EXTERN_C XHOOK_API LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    UINT                uMsg        = (UINT)wParam;
    LPMOUSEHOOKSTRUCT   pHookData   = (LPMOUSEHOOKSTRUCT)lParam;

    if (nCode < 0)
    {
        return CallNextHookEx(xTest::g_hMouseHook, nCode,  wParam, lParam);
    }

    if (pHookData)
    {
        if (uMsg == WM_MOUSEMOVE
            || uMsg == WM_NCMOUSEMOVE)
        {
            if (xTest::g_dwThreadId)
                ::PostThreadMessage(xTest::g_dwThreadId, WM_USER+1, 0, 0);
        }
    }

    return CallNextHookEx(xTest::g_hMouseHook, nCode,  wParam, lParam);
}

XHOOK_API BOOL SetHook(DWORD tid)
{
    xTest::g_dwThreadId = tid;

    //xTest::g_hMouseHook = ::SetWindowsHookEx(WH_MOUSE, xTest::MouseHookProc, ::GetModuleHandle(L"xHook.dll"), 0);

    return TRUE;
}