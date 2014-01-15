#include "stdafx.h"
#include "MessageLoop.h"

CxMessageLoop::CxMessageLoop()
    : m_pState(NULL)
{}

CxMessageLoop::~CxMessageLoop()
{}

HRESULT CxMessageLoop::FinalConstruct()
{
    return S_OK;
}

void CxMessageLoop::FinalRelease()
{
}

HRESULT CxMessageLoop::Run()
{
    AutoRunState state(this);

    MSG msg = {0};

    while ( ::GetMessage(&msg, NULL, 0, 0) )
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return S_OK;
}

HRESULT CxMessageLoop::Quit()
{
    ::PostQuitMessage(0);
    return S_OK;;
}

HRESULT CxMessageLoop::QuitAll()
{
    ::PostQuitMessage(0);
    return S_OK;
}

HRESULT CxMessageLoop::InitService()
{
    return S_OK;
}

HRESULT CxMessageLoop::UninitService()
{
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
CxMessageLoop::AutoRunState::AutoRunState(CxMessageLoop* loop) : m_pLoop(loop)
{
    m_pPreviousState = m_pLoop->m_pState;

    if (m_pPreviousState)
    {
        m_nDepth = m_pPreviousState->m_nDepth + 1;
    }
    else
    {
        m_nDepth = 1;
    }

    m_pLoop->m_pState = this;
}

CxMessageLoop::AutoRunState::~AutoRunState()
{
    m_pLoop->m_pState = m_pPreviousState;
}