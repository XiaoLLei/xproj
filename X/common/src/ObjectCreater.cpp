#include "stdafx.h"
#include "xCommon/IxService.h"
#include "Lock.h"
#include "Util.h"
#include "ObjectCreater.h"

CxObjectCreater g_oObjectCreater;

CxObjectCreater::CxObjectCreater()
{
    m_strModulePath = xCommon::xUtil::GetModuleDir(NULL);
}

CxObjectCreater::~CxObjectCreater()
{}

HRESULT CxObjectCreater::Init()
{
    return S_OK;
}

HRESULT CxObjectCreater::Uninit()
{
    {
        xCommon::CxAutoLock autolock(m_oLockService);
        SERVICEMAP::iterator iter = m_mapService.begin();
        while (iter != m_mapService.end())
        {
            CComPtr<IUnknown> spUnknown = iter->second;
            CComQIPtr<IxService> spService = spUnknown;
            if (spService)
                spService->UninitService();
            ++iter;
        }
    }
    return S_OK;
}

HRESULT CxObjectCreater::SetATLModule(_ATL_COM_MODULE* pModule)
{
    return S_OK;
}

HRESULT CxObjectCreater::CreateObjectByIID(REFIID iid, void** ppOut, IUnknown *pOuterUnk)
{
    HRESULT hRet = E_FAIL;

    OBJCREATEINFO info = {0};

    {
        xCommon::CxAutoLock autolock(m_oLockCreateInfo);
        GUIDMAP::iterator iter = m_mapGuid.find(iid);
        if (iter != m_mapGuid.end() && iter->second < m_vecCreateInfo.size())
        {
            info = m_vecCreateInfo[iter->second];
            hRet = S_OK;
        }
    }

    if (SUCCEEDED(hRet))
    {
        hRet = _create_obj_from_file(info.iid, info.clsid, info.strFile, ppOut, pOuterUnk);
    }

    return hRet;
}

HRESULT CxObjectCreater::CreateObjectByInterface(BSTR bsInterface, void** ppOut)
{
    HRESULT hRet = E_FAIL;

    OBJCREATEINFO info = {0};

    {
        xCommon::CxAutoLock autolock(m_oLockCreateInfo);
        INTERFACEMAP::iterator iter = m_mapInterface.find(CString(bsInterface));
        if (iter != m_mapInterface.end())
        {
            info = m_vecCreateInfo[iter->second];
            hRet = S_OK;
        }
    }

    if (SUCCEEDED(hRet))
    {
        hRet = _create_obj_from_file(info.iid, info.clsid, info.strFile, ppOut, NULL);
    }

    return S_OK;
}

HRESULT CxObjectCreater::RegObject(REFIID iid, REFCLSID clsid, BSTR bsInterface, BSTR bsFilename, BOOL bService)
{
    return _add_obj_create_info(iid, clsid, CString(bsInterface), CString(bsFilename), bService);
}

HRESULT CxObjectCreater::GetService(REFIID iid, void** ppOut)
{
    {
        xCommon::CxAutoLock autolock(m_oLockService);
        SERVICEMAP::iterator iter = m_mapService.find(iid);
        if (iter != m_mapService.end())
        {
            CComPtr<IUnknown> spOut = iter->second;
            if (spOut)
            {
                return spOut->QueryInterface(iid, ppOut);
            }
            else
            {
                return E_FAIL;
            }
        }
    }

    CString strFilename;
    CLSID clsid = GUID_NULL;

    {
        xCommon::CxAutoLock autolock(m_oLockCreateInfo);
        CREATEINFOMAP::iterator iter = m_mapServiceCreateInfo.find(iid);
        if (iter != m_mapServiceCreateInfo.end())
        {
            strFilename = iter->second.strFile;
            clsid = iter->second.clsid;
        }
        else
        {
            return E_FAIL;
        }
    }

    CComPtr<IUnknown> spUnknown;
    HRESULT hRet = _create_obj_from_file(iid, clsid, strFilename, (void**)&spUnknown, NULL);
    if (!spUnknown)
    {
        return hRet;
    }

    {
        xCommon::CxAutoLock autolock(m_oLockService);
        m_mapService.insert(SERVICEMAP::value_type(iid, spUnknown));
    }

    CComQIPtr<IxService> spService = spUnknown;
    if (spService)
    {
        spService->InitService();
    }

    spUnknown->QueryInterface(iid, ppOut);

    return S_OK;
}

HRESULT CxObjectCreater::ResetPath(BSTR bsFile)
{
    return S_OK;
}

HRESULT CxObjectCreater::_create_obj_from_file(REFIID iid, REFCLSID clsid, CString &strFilename, void** ppOut, IUnknown *pOuterUnk)
{
    INT nPos = strFilename.ReverseFind(L'.');
    if (-1 != nPos)
    {
        CString strExtension = strFilename.Mid(nPos + 1);
        if (0 == strExtension.CompareNoCase(L"DLL"))
        {
            return _create_obj_from_dll(iid, clsid, strFilename, ppOut, pOuterUnk);
        }
        else
        {
            return _create_obj_from_exe(iid, clsid, strFilename, ppOut, pOuterUnk);
        }
    }
    return E_FAIL;
}

