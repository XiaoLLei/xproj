#pragma once

namespace xCommon
{
    namespace xUtil
    {
        inline CString GetModuleDir(HMODULE hModule)
        {
            TCHAR strFullPath[MAX_PATH] = {0};
            ::GetModuleFileName(hModule, strFullPath, MAX_PATH);
            ::PathRemoveFileSpec(strFullPath);
            return strFullPath;
        }

        template <typename F>
        static HRESULT GetProcAddress(HMODULE hMod, const char* funcname, F** funcptr)
        {
            if (!hMod || !funcname || !funcptr)
                return E_INVALIDARG;
            *funcptr = (F*)::GetProcAddress(hMod, funcname);
            if (NULL == *funcptr)
                return E_FAIL;
            return S_OK;
        }
    }
}