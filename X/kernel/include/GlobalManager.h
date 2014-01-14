#pragma once

class CxGlobalManager
{
public:
    CxGlobalManager();
    virtual ~CxGlobalManager();

protected:
    ULONG_PTR           m_ulGdiplusToken;
};