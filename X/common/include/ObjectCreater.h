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

    // ��ͨ���󴴽���
    GUIDMAP	        m_mapGuid;
    INTERFACEMAP    m_mapInterface;
    CREATEINFOVEC   m_vecCreateInfo;

    // ������󴴽���
    CREATEINFOMAP   m_mapServiceCreateInfo;

    // ��ͨ����ͷ������Ĵ�����ʹ��ͬһ����
    LOCK            m_oLockCreateInfo;

    // Service����
    SERVICEMAP      m_mapService;
    LOCK            m_oLockService;

    // ���������factory����
    OBJFACTORYMAP	m_mapObjFactory;
    LOCK            m_oLockObjFactoryMap;

    // ��¼���ع���dll
    STRSET          m_setLoadedDll;
    LOCK            m_oLockDllLoadSet;
};