HRESULT CxObjectCreater::_create_obj_from_dll(REFIID iid, REFCLSID clsid, CString& strFilename, void** ppOut, IUnknown *pOuterUnk)
{
    if (!ppOut)
    {
        return E_POINTER;
    }
    *ppOut = NULL;

    CComPtr<IClassFactory> spFactory;

    {
        xCommon::CxAutoLock autolock(m_oLockObjFactoryMap);
        OBJFACTORYMAP::iterator iter = m_mapObjFactory.find(clsid);
        if (iter != m_mapObjFactory.end())
        {
            spFactory = iter->second;
        }
    }

    if (!spFactory)
    {
        HRESULT hRet = _create_obj_factory_from_dll(strFilename, clsid, &spFactory);
        if (SUCCEEDED(hRet) && spFactory)
        {
            xCommon::CxAutoLock autolock(m_oLockObjFactoryMap);
            m_mapObjFactory[clsid] = spFactory;
        }
        else
        {
            return hRet;
        }
    }

    if (spFactory)
    {
        HRESULT hRet = spFactory->CreateInstance(pOuterUnk, (NULL == pOuterUnk) ? iid : IID_IUnknown, ppOut);
        return hRet;
    }

    return CO_E_DLLNOTFOUND;
}

HRESULT CxObjectCreater::_create_obj_from_exe(REFIID iid, REFCLSID clsid, CString& strFilename, void** ppOut, IUnknown *pOuterUnk)
{
    return S_OK;
}

HRESULT CxObjectCreater::_create_obj_factory_from_dll(CString& strFilename, REFCLSID clsid, IClassFactory** ppFactory)
{
    if (!ppFactory)
    {
        return E_POINTER;
    }
    *ppFactory = NULL;

    BOOL bLoaded = FALSE;

    {
        xCommon::CxAutoLock autolock(m_oLockDllLoadSet);
        bLoaded = !!(m_setLoadedDll.count(strFilename));
    }

    CString strPath;
    strPath.Format(_T("%s\\%s"), m_strModulePath, strFilename);

    HINSTANCE hInstance = ::GetModuleHandle(strPath);
    if (!hInstance || !bLoaded)
    {
        hInstance = ::LoadLibrary(strPath);
        if (!hInstance)
        {
            return E_FAIL;
        }
        else
        {
            xCommon::CxAutoLock autolock(m_oLockDllLoadSet);
            if (m_setLoadedDll.count(strFilename) <= 0)
                m_setLoadedDll.insert(strFilename);
        }
    }

    if (!hInstance)
        return CO_E_DLLNOTFOUND;

    typedef HRESULT (__stdcall *GETCLASS_PROC)(REFCLSID, REFIID, LPVOID*);

    GETCLASS_PROC proc = NULL;
    xCommon::xUtil::GetProcAddress(hInstance, "DllGetClassObject", &proc);

    if (proc)
    {
        HRESULT hr = proc(clsid, IID_IClassFactory, (void**)ppFactory);
        if (SUCCEEDED(hr) && *ppFactory)
            return S_OK;
        else
            return hr;
    }

    return E_FAIL;
}

HRESULT CxObjectCreater::_add_obj_create_info(IID iid, REFCLSID clsid, CString strFilename, CString& strInterface, BOOL bService)
{
    OBJCREATEINFO info = {0};
    info.iid = iid;
    info.clsid = clsid;
    info.strFile = strFilename;
    info.strInterface = strInterface;

    HRESULT hRet = E_FAIL;

    xCommon::CxAutoLock autolock(m_oLockCreateInfo);

    if (bService)
    {
        CREATEINFOMAP::iterator iter = m_mapServiceCreateInfo.find(iid);
        if (iter == m_mapServiceCreateInfo.end())
        {
            m_mapServiceCreateInfo.insert(CREATEINFOMAP::value_type(info.iid, info));
            hRet = S_OK;
        }
        else
        {
            ATLASSERT(!_T("添加重复service"));
        }
    }
    else
    {
        GUIDMAP::iterator iter = m_mapGuid.find(iid);
        if (iter == m_mapGuid.end())
        {
            m_mapGuid.insert(GUIDMAP::value_type(info.iid, m_vecCreateInfo.size()));
            m_mapInterface.insert(INTERFACEMAP::value_type(info.strInterface, m_vecCreateInfo.size()));
            m_vecCreateInfo.push_back(info);
            hRet = S_OK;
        }
        else
        {
            ATLASSERT(!_T("添加重复object"));
        }
    }

    return hRet;
}

//////////////////////////////////////////////////////////////////////////
bool operator < (const GUID& first, const GUID& second)
{
    if (first.Data1 < second.Data1)
    {
        return true;
    }
    else if (first.Data1 > second.Data1)
    {
        return false;
    }

    if (first.Data2 < second.Data2)
    {
        return true;
    }
    else if (first.Data2 > second.Data2)
    {
        return false;
    }

    if (first.Data3 < second.Data3)
    {
        return true;
    }
    else if (first.Data3 > second.Data3)
    {
        return false;
    }

    int nRet = memcmp((const char*)first.Data4, (const char*)second.Data4, 8);

    return (nRet < 0);
}