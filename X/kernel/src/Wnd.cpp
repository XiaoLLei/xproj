#include "stdafx.h"
#include "xKernel/IxWndManager.h"
#include "xKernel/IxPaint.h"
#include "Wnd.h"

CxWnd::CxWnd()
    : m_spCanvas(NULL)
{
    ::xCommon::CreateObjectByIID(__uuidof(IxCanvas), (void**)&m_spCanvas);
    ATLASSERT(m_spCanvas);
}

CxWnd::~CxWnd()
{}

BOOL CxWnd::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
    SetMsgHandled(FALSE);

    _register();

    return FALSE;
}

void CxWnd::OnPaint(CDCHandle dc)
{
    PAINTSTRUCT ps = {0};
    BeginPaint(&ps);

    ATLASSERT(m_spCanvas);
    if (m_spCanvas)
    {
        SIZE sz = {0};
        m_spCanvas->GetSize(&sz);

        SIZE szWnd = {0};
        GetSize(&szWnd);

        if (szWnd.cx != sz.cx || szWnd.cy != sz.cy)
        {
            m_spCanvas->Create(ps.hdc, szWnd);
        }
    }

    CComPtr<IxPaint> spPaint = GetEntity<IxPaint>();
    if (spPaint)
    {
        spPaint->Paint(m_spCanvas);
    }

    for (NODEVEC::iterator it = m_vecChildren.begin(); it != m_vecChildren.end(); ++it)
    {
        CComQIPtr<IxPaint> spPaint = *it;
        if (spPaint)
        {
            spPaint->Paint(m_spCanvas);
        }
    }

    m_spCanvas->PaintToDC(CPoint(ps.rcPaint.left, ps.rcPaint.top), ps.hdc, ps.rcPaint);

    EndPaint(&ps);
}

void CxWnd::OnSize(UINT nType, CSize size)
{
    SetMsgHandled(FALSE);
}

void CxWnd::OnFinalMessage(HWND hWnd)
{
    __super::OnFinalMessage(hWnd);

    _unregister();
}

HRESULT CxWnd::CreateWnd()
{
    Create();
    ShowWindow(SW_SHOW);
    return S_OK;
}

HRESULT CxWnd::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* plRet, LPBOOL pbHandle)
{
    *pbHandle = FALSE;
    return S_OK;
}

HRESULT CxWnd::GetBoxRect(LPRECT lprcBox)
{
    if (!lprcBox)   return E_POINTER;

    GetClientRect(lprcBox);

    return S_OK;
}

HRESULT CxWnd::SetBoxRect(RECT rcBox)
{
    SetWindowPos(NULL, &rcBox, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    return S_OK;
}

HRESULT CxWnd::GetSize(LPSIZE lpszSize)
{
    if (!lpszSize)  return E_POINTER;

    RECT rc = {0};
    GetClientRect(&rc);

    lpszSize->cx = rc.right - rc.left;
    lpszSize->cy = rc.bottom - rc.top;

    return S_OK;
}

HRESULT CxWnd::SetSize(SIZE szSize)
{
    SetWindowPos(NULL, 0, 0, szSize.cx, szSize.cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE);
    return S_OK;
}

HRESULT CxWnd::GetPosition(LPPOINT pptPos)
{
    if (!pptPos)  return E_POINTER;

    RECT rc = {0};
    GetClientRect(&rc);

    pptPos->x = rc.left;
    pptPos->y = rc.top;

    return S_OK;
}

HRESULT CxWnd::SetPosition(POINT ptPos)
{
    SetWindowPos(NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE);
    return S_OK;
}

HRESULT CxWnd::GetAlpha(LPBYTE pbyAlpha)
{
    // to do ...
    return S_OK;
}

HRESULT CxWnd::SetAlpha(BYTE byAlpha)
{
    // to do ...
    return S_OK;
}

HRESULT CxWnd::GetShowState(LPBOOL pbShow)
{
    if (!pbShow)    return E_POINTER;

    *pbShow = IsWindowVisible();

    return S_OK;
}

HRESULT CxWnd::SetShowState(BOOL bShow)
{
    if (bShow != IsWindowVisible())
    {
        ShowWindow(bShow ? SW_SHOW : SW_HIDE);
    }
    return S_OK;
}

HRESULT CxWnd::GetVisibleState(LPBOOL pbVisible)
{
    return GetShowState(pbVisible);
}

HRESULT CxWnd::SetFocus()
{
    if (GetFocus() != m_hWnd)
    {
        SetFocus();
    }
    return S_OK;
}

HRESULT CxWnd::GetFocusState(LPBOOL pbFocus)
{
    if (!pbFocus)   return E_POINTER;

    *pbFocus = (GetFocus() == m_hWnd);

    return S_OK;
}

void CxWnd::_register()
{
    CComPtr<IxWndManager> spWndMgr;
    ::xCommon::GetService(__uuidof(IxWndManager), (void**)&spWndMgr);
    ATLASSERT(spWndMgr);
    if (spWndMgr)
    {
        spWndMgr->AddWnd(GetEntity<IxWnd>());
    }
}

void CxWnd::_unregister()
{
    CComPtr<IxWndManager> spWndMgr;
    ::xCommon::GetService(__uuidof(IxWndManager), (void**)&spWndMgr);
    ATLASSERT(spWndMgr);
    if (spWndMgr)
    {
        spWndMgr->RemoveWnd(GetEntity<IxWnd>());
    }
}