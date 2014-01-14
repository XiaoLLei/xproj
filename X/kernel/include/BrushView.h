#pragma once
#include "xKernel/IxBrushView.h"
#include "xKernel/IxPaint.h"
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
    HRESULT Paint();

protected:
    COLORREF    m_clrBkg;
};