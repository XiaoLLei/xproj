#pragma once

[
    object,
    uuid("3D671AC9-F3E8-403f-9FEC-213C5BF83B9E"),
    pointer_default(unique)
]
__interface IxService : IUnknown
{
    HRESULT InitService();
    HRESULT UninitService();
};
