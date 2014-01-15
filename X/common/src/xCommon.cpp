#include "stdafx.h"
#include "ObjectCreater.h"
#include "xCommon/xCommon.h"

HRESULT WINAPI xCommon::CreateObjectByIID(REFIID iid, void** ppOut)
{
    return g_oObjectCreater.CreateObjectByIID(iid, ppOut);
}

HRESULT WINAPI xCommon::CreateObjectByInterface(BSTR bsInterface, void** ppOut)
{
    return g_oObjectCreater.CreateObjectByInterface(bsInterface, ppOut);
}

HRESULT WINAPI xCommon::CreateAggObjectByIID(REFIID iid, void** ppOut, IUnknown* pOuterUnk)
{
    return g_oObjectCreater.CreateObjectByIID(iid, ppOut, pOuterUnk);
}

HRESULT WINAPI xCommon::GetService(REFIID iid, void** ppOut)
{
    return g_oObjectCreater.GetService(iid, ppOut);
}

HRESULT WINAPI xCommon::RegObject(REFIID iid, REFCLSID clsid, BSTR bsFile, BSTR bsInterface)
{
    return g_oObjectCreater.RegObject(iid, clsid, bsFile, bsInterface, FALSE);
}

HRESULT WINAPI xCommon::RegService(REFIID iid, REFCLSID clsid, BSTR bsFile, BSTR bsInterface)
{
    return g_oObjectCreater.RegObject(iid, clsid, bsFile, bsInterface, TRUE);
}