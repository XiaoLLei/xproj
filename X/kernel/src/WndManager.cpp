#include "stdafx.h"
#include "WndManager.h"

CxWndManager::CxWndManager()
{}

CxWndManager::~CxWndManager()
{}

HRESULT CxWndManager::AddWnd(IxWnd* pWnd)
{
    if (!pWnd)
    {
        return E_INVALIDARG;
    }

    if (m_setWnds.count(pWnd) > 0)
    {
        return E_FAIL;
    }

    m_setWnds.insert(pWnd);

    return S_OK;
}

HRESULT CxWndManager::RemoveWnd(IxWnd* pWnd)
{
    if (!pWnd)
    {
        return E_INVALIDARG;
    }

    if (0 == m_setWnds.count(pWnd))
    {
        return E_FAIL;
    }

    m_setWnds.erase(pWnd);

    if (0 == m_setWnds.size())
    {
         CComPtr<IxMessageLoop> spLoop;
         ::xCommon::GetService(__uuidof(IxMessageLoop), (void**)&spLoop);
         ATLASSERT(spLoop);
         if (spLoop)
         {
             spLoop->QuitAll();
         }
    }

    return S_OK;
}