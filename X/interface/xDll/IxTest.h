#pragma once

[
    object,
    uuid("ACF501B6-D4C8-47c2-AF16-41530E778871"),
    pointer_default(unique)
]
__interface IxTest : IUnknown
{
    HRESULT Test();
};
