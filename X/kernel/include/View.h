#pragma once
#include "xKernel/IxView.h"
#include "Node.h"

class CxView
    : public CxNode
    , public IxView
{
public:
    CxView();
    virtual ~CxView();

    // interface of IxView
    HRESULT STDMETHODCALLTYPE GetBoxRect(LPRECT lprcBox);
    HRESULT STDMETHODCALLTYPE SetBoxRect(RECT rcBox);

    HRESULT STDMETHODCALLTYPE GetSize(LPSIZE lpszSize);
    HRESULT STDMETHODCALLTYPE SetSize(SIZE szSize);

    HRESULT STDMETHODCALLTYPE GetPosition(LPPOINT pptPos);
    HRESULT STDMETHODCALLTYPE SetPosition(POINT ptPos);

    HRESULT STDMETHODCALLTYPE GetAlpha(LPBYTE pbyAlpha);
    HRESULT STDMETHODCALLTYPE SetAlpha(BYTE byAlpha);

    HRESULT STDMETHODCALLTYPE GetShowState(LPBOOL pbShow);
    HRESULT STDMETHODCALLTYPE SetShowState(BOOL bShow);

    HRESULT STDMETHODCALLTYPE GetVisibleState(LPBOOL pbVisible);

    HRESULT STDMETHODCALLTYPE SetFocus();
    HRESULT STDMETHODCALLTYPE GetFocusState(LPBOOL pbFocus);

protected:
    HRESULT _set_box_rect(RECT& rcBox);

protected:
    CRect   m_rcBox;
    BYTE    m_byAlpha;
    bool    m_bShow;
    bool    m_bEnable;
};