#pragma once

#include "public/xDefine.h"

namespace xKernel
{
    static void xKernel_RegisterObjectsAndServices()
    {
        ////////////////////////////////////////service table definition//////////////////////////////////
        OBJINFO objTable[] =
        {
            DEFITEM(DEFGUID(1F,94,44,65,9F,C5,4b,08,BE,A0,AA,A9,82,39,AB,B9), DEFGUID(28,2D,F7,B2,77,56,4f,0f,A7,88,78,B4,F2,30,DC,1B), "xKernel.dll", "IxWnd")
            DEFITEM(DEFGUID(28,3C,DD,B0,A5,A5,41,e0,AD,F6,78,25,EA,00,24,E8), DEFGUID(93,69,E3,78,16,79,44,c4,A4,C1,E1,F3,29,35,F9,B9), "xKernel.dll", "IxCanvas")
            DEFITEM(DEFGUID(79,83,1E,87,23,77,42,14,B3,DE,4E,58,43,92,6D,EF), DEFGUID(3B,CA,6D,24,04,6C,44,fc,A6,22,01,79,7D,26,3E,25), "xKernel.dll", "IxBrushView")
        };

        ////////////////////////////////////////service table definition//////////////////////////////////
        OBJINFO serTable[] =
        {
            DEFITEM(DEFGUID(49,AE,78,E5,30,29,4c,51,AD,77,8F,0E,1B,4A,F5,EA), DEFGUID(4B,B0,C8,DF,B5,6B,4e,f7,9D,60,0C,D5,76,C0,E2,9C), "xKernel.dll", "IxWndManager")
        };

        int countObj = sizeof(objTable) / sizeof(ObjectInfo);

        for(int i = 0; i < countObj; i++)
        {
            ::xCommon::RegObject(*objTable[i].guid, *(objTable[i].guid + 1), CComBSTR(objTable[i].strPath), CComBSTR(objTable[i].progid));
        }

        countObj = sizeof(serTable) / sizeof(ObjectInfo);

        for(int i = 0; i < countObj; i++)
        {
            ::xCommon::RegService(*serTable[i].guid, *(serTable[i].guid + 1), CComBSTR(serTable[i].strPath), CComBSTR(serTable[i].progid));
        }
    }
}