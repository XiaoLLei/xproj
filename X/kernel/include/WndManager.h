#pragma once
#include "xKernel/IxWndManager.h"

[
    default(IxWndManager),
    threading(free),
    uuid("4BB0C8DF-B56B-4ef7-9D60-0CD576C0E29C"),
    coclass
]
class ATL_NO_VTABLE CxWndManager : public IxWndManager
{
    typedef std::set< CComPtr<IxWnd> > WNDSET;
public:
    CxWndManager();
    virtual ~CxWndManager();

public:
    // interface of IxWndManager
    HRESULT AddWnd(IxWnd* pWnd);
    HRESULT RemoveWnd(IxWnd* pWnd);

    // interface of IxService

protected:
    WNDSET      m_setWnds;
};