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
        };

        ////////////////////////////////////////service table definition//////////////////////////////////
        OBJINFO serTable[] =
        {
            DEFITEM(DEFGUID(1F,94,44,65,9F,C5,4b,08,BE,A0,AA,A9,82,39,AB,B9), DEFGUID(28,2D,F7,B2,77,56,4f,0f,A7,88,78,B4,F2,30,DC,1B), "xKernel.dll", "IxWnd")
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