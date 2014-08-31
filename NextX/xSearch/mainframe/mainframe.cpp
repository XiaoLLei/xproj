#include "stdafx.h"
#include "mainframe.h"

static const UINT kWndId            = 10000;
static const UINT kEditId           = 10001;
static const UINT kSearchBtnId      = 10002;

BEGIN_BGEVENT2_MAP(CMainFrame)
    ON_BGEVENT2_IE(kEditId,      xEvent_xEdit_KeyDown,      OnSearch)
    ON_BGEVENT2_IE(kEditId,      xEvent_Frame_Focus_Kill,   OnEditKillFocus)
    ON_BGEVENT2_IE(kSearchBtnId, xEvent_Btn_LBtn_Click,     OnSearchBtnClick)
END_BGEVENT2_MAP()

CMainFrame::CMainFrame()
    : m_strXml(L"skin:\\xsearch.xml|main")
    , m_spCanvas(NULL)
    , m_pEventObserver(this)
	, m_dwTickCount(0)
{
    m_pEventObserver->Hook_OnEvent(&CMainFrame::OnEvent);
    _init();
}

CMainFrame::~CMainFrame()
{

}

void CMainFrame::show()
{
    if (m_spCanvas)
    {
        m_spCanvas->ShowCanvas(SW_SHOW);
    }
}

void CMainFrame::OnSearch(bd::XuiRaiseEvent* pArg, BOOL& bCallNext)
{
    if (pArg)
    {
        KDARG* pData = pArg->as<KDARG*>();
        if (pData)
        {
            if (VK_RETURN == pData->nChars[0])
            {
                _do_search();
            }
        }
    }
}

void CMainFrame::OnEditKillFocus(bd::XuiRaiseEvent* pArg, BOOL& bCallNext)
{
    _move_to_corner();
}

void CMainFrame::OnSearchBtnClick(bd::XuiRaiseEvent* pArg, BOOL& bCallNext)
{
    _do_search();
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg && pMsg->message == WM_HOTKEY)
    {
        //DWORD curTickCount = ::GetTickCount();

        //if (m_dwTickCount > 0&& curTickCount - m_dwTickCount < 250)
        {
            if (m_spCanvas)
            {
                _move_to_center();
                HWND hwnd = m_spCanvas->GetHWnd();
                ::SetForegroundWindow(hwnd);
            }
        }

        //m_dwTickCount = ::GetTickCount();
    }

    return FALSE;
}

void CMainFrame::_init()
{
    do 
    {
        CComPtr<IxBuilder> pBuilder;
        ::util::GetService(__uuidof(IxBuilder), (void**)&pBuilder);
        ASSERT_BREAK(!pBuilder);

        CComPtr<IElement> spEle;

        pBuilder->CreateFromResource(CComBSTR(m_strXml), &spEle, NULL, m_pEventObserver);

        ASSERT_BREAK(!spEle);

        CComQIPtr<IxCanvas> spCanvas = spEle;
        m_spCanvas = spCanvas;
        ASSERT_BREAK(!m_spCanvas);

        HWND hWnd = m_spCanvas->GetHWnd();
        ASSERT_BREAK(!::IsWindow(hWnd));

        CComPtr<IFrame> spEditFrame;
        m_spCanvas->GetFrameByID(kEditId, &spEditFrame);
        m_spRichEdit = CComQIPtr<IxRichEdit>(spEditFrame);
        ATLASSERT(m_spRichEdit);

        _move_to_corner();

        spEditFrame->SetFrameFocus();

        CComPtr<IServiceThreadMgr> pServiceThreadMgr;
        Util::Com::GetService(__uuidof(IServiceThreadMgr), (VOID **)&pServiceThreadMgr);
        if (pServiceThreadMgr)
            pServiceThreadMgr->AddUIThreadMessageFilter(this);

    } while (FALSE);
}

void CMainFrame::_do_search()
{
    if (m_spRichEdit)
    {
        CComBSTR bsText;
        m_spRichEdit->GetText(&bsText);
        CString strText = bsText;
        strText.Trim();

        CString strUrl;
        strUrl.Format(L"http://www.baidu.com/s?wd=%s", strText);

        ::ShellExecute(0, _T("open"), strUrl, 0,0, SW_SHOWNORMAL);
    }
}

void CMainFrame::_move_to_corner()
{
    if (!m_spCanvas)
        return;

    HWND hWnd = m_spCanvas->GetHWnd();

    CRect rcWnd(0, 0, 0, 0);
    ::GetWindowRect(hWnd, &rcWnd);

    HMONITOR hMonitor = ::MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
    if (hMonitor)
    {
        MONITORINFO mi = {0};
        mi.cbSize = sizeof(mi);
        ::GetMonitorInfo(hMonitor, &mi);
        CPoint pt(0, 0);
        pt.x = mi.rcWork.right - rcWnd.Width() - 20;
        pt.y = mi.rcWork.top + 20;
        m_spCanvas->SetWindowPos(pt.x , pt.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

void CMainFrame::_move_to_center()
{
    m_spCanvas->CenterWindow();
}