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
    HRESULT GetBoxRect(LPRECT lprcBox);
    HRESULT SetBoxRect(RECT rcBox);

    HRESULT GetSize(LPSIZE lpszSize);
    HRESULT SetSize(SIZE szSize);

    HRESULT GetPosition(LPPOINT pptPos);
    HRESULT SetPosition(POINT ptPos);

    HRESULT GetAlpha(LPBYTE pbyAlpha);
    HRESULT SetAlpha(BYTE byAlpha);

    HRESULT GetShowState(LPBOOL pbShow);
    HRESULT SetShowState(BOOL bShow);

    HRESULT GetVisibleState(LPBOOL pbVisible);

    HRESULT SetFocus();
    HRESULT GetFocusState(LPBOOL bFocus);

protected:
    HRESULT _set_box_rect(RECT& rcBox);

protected:
    CRect   m_rcBox;
    BYTE    m_byAlpha;
    bool    m_bShow;
    bool    m_bEnable;
};