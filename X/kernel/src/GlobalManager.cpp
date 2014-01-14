#include "stdafx.h"
#include "GlobalManager.h"

using namespace Gdiplus;

CxGlobalManager g_oMgr;

CxGlobalManager::CxGlobalManager()
    : m_ulGdiplusToken(0)
{
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_ulGdiplusToken, &gdiplusStartupInput, NULL);
}

CxGlobalManager::~CxGlobalManager()
{
    GdiplusShutdown(m_ulGdiplusToken);
}