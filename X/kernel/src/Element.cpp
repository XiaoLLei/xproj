#include "stdafx.h"
#include "element.h"

CxElement::CxElement()
    : m_nID(0)
{}

CxElement::~CxElement()
{}

HRESULT CxElement::GetID(LPINT pnID)
{
    if (*pnID)  return E_POINTER;

    *pnID = m_nID;

    return S_OK;
}

HRESULT CxElement::SetID(INT nID)
{
    m_nID = nID;
    return S_OK;
}