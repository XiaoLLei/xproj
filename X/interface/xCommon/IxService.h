#pragma once

[
    object,
    uuid("A5B1772B-6D14-4420-99BE-AF2E4030EEE5"),
    pointer_default(unique)
]
__interface IxService : IUnknown
{
    HRESULT InitService();
    HRESULT UninitService();
};
