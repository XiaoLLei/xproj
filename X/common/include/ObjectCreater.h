#pragma once
#include <vector>
#include <map>
#include <set>
#include "Lock.h"

class CxObjectCreater;
extern CxObjectCreater g_oObjectCreater;

class CxObjectCreater
{
public:
    CxObjectCreater();
    virtual ~CxObjectCreater();

    HRESULT Init();
    HRESULT Uninit();
    HRESULT SetATLModule(_ATL_COM_MODULE* pModule);
    HRESULT CreateObjectByIID(REFIID iid, void** ppOut, IUnknown *pOuterUnk = NULL);
    HRESULT CreateObjectByInterface(BSTR bsInterface, void** ppOut);
    HRESULT RegObject(REFIID iid, REFCLSID clsid, BSTR bsFile, BSTR bsInterface, BOOL bService);
    HRESULT GetService(REFIID iid, void** ppOut);
    HRESULT ResetPath(BSTR bsFile);

protected:
    HRESULT _add_obj_create_info(IID iid, REFCLSID clsid, CString strFilename, CString& strInterface, BOOL bService);
    HRESULT _create_obj_from_file(REFIID iid, REFCLSID clsid, CString& strFilename, void** ppOut, IUnknown *pOuterUnk = NULL);
    HRESULT _create_obj_from_dll(REFIID iid, REFCLSID clsid, CString& strFilename, void** ppOut, IUnknown *pOuterUnk = NULL);
    HRESULT _create_obj_from_exe(REFIID iid, REFCLSID clsid, CString& strFilename, void** ppOut, IUnknown *pOuterUnk = NULL);
    HRESULT _create_obj_factory_from_dll(CString& strFilename, REFCLSID clsid, IClassFactory** ppFactory);

protected:
    typedef struct tagObjectCreateInfo
    {
        GUID	iid;
        CLSID	clsid;
        CString	strFile;
        CString	strInterface;
    }OBJCREATEINFO, *LPOBJCREATEINFO;

    typedef std::map<GUID, size_t> GUIDMAP;
    typedef std::map<CString, size_t> INTERFACEMAP;
    typedef std::vector<OBJCREATEINFO> CREATEINFOVEC;
    typedef std::map<GUID, OBJCREATEINFO> CREATEINFOMAP;

    typedef std::map<GUID, CAdapt<CComPtr<IUnknown>>> SERVICEMAP;

    typedef std::map<GUID, CComPtr<IClassFactory> > OBJFACTORYMAP;

    typedef std::set<CString> STRSET;

    typedef xCommon::CxLock LOCK;

protected:
    CString			m_strModulePath;

    // 普通对象创建表
    GUIDMAP	        m_mapGuid;
    INTERFACEMAP    m_mapInterface;
    CREATEINFOVEC   m_vecCreateInfo;

    // 服务对象创建表
    CREATEINFOMAP   m_mapServiceCreateInfo;

    // 普通对象和服务对象的创建表使用同一个锁
    LOCK            m_oLockCreateInfo;

    // Service缓存
    SERVICEMAP      m_mapService;
    LOCK            m_oLockService;

    // 创建对象的factory缓存
    OBJFACTORYMAP	m_mapObjFactory;
    LOCK            m_oLockObjFactoryMap;

    // 记录加载过的dll
    STRSET          m_setLoadedDll;
    LOCK            m_oLockDllLoadSet;
};