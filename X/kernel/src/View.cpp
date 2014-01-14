#include "stdafx.h"
#include "View.h"

CxView::CxView()
    : m_rcBox(0, 0, 0, 0)
    , m_byAlpha(0xFF)
    , m_bShow(TRUE)
    , m_bEnable(TRUE)
{}

CxView::~CxView()
{}

HRESULT CxView::GetBoxRect(LPRECT lprcBox)
{
    if (!lprcBox)   return E_POINTER;

    *lprcBox = m_rcBox;

    return S_OK;
}

HRESULT CxView::SetBoxRect(RECT rcBox)
{
    m_rcBox = rcBox;
    return S_OK;
}

HRESULT CxView::GetSize(LPSIZE lpszSize)
{
    if (!lpszSize)  return E_POINTER;

    *lpszSize = m_rcBox.Size();

    return S_OK;
}

HRESULT CxView::SetSize(SIZE szSize)
{
    return _set_box_rect(CRect(m_rcBox.TopLeft(), szSize));
}

HRESULT CxView::GetPosition(LPPOINT pptPos)
{
    if (!pptPos)    return E_POINTER;
    *pptPos = m_rcBox.TopLeft();
    return S_OK;
}

HRESULT CxView::SetPosition(POINT ptPos)
{
    return _set_box_rect(CRect(ptPos, m_rcBox.Size()));
}

HRESULT CxView::GetAlpha(LPBYTE pbyAlpha)
{
    if (!pbyAlpha)  return E_POINTER;

    *pbyAlpha = m_byAlpha;

    return S_OK;
}

HRESULT CxView::SetAlpha(BYTE byAlpha)
{
    m_byAlpha = byAlpha;
    return S_OK;
}

HRESULT CxView::GetShowState(LPBOOL pbShow)
{
    if (!pbShow)    return E_POINTER;
    *pbShow = m_bShow;
    return S_OK;
}

HRESULT CxView::SetShowState(BOOL bShow)
{
    m_bShow = !!bShow;
    return S_OK;
}

HRESULT CxView::GetVisibleState(LPBOOL pbVisible)
{
    // to do ...
    return S_OK;
}

HRESULT CxView::SetFocus()
{
    // to do ...
    return S_OK;
}

HRESULT CxView::GetFocusState(LPBOOL bFocus)
{
    // to do ...
    return S_OK;
}

HRESULT CxView::_set_box_rect(RECT& rcBox)
{
    CComPtr<IxView> spView = GetEntity<IxView>();
    if (spView)
        return spView->SetBoxRect(rcBox);
    else
        return E_FAIL;
}