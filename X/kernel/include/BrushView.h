#pragma once
#include "xKernel/IxBrushView.h"
#include "xKernel/IxPaint.h"
#include "def.h"
#include "View.h"

class CxBrushView
    : public CxView
    , public IxBrushView
    , public IxPaint
{
public:
    CxBrushView();
    virtual ~CxBrushView();

public:
    // interface of IxBrushView
    HRESULT GetColor(LPCOLORREF lpClr);
    HRESULT SetColor(COLORREF clr);

    // interface of IxPaint
    HRESULT Paint(IxCanvas* pCanvas);

protected:
    COLORREF    m_clrBkg;
};

[
    default(IxBrushView),
    threading(free),
    uuid("3BCA6D24-046C-44fc-A622-01797D263E25"),
    coclass
]
class CCoBrushView : public CxBrushView
{
public:
    DECLARE_PROTECT_FINAL_CONSTRUCT()
    DECLARE_GET_CONTROLLING_UNKNOWN()

    BEGIN_COM_MAP(CCoBrushView)
        BRUSHVIEW_INTERFACE()
    END_COM_MAP()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {}
};