#pragma once
#include "xKernel/IxElement.h"

class CxElement
    : public IxElement
{
public:
    CxElement();
    virtual ~CxElement();

    // interface of IxElement
    HRESULT GetID(LPINT pnID);
    HRESULT SetID(INT nID);

protected:

    template<class T>
    CComPtr<T> GetEntity()
    {
        CComPtr<T> p;
        QueryInterface(__uuidof(T), (VOID**)&p);
        return p;
    }

protected:
    INT     m_nID;
};