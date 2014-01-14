#pragma once
#include "xKernel/IxWnd.h"
#include "View.h"

class CxWnd
    : public CxView
    , public IxWnd
    , public CFrameWindowImpl<CxWnd>
{
public:
    CxWnd();
    virtual ~CxWnd();
};

#define WND_INTERFACE()                                                                                 \
    COM_INTERFACE_ENTRY(IxWnd)                                                                          \
    COM_INTERFACE_ENTRY(IxView)                                                                         \
    COM_INTERFACE_ENTRY(IxNode)                                                                         \
    COM_INTERFACE_ENTRY(IxElement)

[
    default(IxWnd),
    threading(free),
    uuid("282DF7B2-7756-4f0f-A788-78B4F230DC1B"),
    coclass
]
class CCoWnd : public CxWnd
{
public:
    DECLARE_PROTECT_FINAL_CONSTRUCT()
    DECLARE_GET_CONTROLLING_UNKNOWN()

    BEGIN_COM_MAP(CCoWnd)
        WND_INTERFACE()
    END_COM_MAP()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {}
};