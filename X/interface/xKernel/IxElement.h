#pragma once

[
    object,
    uuid("851650CD-BD7C-486c-BBD1-48C93F80DC11"),
    pointer_default(unique)
]
__interface IxElement : IUnknown
{
    HRESULT GetID(LPINT pnID);
    HRESULT SetID(INT nID);
};