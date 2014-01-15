#pragma once
#include "xKernel/IxWnd.h"
#include "xKernel/IxWndProc.h"
#include "def.h"
#include "View.h"

class CxWnd
    : public CxView
    , public IxWnd
    , public IxWndProc
    , public CFrameWindowImpl<CxWnd>
{
    typedef CFrameWindowImpl<CxWnd> __wndclass;
public:
    CxWnd();
    virtual ~CxWnd();

    BEGIN_MSG_MAP_EX_UD(CxWnd)
        MSG_WM_NCCREATE(OnNcCreate)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_SIZE(OnSize)
        CHAIN_MSG_MAP(__wndclass)
    END_MSG_MAP()

    virtual BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
    virtual void OnPaint(CDCHandle dc);
    virtual void OnSize(UINT nType, CSize size);
    virtual void OnFinalMessage(HWND hWnd);

public:
    // interface of IxWnd
    HRESULT CreateWnd();

    // interface of IxWndProc
    HRESULT STDMETHODCALLTYPE ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* plRet, LPBOOL pbHandle);

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
    void _register();
    void _unregister();

protected:
    CComPtr<IxCanvas>       m_spCanvas;
};


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