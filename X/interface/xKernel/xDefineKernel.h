#pragma once

enum _xMsgId
{
    //////////////////////////////////////////////////////////////////////////
    XM_DEPTH_CHANGE         = (WM_USER + 1),
    //////////////////////////////////////////////////////////////////////////
};

typedef struct _xEventParam
{
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    BOOL        bHandled;

    _xEventParam()
        : message(0)
        , wParam(0)
        , lParam(0)
        , bHandled(FALSE)
    {}
}EVENTPARAM, *LPEVENTPARAM;