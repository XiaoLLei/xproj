#pragma once

[
    object,
    uuid("10AAECEC-A2F8-448c-B172-02295E8D9F46"),
    pointer_default(unique)
]
__interface IxTestService : IUnknown
{
    HRESULT Test();
};
