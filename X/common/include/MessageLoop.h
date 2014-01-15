#pragma once
#include "xCommon/IxMessageLoop.h"
#include "xCommon/IxService.h"

[
    default(IxMessageLoop),
    threading(free),
    uuid("C98C1787-DC1A-43fe-897E-BA0C7E172A85"),
    coclass
]
class CxMessageLoop
    : public IxMessageLoop
    , public IxService
{
public:
    CxMessageLoop();
    virtual ~CxMessageLoop();

    DECLARE_PROTECT_FINAL_CONSTRUCT()
    HRESULT STDMETHODCALLTYPE FinalConstruct();
    void    STDMETHODCALLTYPE FinalRelease();

    struct RunState
    {
        INT     m_nDepth;
    };

    class AutoRunState : RunState
    {
    public:
        explicit AutoRunState(CxMessageLoop* loop);
        ~AutoRunState();

    private:
        CxMessageLoop*      m_pLoop;
        RunState*           m_pPreviousState;
    };

public:
    // interface of IxMessageLoop
    HRESULT Run();
    HRESULT Quit();
    HRESULT QuitAll();

    // interface of IxService
    HRESULT InitService();
    HRESULT UninitService();

protected:
    RunState*           m_pState;
};