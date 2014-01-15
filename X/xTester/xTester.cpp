// xTester.cpp : Implementation of WinMain


#include "stdafx.h"
#include "AutoDo.h"
#include "xCommon/IxMessageLoop.h"


// The module attribute causes WinMain to be automatically implemented for you
[ module(exe, uuid = "{4D261217-3F7C-41D6-BD07-FAB40D26D930}", 
         name = "xTester", 
         helpstring = "xTester 1.0 Type Library") ]
class CxTesterModule
{
public:
    // Override CAtlExeModuleT members
    HRESULT Run(int nShowCmd)
    {
        CxAutoDo _autoDo;

        xDll::XDll_RegisterObjectsAndServices();
        xKernel::xKernel_RegisterObjectsAndServices();

        //CComPtr<IxTest> spTest;
        //::xCommon::CreateObjectByIID(__uuidof(IxTest), (void**)&spTest);
        //if (spTest)
        //    spTest->Test();

        //CComPtr<IxTestService> spTestService;
        //::xCommon::GetService(__uuidof(IxTestService), (void**)&spTestService);
        //if (spTestService)
        //    spTestService->Test();

        CComPtr<IxWnd> spWnd;
        ::xCommon::CreateObjectByIID(__uuidof(IxWnd), (void**)&spWnd);
        if (spWnd)
            spWnd->CreateWnd();

        CComPtr<IxBrushView> spBrushView;
        ::xCommon::CreateObjectByIID(__uuidof(IxBrushView), (void**)&spBrushView);
        if (spBrushView)
            spBrushView->SetColor(RGB(100,100,200));

        CComQIPtr<IxView> spView = spBrushView;
        if (spView)
        {
            spView->SetBoxRect(CRect(0, 0, 800, 600));
        }

        CComQIPtr<IxNode> spNode = spWnd;
        if (spNode)
            spNode->AddChild(CComQIPtr<IxNode>(spBrushView));

        CComPtr<IxMessageLoop> spLoop;
        ::xCommon::GetService(__uuidof(IxMessageLoop), (void**)&spLoop);
        if (spLoop)
            spLoop->Run();

        return S_OK;
    }
};
