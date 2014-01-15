#pragma once

//////////////////////////////////////////////////////////////////////////
// interface
#include "IxService.h"
#include "IxMessageLoop.h"
//////////////////////////////////////////////////////////////////////////

#ifndef XCOMMON_EXPORT
#define XCOMMON_API __declspec(dllimport)
#else
#define XCOMMON_API __declspec(dllexport)
#endif

namespace xCommon
{
    XCOMMON_API HRESULT WINAPI CreateObjectByIID(REFIID iid, void** ppOut);
    XCOMMON_API HRESULT WINAPI CreateObjectByInterface(BSTR bsInterface, void** ppOut);
    XCOMMON_API HRESULT WINAPI CreateAggObjectByIID(REFIID iid, void** ppOut, IUnknown* pOuterUnk);

    XCOMMON_API HRESULT WINAPI GetService(REFIID iid, void** ppOut);

    XCOMMON_API HRESULT WINAPI RegObject(REFIID iid, REFCLSID clsid, BSTR bsFile, BSTR bsInterface);
    XCOMMON_API HRESULT WINAPI RegService(REFIID iid, REFCLSID clsid, BSTR bsFile, BSTR bsInterface);
}