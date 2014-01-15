#include "stdafx.h"
#include "public/xDefine.h"
#include "xCommon/xCommon.h"
#include "Global.h"

namespace xCommon
{
    CxGlobal g_oGlobal;

    CxGlobal::CxGlobal()
    {
        ////////////////////////////////////////service table definition//////////////////////////////////
        /*
        OBJINFO objTable[] =
        {
            DEFITEM(DEFGUID(), DEFGUID(), "xCommon.dll", "IxMessageLoop")
        };
        */

        /*
        int countObj = sizeof(objTable) / sizeof(ObjectInfo);

        for(int i = 0; i < countObj; ++i)
        {
            ::xCommon::RegObject(*objTable[i].guid, *(objTable[i].guid + 1), CComBSTR(objTable[i].strPath), CComBSTR(objTable[i].progid));
        }
        */

        ////////////////////////////////////////service table definition//////////////////////////////////
        OBJINFO serTable[] =
        {
            DEFITEM(DEFGUID(A5,B1,77,2B,6D,14,44,20,99,BE,AF,2E,40,30,EE,E5), DEFGUID(C9,8C,17,87,DC,1A,43,fe,89,7E,BA,0C,7E,17,2A,85), "xCommon.dll", "IxMessageLoop")
        };

        int countSer = sizeof(serTable) / sizeof(ObjectInfo);

        for(int i = 0; i < countSer; ++i)
        {
            ::xCommon::RegService(*serTable[i].guid, *(serTable[i].guid + 1), CComBSTR(serTable[i].strPath), CComBSTR(serTable[i].progid));
        }
    }

    CxGlobal::~CxGlobal()
    {

    }
}