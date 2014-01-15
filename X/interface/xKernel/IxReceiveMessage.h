#pragma once

[
    object,
    uuid("FBBC02E0-C0DF-4d4c-9193-574E4B16F49A"),
    pointer_default(unique)
]
__interface IxReceiveMessage : IUnknown
{
    HRESULT OnMessage(LPEVENTPARAM params, LPBOOL pbHandled);
};