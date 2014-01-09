#include "stdafx.h"
#include "TestService.h"

HRESULT CxTestService::Test()
{
    ::MessageBox(NULL, _T("CxTestService::Test"), _T("IxTestService"), MB_OK);
    return S_OK;
}