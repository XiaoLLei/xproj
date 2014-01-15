#pragma once

[
    object,
    uuid("BF9762E7-D1C4-4768-9368-6531D6D51DC3"),
    pointer_default(unique)
]
__interface IxLayout : IUnknown
{
    HRESULT Layout(IxView* pView);
};