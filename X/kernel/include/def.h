#pragma once

#define BEGIN_MSG_MAP_EX_UD(theClass)                                                                                       \
public:                                                                                                                     \
    BOOL m_bMsgHandled;                                                                                                     \
    /* "handled" management for cracked handlers */                                                                         \
    BOOL IsMsgHandled() const                                                                                               \
    {                                                                                                                       \
        return m_bMsgHandled;                                                                                               \
    }                                                                                                                       \
    void SetMsgHandled(BOOL bHandled)                                                                                       \
    {                                                                                                                       \
        m_bMsgHandled = bHandled;                                                                                           \
    }                                                                                                                       \
    BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)   \
    {                                                                                                                       \
        BOOL bOldMsgHandled = m_bMsgHandled;                                                                                \
        CComQIPtr<IxWndProc> spWndProc = GetEntity<IxWndProc>();                                                            \
        ATLASSERT(spWndProc);                                                                                               \
        if (spWndProc)                                                                                                      \
        {                                                                                                                   \
            spWndProc->ProcessMessage(uMsg, wParam, lParam, &lResult, &m_bMsgHandled);                                      \
        }                                                                                                                   \
        BOOL bRet = FALSE;                                                                                                  \
        if (m_bMsgHandled)                                                                                                  \
        {                                                                                                                   \
            bRet = TRUE;                                                                                                    \
        }                                                                                                                   \
        else                                                                                                                \
        {                                                                                                                   \
            bRet = _ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);                                  \
        }                                                                                                                   \
        m_bMsgHandled = bOldMsgHandled;                                                                                     \
        return bRet;                                                                                                        \
    }                                                                                                                       \
    BOOL _ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)      \
    {                                                                                                                       \
        BOOL bHandled = TRUE;                                                                                               \
        hWnd;                                                                                                               \
        uMsg;                                                                                                               \
        wParam;                                                                                                             \
        lParam;                                                                                                             \
        lResult;                                                                                                            \
        bHandled;                                                                                                           \
        switch(dwMsgMapID)                                                                                                  \
        {                                                                                                                   \
        case 0:

#define VIEW_INTERFACE()                                                                                                    \
    COM_INTERFACE_ENTRY(IxView)                                                                                             \
    COM_INTERFACE_ENTRY(IxNode)                                                                                             \
    COM_INTERFACE_ENTRY(IxElement)

#define WND_INTERFACE()                                                                                                     \
    COM_INTERFACE_ENTRY(IxWnd)                                                                                              \
    COM_INTERFACE_ENTRY(IxWndProc)                                                                                          \
    VIEW_INTERFACE()

#define BRUSHVIEW_INTERFACE()                                                                                               \
    COM_INTERFACE_ENTRY(IxBrushView)                                                                                        \
    VIEW_INTERFACE()