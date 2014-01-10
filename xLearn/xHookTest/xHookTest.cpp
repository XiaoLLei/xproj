// xHookTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "..\xHook\xHook.h"


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    HINSTANCE hinstDLL = ::LoadLibrary(L"E:\\TestCode\\xproj\\xLearn\\Debug\\xHook.dll"); 

    SetHook(::GetCurrentThreadId());


    HOOKPROC fnMouseProc = (HOOKPROC)GetProcAddress(hinstDLL, "_MouseHookProc@12"); 
    ::SetWindowsHookEx(WH_MOUSE, fnMouseProc, hinstDLL, 0); 

    //::SetWindowsHookEx(WH_MOUSE, fnMouseProc, ::GetModuleHandle(L"xHook.dll"), 0);

    //cin.get();

    MSG msg = {0};

    int count = 0;

    for (;;)
    {
        if (::PeekMessage(&msg, NULL,  0, 0, PM_REMOVE))
        {
            if (msg.message == WM_USER + 1)
            {
                std::cout<<"mouse move "<<++count<<std::endl;
            }
            //::TranslateMessage(&msg);
            //::DispatchMessage(&msg);
        }
    }

    return 0;
}
