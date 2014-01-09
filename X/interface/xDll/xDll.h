#pragma once

#include "public/xDefine.h"

namespace xDll
{
    static void XDll_RegisterObjectsAndServices()
    {
        ////////////////////////////////////////service table definition//////////////////////////////////
        OBJINFO objTable[] =
        {
            DEFITEM(DEFGUID(AC,F5,01,B6,D4,C8,47,c2,AF,16,41,53,0E,77,88,71), DEFGUID(E0,EA,E9,1D,C1,80,4b,ff,A1,95,35,A3,9A,F0,9C,6D), "xDll.dll", "IxTest")
        };

        ////////////////////////////////////////service table definition//////////////////////////////////
        OBJINFO serTable[] =
        {
            DEFITEM(DEFGUID(10,AA,EC,EC,A2,F8,44,8c,B1,72,02,29,5E,8D,9F,46), DEFGUID(C3,87,53,6E,89,71,4a,a4,82,18,6F,1E,52,01,9A,9C), "xDll.dll", "IxTestService")
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