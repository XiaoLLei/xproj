#include "stdafx.h"
#include "publicdef/objectfactory/ObjectRegister.h"
#include "AutoDo.h"

#ifdef _DEBUG
#define SKIN_PATH_SUFFIX             L"\\..\\resource\\skin\\"
#define PACKAGE_SUFFIX               L"\\"
#else
#define SKIN_PATH_SUFFIX             L"\\resource\\skin\\"
#define PACKAGE_SUFFIX               L"\\"
#endif

CAutoDo::CAutoDo()
{
    ::CoInitialize(NULL);
    ::OleInitialize(NULL);

    // 注册类表
    _register_obj_ser_();

    // 初始化XUI
    CComPtr<IXuiLib> spLib;
    ::Util::Com::GetService(&spLib);
    if (spLib)
        spLib->Initialize();

    // 初始化皮肤库
    _initSkin();

    // 初始化线程管理
    CComPtr<IServiceThreadMgr> pServiceThreadMgr;
    Util::Com::GetService(__uuidof(IServiceThreadMgr), (VOID **)&pServiceThreadMgr);
    if (pServiceThreadMgr)
        pServiceThreadMgr->RegisterUIThread(::GetCurrentThreadId(), "Main UI Thread");
}

CAutoDo::~CAutoDo()
{
    // 反初始化XUI
    CComPtr<IXuiLib> spLib;
    ::Util::Com::GetService(&spLib);
    if (spLib)
        spLib->Uninitialize();

    Util::Com::ClearService();
    ::OleUninitialize();
    ::CoUninitialize();
}

void CAutoDo::_initSkin()
{
    CComPtr<IxSkinMgr> spSkinMgr;
    ::util::GetService(__uuidof(IxSkinMgr), (VOID **)&spSkinMgr);

    if (spSkinMgr)
    {
        CStringW strModulePath = util::GetModuleDir(NULL);
        strModulePath.Append(SKIN_PATH_SUFFIX);
        CStringW strSkinPath = strModulePath;
        strSkinPath.Append(PACKAGE_SUFFIX);

        spSkinMgr->RegSymbolPath(CComBSTR(L"skin"), CComBSTR(strSkinPath), 0);
        spSkinMgr->RegConfigPath(CComBSTR(L"skin"), 0, CComBSTR(L"config.xml"));
        spSkinMgr->RegStylePath(CComBSTR(L"skin"), 0, CComBSTR(L"style.xml"));

        spSkinMgr->InitSkin(0);
    }
}

