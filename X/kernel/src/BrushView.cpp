#include "stdafx.h"
#include "BrushView.h"

CxBrushView::CxBrushView()
    : m_clrBkg(CLR_INVALID)
{}

CxBrushView::~CxBrushView()
{}

HRESULT CxBrushView::GetColor(LPCOLORREF lpClr)
{
    if (!lpClr) return E_POINTER;

    *lpClr = m_clrBkg;

    return S_OK;
}

HRESULT CxBrushView::SetColor(COLORREF clr)
{
    m_clrBkg = clr;
    return S_OK;
}

HRESULT CxBrushView::Paint()
{
    return S_OK;
}