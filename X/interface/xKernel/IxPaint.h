#pragma once

#include "xKernel/IxCanvas.h"

[
    object,
    uuid("95FC3EC1-E302-46ca-B165-B75C0C60DA75"),
    pointer_default(unique)
]
__interface IxPaint : IUnknown
{
    HRESULT Paint(IxCanvas* pCanvas);
};