#include "stdafx.h"
#include "Test.h"

HRESULT CxTest::Test()
{
    ::MessageBox(NULL, _T("CxTest::Test()"), _T("IxTest"), MB_OK);
    return S_OK;
}