#include "stdafx.h"
#include "HotKeyMgr.h"

CHotKeyMgr::CHotKeyMgr()
{
    m_oWnd.Create();

    BOOL ret = ::RegisterHotKey(NULL, 100, MOD_CONTROL, VK_OEM_2);
    //ret = ::RegisterHotKey(NULL, 101, MOD_WIN|MOD_ALT, 'x');
}

CHotKeyMgr::~CHotKeyMgr()
{}