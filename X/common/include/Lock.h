#pragma once

namespace xCommon
{
    class CxLock
    {
    public:
        CxLock();
        ~CxLock();

        VOID Acquire();
        VOID Release();

        BOOL Try();

    private:
        CRITICAL_SECTION m_cs;

    protected:
        CxLock(const CxLock& other);
        CxLock& operator = (const CxLock& other);
    };

    class CxAutoLock
    {
    public:
        explicit CxAutoLock(CxLock& lock)
            : m_Lock(lock)
        {
            m_Lock.Acquire();
        }

        ~ CxAutoLock()
        {
            m_Lock.Release();
        }

    private:
        CxLock & m_Lock;

    private:
        CxAutoLock(const CxAutoLock& other);
        CxAutoLock & operator == (const CxAutoLock & right);
    };
}

namespace xCommon
{
    inline CxLock::CxLock()
    {
        ::InitializeCriticalSectionAndSpinCount(&m_cs, 2000);
    }

    inline CxLock::~CxLock()
    {
        ::DeleteCriticalSection(&m_cs);
    }

    inline VOID CxLock::Acquire()
    {
        ::EnterCriticalSection(&m_cs);
    }

    inline VOID CxLock::Release()
    {
        ::LeaveCriticalSection(&m_cs);
    }

    inline BOOL CxLock::Try()
    {
        if (FALSE != ::TryEnterCriticalSection(&m_cs))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}