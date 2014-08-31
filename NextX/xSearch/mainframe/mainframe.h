#pragma once

#include "HotKeyMgr.h"

class CMainFrame : public Thread::CMessageFilter
{
public:
    CMainFrame();
    ~CMainFrame();

    void show();

    DECLARE_BGEVENT2_MAP();
    void OnSearch(bd::XuiRaiseEvent* pArg, BOOL& bCallNext);
    void OnEditKillFocus(bd::XuiRaiseEvent* pArg, BOOL& bCallNext);
    void OnSearchBtnClick(bd::XuiRaiseEvent* pArg, BOOL& bCallNext);

    BOOL PreTranslateMessage(MSG* pMsg);

protected:
    void _init();
    void _do_search();
    void _move_to_corner();
    void _move_to_center();

private:
    typedef CEventObserver2Ptr<CMainFrame>  OBSERVER2;

    CString             m_strXml;
    CComPtr<IxCanvas>   m_spCanvas;
    CComPtr<IxRichEdit> m_spRichEdit;
    OBSERVER2           m_pEventObserver;

	CHotKeyMgr			m_oHotKeyMgr;

	DWORD				m_dwTickCount;
};