void CAutoDo::_register_obj_ser_()
{
    ////////////////////////////////////////service table definition//////////////////////////////////
    ObjectInfo objTable[] =
    {
        DEFITEM(DEFGUID(CC,04,A4,4F,92,FC,45,40,A2,E0,C6,56,D0,7F,18,9D), DEFGUID(91,6B,B0,E4,87,15,41,F6,BB,DE,49,D5,E4,A8,9C,AA), "bdcommon.dll",     "IBDArray_CBDArray")
        DEFITEM(DEFGUID(10,d7,77,83,a7,db,46,a8,9d,ce,4f,54,f7,ae,6b,c8), DEFGUID(F6,29,38,67,7A,2F,47,ed,85,30,D5,74,B0,58,97,15), "bdcommon.dll",     "IBDTree_CBDTree")
        DEFITEM(DEFGUID(CB,4B,D3,FB,CE,BA,4b,5d,95,9E,5E,B0,26,7F,86,55), DEFGUID(E4,8F,3F,50,5D,D8,4c,04,96,31,FC,EA,37,C8,AC,EF), "bdcommon.dll",     "IBDBuffer_CBDBuffer")
        DEFITEM(DEFGUID(44,01,43,58,3A,9A,4f,b2,92,C6,B2,A4,AA,26,72,1E), DEFGUID(E4,68,9A,82,71,1E,4d,f7,8B,16,39,F0,B9,4B,4A,77), "bdcommon.dll",     "IBDStrMap_CBDStrMap")
        DEFITEM(DEFGUID(76,11,5F,42,6E,8B,41,3a,B9,1C,8B,47,6B,3A,5E,B4), DEFGUID(EA,17,F3,EC,AA,A4,4d,cb,A7,07,57,14,58,8A,B1,03), "bdcommon.dll",     "IBDIntMap_CBDIntMap")
        DEFITEM(DEFGUID(62,AF,FA,DF,CC,EF,40,a3,B2,B2,D1,75,EE,DF,28,8C), DEFGUID(0F,24,75,A6,83,EB,44,24,A5,23,84,34,A6,DE,00,EB), "bdcommon.dll",     "IBDUrl_CBDUrl")
        DEFITEM(DEFGUID(41,4F,22,89,FD,FB,41,6b,A3,C4,25,B8,9F,D5,F5,AE), DEFGUID(B1,C5,FB,E8,B3,45,48,c6,98,4B,9E,36,DD,6D,83,C6), "bdcommon.dll",     "IBDIcon")

        DEFITEM(DEFGUID(52,66,77,DD,35,95,4c,dd,AF,DA,06,7B,9C,71,A4,1C), DEFGUID(A0,F8,11,53,DB,46,41,3f,9E,BF,DC,8E,14,22,D5,72), "bdxui.dll",        "IxFocusMgr")
        DEFITEM(DEFGUID(7F,4D,E6,19,AD,25,47,ad,AE,F1,B7,04,80,B3,EF,CB), DEFGUID(68,52,60,E7,6A,1D,45,33,83,08,24,53,16,6B,EF,70), "bdxui.dll",        "IxRender")
        DEFITEM(DEFGUID(B6,E5,2E,15,3B,C6,48,e8,8A,17,23,25,5B,96,05,4F), DEFGUID(EE,1B,4F,9C,16,E0,4b,45,8C,8B,69,F2,0E,49,FD,D4), "bdxui.dll",        "ITexture")
        DEFITEM(DEFGUID(E9,78,05,04,12,58,4c,1d,84,4F,F2,6F,4E,30,9C,DE), DEFGUID(61,E0,29,47,09,E9,47,5f,B3,D5,D4,9C,C0,2A,E3,3A), "bdxui.dll",        "IxTexture2")
        DEFITEM(DEFGUID(E7,49,09,77,FA,D1,48,9c,BE,9C,54,8B,6C,A0,EB,1B), DEFGUID(FB,56,61,63,13,71,42,3b,8B,E3,27,0F,EA,0B,08,1D), "bdxui.dll",        "IxFont")
        DEFITEM(DEFGUID(40,8C,A6,24,39,B5,4c,f7,A1,C4,8B,43,E0,63,2F,08), DEFGUID(6E,3F,F4,CE,35,81,49,aa,9D,BF,9C,14,85,01,D8,19), "bdxui.dll",        "IxText")
        DEFITEM(DEFGUID(CD,98,41,B2,2C,FA,44,D0,8C,30,FE,4D,34,14,48,B5), DEFGUID(64,93,A1,25,0A,98,4A,51,A9,C3,35,55,46,8E,30,D1), "bdxui.dll",        "IBDStateAutoTransMgr")
        DEFITEM(DEFGUID(C8,61,32,A5,1E,D9,45,da,A0,5A,EE,C6,54,6A,01,33), DEFGUID(92,E7,B4,2A,2B,86,4c,fc,B3,C9,ED,0F,D4,AA,74,BE), "bdxui.dll",        "IFrame")
        DEFITEM(DEFGUID(32,9D,19,D8,49,31,49,4a,89,B6,5B,AE,85,6C,04,32), DEFGUID(1F,0D,5B,E8,1E,B6,47,06,BC,83,43,F2,85,B8,C6,19), "bdxui.dll",        "IBlockLevel")
        DEFITEM(DEFGUID(92,D5,51,66,16,E4,45,a8,81,55,E5,94,18,57,66,40), DEFGUID(03,38,2B,00,7E,2F,47,e2,BF,7E,43,8C,D1,3A,6D,59), "bdxui.dll",        "ISysBtnClose")
        DEFITEM(DEFGUID(E4,49,E9,18,26,D9,40,87,B7,F2,17,2B,C4,0B,E2,FD), DEFGUID(FC,FB,B4,AB,84,3A,48,7e,AD,7D,25,44,70,90,75,FD), "bdxui.dll",        "ISysBtnMin")
        DEFITEM(DEFGUID(18,3A,C0,A5,94,42,4e,60,9C,2E,C2,50,30,5C,12,6E), DEFGUID(D4,A9,CB,4E,3C,23,41,86,96,18,86,75,70,CF,36,B2), "bdxui.dll",        "ISysBtnMax")
        DEFITEM(DEFGUID(1C,C0,AE,0B,66,F0,49,32,8A,F1,0E,D7,A9,BC,02,46), DEFGUID(F7,C6,49,35,4E,AB,45,3f,82,12,D6,28,F5,14,3F,42), "bdxui.dll",        "IBDSplitter")
        DEFITEM(DEFGUID(37,5B,EF,41,2D,82,45,3e,97,53,DB,44,06,27,4D,74), DEFGUID(FB,93,90,E2,C8,DD,41,49,B3,14,A2,B3,2E,D2,4B,31), "bdxui.dll",        "IxButton")
        DEFITEM(DEFGUID(B9,50,74,80,00,66,46,de,A2,8C,C4,B4,A1,C3,29,82), DEFGUID(6C,5D,BD,31,5B,75,45,a7,B8,45,23,FC,01,CB,64,1A), "bdxui.dll",        "IInlineLevel")
        DEFITEM(DEFGUID(6B,B3,D8,9D,73,7E,43,d4,8A,34,42,6A,E9,0F,35,BE), DEFGUID(EA,F9,AB,18,29,F9,40,8b,8F,4F,2B,70,66,20,B7,C3), "bdxui.dll",        "IxDocument")
        DEFITEM(DEFGUID(2D,D6,06,BC,48,31,4b,0e,84,B1,39,2A,32,D3,84,B8), DEFGUID(45,D8,24,1F,99,20,41,c9,89,70,45,64,F0,19,3C,43), "bdxui.dll",        "IxCanvas")
        DEFITEM(DEFGUID(1C,D2,D2,03,B5,BB,4f,ce,B4,65,17,37,84,EA,19,8F), DEFGUID(81,D0,01,38,D7,BB,4a,71,95,47,6F,FF,85,A8,EA,1F), "bdxui.dll",        "IxShadow")
        DEFITEM(DEFGUID(71,37,E6,FE,76,92,48,e2,A3,1B,F8,A1,D7,17,34,A0), DEFGUID(3E,A0,AE,63,6D,1E,48,0f,B2,63,F7,6A,62,F4,E5,5F), "bdxui.dll",        "IxLayoutMgr")
        DEFITEM(DEFGUID(78,53,0C,BC,6E,94,4d,de,82,CF,34,2D,34,47,58,4D), DEFGUID(E3,44,2C,8A,7F,E2,4e,0b,87,27,07,89,90,C3,50,0E), "bdxui.dll",        "IScrollBar")
        DEFITEM(DEFGUID(0B,9E,36,3B,6F,58,42,ff,B6,65,E1,F5,1A,55,2E,AB), DEFGUID(13,C7,F2,B4,25,49,4d,6e,9C,41,0A,80,99,58,67,16), "bdxui.dll",        "IScrollView")
        DEFITEM(DEFGUID(6B,D1,7B,EE,44,41,44,b1,A0,1F,D9,6F,28,37,2A,C8), DEFGUID(3B,8F,C2,3D,12,C0,4f,51,92,CB,18,23,FA,9E,E0,91), "bdxui.dll",        "IxTabItem")
        DEFITEM(DEFGUID(5A,36,6F,54,3C,9A,4a,08,8A,12,C7,46,96,B3,01,7B), DEFGUID(1C,2B,A0,90,2B,35,44,6c,96,F7,62,C4,6E,04,DD,73), "bdxui.dll",        "IxTabBody")
        DEFITEM(DEFGUID(3C,71,9E,16,63,D6,4f,46,8C,6B,FF,DE,35,30,8F,CC), DEFGUID(A6,DF,30,00,0A,A3,43,a0,B5,FF,E4,C5,0E,7C,99,B2), "bdxui.dll",        "IxTab")
        DEFITEM(DEFGUID(23,F1,E1,B9,4E,F4,4A,EC,A7,75,E6,28,01,27,F9,4B), DEFGUID(FA,46,03,80,18,02,49,C3,A1,1A,CE,58,33,57,BB,A3), "bdxui.dll",        "IBrowserTabCtrl")
        DEFITEM(DEFGUID(D9,41,CD,01,0B,BD,47,30,BA,66,F7,62,13,9F,26,68), DEFGUID(F8,48,CE,61,A6,73,4e,1d,89,E6,ED,33,C3,5E,F8,CF), "bdxui.dll",        "IComboEdit")
        DEFITEM(DEFGUID(04,D4,2F,6C,98,09,48,6d,B8,51,36,97,8B,C1,B1,07), DEFGUID(A6,09,66,D0,78,3B,4d,7a,93,3B,71,55,03,8F,13,AA), "bdxui.dll",        "IComboEditList")
        DEFITEM(DEFGUID(E9,63,EC,2E,04,FE,49,71,83,59,46,43,87,91,A2,13), DEFGUID(15,F7,78,3C,7E,43,49,ba,87,25,AE,AF,3F,B1,48,7E), "bdxui.dll",        "IComboEditItem")
        DEFITEM(DEFGUID(FC,95,96,B4,80,BA,4f,df,9F,05,91,6A,60,14,B5,0E), DEFGUID(68,01,96,9B,12,9F,4a,a5,88,31,49,61,82,E9,EB,2E), "bdxui.dll",        "IxProgress")
        DEFITEM(DEFGUID(12,6A,18,D5,5F,CF,4b,17,8D,71,2C,87,99,EE,AE,3B), DEFGUID(1F,C3,8E,3E,18,FD,45,f9,BB,56,14,FF,F4,8F,A6,4D), "bdxui.dll",        "IxDropBtn")
        DEFITEM(DEFGUID(C6,78,D0,68,87,C0,47,7d,8E,89,CD,ED,B1,A1,8A,22), DEFGUID(BA,57,C1,25,E9,5F,40,a1,A7,5A,95,DE,38,3C,57,D0), "bdxui.dll",        "IMsgBox")
        DEFITEM(DEFGUID(A3,A2,61,9B,26,9C,4f,e0,9C,C5,FC,D1,48,DC,93,E1), DEFGUID(4F,82,6E,D6,B6,44,49,ab,94,23,44,28,45,D8,73,95), "bdxui.dll",        "IxAnimCtrl")
        DEFITEM(DEFGUID(47,68,52,9E,BF,F0,43,25,AF,9B,93,69,B9,28,C1,D2), DEFGUID(12,BC,46,4B,00,19,47,75,A0,42,BE,3F,1C,9B,FC,F8), "bdxui.dll",        "IAnimationCtrl")
        DEFITEM(DEFGUID(68,38,03,AB,D8,C9,42,64,8D,30,57,A5,4B,20,06,EA), DEFGUID(DD,5D,38,DE,1E,68,49,b5,BA,86,7E,37,3D,D4,63,0D), "bdxui.dll",        "ITreeCtrl")
        DEFITEM(DEFGUID(85,96,44,B5,69,53,40,f8,A6,0C,50,D7,03,1B,03,EA), DEFGUID(44,16,FD,21,E1,58,4a,3f,80,C0,7B,5E,F9,1C,3D,15), "bdxui.dll",        "IxDockMgr")
        DEFITEM(DEFGUID(39,15,B0,C5,ED,B1,47,99,B3,83,53,A3,C6,D7,88,27), DEFGUID(76,EE,0E,49,EB,0C,44,9d,AF,1C,C4,7E,8B,CD,28,38), "bdxui.dll",        "IWindowInplace")
        DEFITEM(DEFGUID(8A,D6,74,46,AB,A3,43,96,AE,1C,E4,A3,1D,32,37,46), DEFGUID(B0,A2,27,D9,87,4F,49,f3,A5,29,BA,16,DE,05,87,60), "bdxui.dll",        "IxScrollBar")
        DEFITEM(DEFGUID(13,72,87,96,5D,6A,4b,40,9F,66,F3,A7,96,D2,1B,11), DEFGUID(3E,BD,25,7C,27,D8,4d,e8,95,25,CC,54,5A,0F,E1,51), "bdxui.dll",        "IxScrollMgr")
        DEFITEM(DEFGUID(14,2C,91,00,D8,C3,47,0b,8E,D3,1D,9B,CA,BA,13,06), DEFGUID(B2,1F,83,C7,B4,42,46,79,86,51,94,32,B3,2D,87,E4), "bdxui.dll",        "IxListRow")
        DEFITEM(DEFGUID(B0,0B,A8,37,E8,02,47,e6,93,3A,B0,EA,B4,27,F4,19), DEFGUID(5E,9C,52,78,35,C6,46,d9,B3,CB,A4,0F,73,C1,B2,71), "bdxui.dll",        "IxList")
        DEFITEM(DEFGUID(C9,C2,9E,8D,5A,27,48,8d,B6,6E,58,DB,B4,CB,2D,87), DEFGUID(65,C3,9C,FE,8B,D3,4e,2e,85,65,2F,6E,B5,69,58,3C), "bdxui.dll",        "IxDropList")
        DEFITEM(DEFGUID(10,2F,EC,AF,DA,9A,4a,6c,98,26,02,47,F0,0F,67,17), DEFGUID(D5,1E,AB,41,FD,B1,41,24,B6,6A,EE,66,61,58,9C,18), "bdxui.dll",        "IStandardWin")
        DEFITEM(DEFGUID(34,75,24,A4,2C,AC,4e,11,98,CF,B8,F1,64,65,58,9B), DEFGUID(98,5B,83,F1,7B,04,42,05,96,B3,80,FC,41,86,7B,92), "bdxui.dll",        "IxClipboard")
        DEFITEM(DEFGUID(3E,38,CC,F9,8E,85,4f,c8,88,CE,54,71,E1,B3,14,09), DEFGUID(83,88,F8,8E,AC,D2,40,55,88,A8,6E,F7,F7,C1,54,FF), "bdxui.dll",        "IxEventDispatch")
        DEFITEM(DEFGUID(48,0A,E8,0C,3C,11,4f,00,A1,FF,BD,6E,A2,50,CE,2F), DEFGUID(3D,10,3D,38,88,DC,41,dc,B9,69,45,A2,DF,CB,4A,04), "bdxui.dll",        "IxStatic")
        //DEFITEM(DEFGUID(F6,64,74,2A,44,9A,49,e1,A7,59,04,54,9B,03,FD,7B), DEFGUID(3D,96,C6,BE,FE,5C,43,01,A0,76,D4,AA,88,49,45,CD), "bdxui.dll",        "IxRichEdit")
        DEFITEM(DEFGUID(04,1F,F2,ED,1B,CD,46,D8,91,D4,E6,C3,4E,BC,0E,FF), DEFGUID(E6,F4,1D,2C,34,95,4E,20,93,DD,F3,D2,E0,0B,D1,75), "bdxui.dll",        "IxWLRichEdit")
        DEFITEM(DEFGUID(68,BF,A1,F1,E7,5A,48,3d,BE,F2,AB,06,9E,31,E4,4E), DEFGUID(70,13,CF,48,D7,9E,4e,dd,8D,E5,0A,D3,07,B1,FE,D1), "bdxui.dll",        "IxComboBox")
        DEFITEM(DEFGUID(25,36,BF,3E,D7,2E,43,c5,8C,4D,65,82,12,DB,D5,2B), DEFGUID(30,EC,92,52,04,DC,4b,af,BD,43,23,95,F4,3C,34,9E), "bdxui.dll",        "IxRenderLayer")
        DEFITEM(DEFGUID(E5,8C,7A,52,B7,19,43,61,87,CF,9F,8B,F6,87,AE,CC), DEFGUID(C5,EE,24,D4,17,F4,47,62,BB,77,29,11,F8,5E,35,8B), "bdxui.dll",        "IxAnimateMgr")
        DEFITEM(DEFGUID(AE,4D,4A,2F,5F,82,46,61,AD,46,6D,CA,C9,0A,25,AD), DEFGUID(67,1E,C5,9C,78,03,4c,be,89,61,00,01,BC,ED,06,CF), "bdxui.dll",        "IxTween")
        DEFITEM(DEFGUID(8C,5D,17,C2,F0,04,42,81,9E,49,E5,92,17,09,0D,75), DEFGUID(01,96,3F,8B,55,BF,41,c9,A0,12,62,A7,E8,1F,44,39), "bdxui.dll",        "IxAnimate")
        DEFITEM(DEFGUID(DE,CD,7F,04,C2,1D,4a,6c,9A,6A,C1,3A,14,6F,9E,5B), DEFGUID(46,9A,EE,DA,3D,A2,4b,79,B1,19,E1,BA,33,7C,46,98), "bdxui.dll",        "IxCanvasHideDelegate")
        DEFITEM(DEFGUID(F4,69,8C,5D,E1,47,4d,6c,A3,57,F9,4F,2C,E6,36,A8), DEFGUID(47,12,68,76,4E,52,4a,93,8B,55,AB,01,C5,02,68,DC), "bdxui.dll",        "IxCanvasShowDelegate")
        DEFITEM(DEFGUID(2F,5E,93,7C,10,D8,42,39,91,A1,D4,0F,70,B1,EC,D4), DEFGUID(F2,12,D3,3F,77,6E,46,07,B6,83,E3,49,38,06,A9,EF), "bdxui.dll",        "IxCanvasMoveDelegate")
        DEFITEM(DEFGUID(78,56,06,BB,B3,43,40,c6,A8,CC,26,67,96,88,44,B6), DEFGUID(74,7F,68,71,33,D6,4f,42,B2,05,DA,36,BC,EF,03,4E), "bdxui.dll",        "IxCanvasAnimateMgr")
        DEFITEM(DEFGUID(F0,7A,7A,5D,41,5F,42,88,A6,76,CC,99,E0,32,86,C8), DEFGUID(4B,35,C2,3C,9B,6E,4b,60,98,E9,E5,FC,F5,A1,3A,43), "bdxui.dll",        "IxMsgDispatcher")
        DEFITEM(DEFGUID(54,FD,08,BD,2C,4E,4b,42,93,34,47,8F,15,5A,87,CF), DEFGUID(DC,C8,AC,BB,01,F9,49,76,B3,AD,22,07,B6,DC,41,0B), "bdxui.dll",        "IxMenu")
        DEFITEM(DEFGUID(E8,0E,A3,6C,19,4E,4b,92,8A,D9,67,8E,F4,6D,59,9E), DEFGUID(2B,E4,AE,CF,56,16,46,be,AD,54,7E,71,0E,F1,F1,11), "bdxui.dll",        "IxMenuItem")
        DEFITEM(DEFGUID(26,DC,39,98,87,03,4D,24,8F,2F,6E,00,14,E1,63,88), DEFGUID(A8,7A,B1,05,A8,19,48,AC,9B,4B,97,02,BC,51,B8,F3), "bdxui.dll",        "IxListAnim")
        DEFITEM(DEFGUID(F2,38,D0,3A,D3,B9,4E,B9,88,EC,83,F4,D0,B3,10,47), DEFGUID(43,2B,2D,23,05,6F,41,DC,96,B8,78,CA,C8,3D,DD,27), "bdxui.dll",        "IxTimer")

        DEFITEM(DEFGUID(A7,37,E7,10,21,E8,4d,43,A5,7D,15,95,08,E8,BB,FF), DEFGUID(92,46,86,DD,4F,58,48,a2,B1,BE,8B,4C,F6,B1,56,4A), "bdxui.dll",        "IxCanvasMgr")
        DEFITEM(DEFGUID(B1,0A,35,F8,32,E7,4f,f1,B3,05,7D,43,06,B4,19,45), DEFGUID(5B,AE,A5,1F,93,68,47,5e,8F,48,65,E9,4F,BC,62,11), "bdxui.dll",        "IxBuilder")
        DEFITEM(DEFGUID(1A,AD,15,05,38,AF,49,96,85,6A,63,BA,03,B3,A2,37), DEFGUID(8E,17,0C,D9,F2,65,48,00,B5,B0,BE,03,E3,4E,5D,DB), "bdxui.dll",        "IxSkinMgr")
        DEFITEM(DEFGUID(E4,43,70,56,59,4C,4e,05,AE,09,CE,93,42,62,86,59), DEFGUID(7D,CF,24,B2,39,65,47,10,9E,4C,A1,7F,F2,8B,6F,BD), "bdxui.dll",        "IxStyleMgr")
        DEFITEM(DEFGUID(99,9F,79,AF,C0,B0,47,55,9F,EE,14,40,72,C2,FE,56), DEFGUID(D3,97,38,D7,71,84,4a,00,BC,37,F5,C3,6A,F9,7F,77), "bdxui.dll",        "IxHelp")
        DEFITEM(DEFGUID(EB,0F,CB,C7,B1,70,43,da,AF,5C,A6,B4,EF,DF,DA,2A), DEFGUID(CA,08,ED,F5,66,A4,4c,ca,A4,C6,39,98,1A,11,BF,CC), "bdxui.dll",        "IxAnimMgr")
        DEFITEM(DEFGUID(AB,00,AA,76,C2,D2,4B,87,8D,D1,8B,4F,C3,70,63,C9), DEFGUID(4A,05,D4,96,F5,2E,48,CB,9C,71,8E,FE,13,33,06,51), "bdxui.dll",        "IxDragDropMgr")
        DEFITEM(DEFGUID(F5,05,B1,48,63,8A,4E,6A,B0,20,E3,E1,CD,4A,09,D3), DEFGUID(0A,91,5E,D8,B0,26,4D,AD,86,CC,C9,25,C7,10,36,94), "bdxui.dll",        "IxLayerWin")
        DEFITEM(DEFGUID(39,FB,A2,80,7A,C8,45,A6,A9,D2,56,D8,27,10,14,81), DEFGUID(5F,83,B4,63,48,C9,40,BF,91,63,C9,0C,1C,FB,D9,EB), "bdxui.dll",        "IxFavoBar")
        DEFITEM(DEFGUID(83,95,7E,A0,00,DF,45,02,94,AA,EB,60,99,B3,B3,EB), DEFGUID(FA,E9,BD,86,2B,E3,45,F1,99,7D,FD,46,25,FE,02,19), "bdxui.dll",        "IxFavoItemData")
        DEFITEM(DEFGUID(B3,07,4D,8D,1F,D9,48,F4,B0,47,2B,B8,1F,A5,57,6F), DEFGUID(5C,1B,75,A0,ED,FF,4A,60,8B,20,C2,AA,8A,D3,40,F9), "bdxui.dll",        "IxAnimBtn")
        DEFITEM(DEFGUID(DD,76,6C,30,3D,CE,41,77,AD,7D,67,E9,B0,A7,9F,45), DEFGUID(90,A4,08,1A,27,CB,43,FE,8D,07,3F,43,36,E1,32,33), "bdxui.dll",        "IxPropertyMgr")

        DEFITEM(DEFGUID(C2,75,1F,55,3E,17,45,d7,88,33,37,51,39,03,46,00), DEFGUID(AE,0B,5C,39,C6,C8,40,10,A9,AE,93,5D,11,9B,85,15), "bdxctrl.dll",      "IxCheckBox")
        DEFITEM(DEFGUID(6B,52,50,8C,E2,1E,45,41,98,47,C0,7F,FD,2A,50,47), DEFGUID(58,F2,44,BE,ED,9A,43,44,9E,42,14,7F,89,A5,20,D2), "bdxctrl.dll",      "IGroup")
        DEFITEM(DEFGUID(39,64,AB,9B,D4,D2,4d,4f,83,B9,C9,7D,EE,2C,FB,71), DEFGUID(34,72,19,5F,91,83,48,71,B2,FF,93,F5,F7,CF,6C,49), "bdxctrl.dll",      "IRadioButton")
        DEFITEM(DEFGUID(90,DB,11,9F,F4,C9,44,fc,97,64,7D,F2,FC,1E,17,5D), DEFGUID(04,5B,EF,C0,EF,18,4b,02,99,18,3F,20,2C,8D,5A,D7), "bdxctrl.dll",      "IxThumb")
        DEFITEM(DEFGUID(D7,82,AC,B4,E7,FE,45,e8,87,5F,31,3B,86,38,83,DE), DEFGUID(D4,1A,12,8F,4F,F3,40,d6,84,11,63,74,14,8F,21,0E), "bdxctrl.dll",      "IxSlider")
        DEFITEM(DEFGUID(2C,91,A5,AD,BB,B7,43,d3,B1,62,22,3F,69,FC,BD,23), DEFGUID(78,03,25,20,49,3A,43,30,A4,E6,2C,DE,7D,05,A8,F5), "bdxctrl.dll",      "IBubbleContainer")
        DEFITEM(DEFGUID(BC,53,94,F8,B9,AA,42,2e,8F,51,EC,44,A1,10,D7,F8), DEFGUID(84,D1,D1,3A,72,9E,4e,5e,A5,06,FD,53,12,94,23,9F), "bdxctrl.dll",      "IBubbleDesc")
        DEFITEM(DEFGUID(ED,4D,EE,C2,FF,C5,47,ec,98,F2,30,6D,CC,16,76,E6), DEFGUID(E4,E9,2E,C9,22,BA,41,52,99,71,D0,A0,00,0D,CA,2C), "bdxctrl.dll",      "IStandardBubble")
        DEFITEM(DEFGUID(F6,83,B8,16,ED,91,46,cc,BA,4B,0C,30,D1,CC,28,9E), DEFGUID(3B,61,D8,00,84,3F,40,00,A9,D6,D2,E4,64,4E,D0,57), "bdxctrl.dll",      "IBubbleMgr")
        DEFITEM(DEFGUID(5D,82,AA,B4,E4,F7,4A,4F,AE,73,10,15,E5,E9,D8,C8), DEFGUID(9C,D2,C9,63,3F,8B,42,35,93,08,3A,C1,FA,22,B7,A1), "bdxctrl.dll",      "IxWeb")

    };


    ////////////////////////////////////////service table definition//////////////////////////////////
    ObjectInfo serTable[] =
    {
        DEFITEM(DEFGUID(C5,9A,FC,5A,2C,B7,45,0e,AB,48,A7,4F,C0,1C,EE,9E), DEFGUID(B5,A9,B7,8F,45,CF,4e,d8,A1,97,4D,F1,A8,61,D4,DE), "bdcommon.dll", "IMessageLoopMgr")
        DEFITEM(DEFGUID(51,08,2B,EE,18,50,47,7c,88,EA,76,16,8C,3B,87,62), DEFGUID(D0,A1,B4,76,45,B8,41,75,82,45,3C,1E,8C,2F,50,A4), "bdcommon.dll", "ITimerService")
        DEFITEM(DEFGUID(B1,96,FF,64,68,8C,48,ff,AF,5B,22,C9,66,4A,87,1B), DEFGUID(5A,F8,B6,B7,03,6A,4d,ea,B7,15,A1,D3,3E,90,1A,B7), "bdcommon.dll", "IStringHelper")
        DEFITEM(DEFGUID(86,09,67,E8,37,4B,46,3a,BA,AC,62,23,C3,5E,88,37), DEFGUID(17,F7,38,47,B9,40,41,b7,BE,0F,03,C9,0E,64,83,67), "bdcommon.dll", "ICommandLine")
        DEFITEM(DEFGUID(40,79,11,03,17,05,46,67,b2,db,7b,c8,eb,ad,aa,a8), DEFGUID(92,99,a4,07,7b,c0,44,5b,8a,35,9f,44,a6,5e,90,9e), "bdcommon.dll", "IServiceThreadMgr")
        DEFITEM(DEFGUID(EB,10,BD,05,CE,A4,41,35,AF,BE,CD,DC,A2,32,4D,68), DEFGUID(28,2B,40,9A,A8,0B,4A,2C,83,BD,9A,A7,BB,25,2C,44), "bdxui.dll",    "IXuiLib")
    };

    int countObj = sizeof(objTable) / sizeof(ObjectInfo);

    for(int i = 0; i < countObj; i++)
    {
        Util::Com::RegObject(*objTable[i].guid, *(objTable[i].guid + 1), CComBSTR(objTable[i].strPath), CComBSTR(objTable[i].progid));
    }

    countObj = sizeof(serTable) / sizeof(ObjectInfo);

    for(int i = 0; i < countObj; i++)
    {
        Util::Com::RegService(*serTable[i].guid, *(serTable[i].guid + 1), CComBSTR(serTable[i].strPath), CComBSTR(serTable[i].progid));
    }
}