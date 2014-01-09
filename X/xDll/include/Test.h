#include "xDll/IxTest.h"

[
    default(IxTest),
    threading(free),
    uuid("E0EAE91D-C180-4bff-A195-35A39AF09C6D"),
    coclass
]
class CxTest : public IxTest
{
public:
    HRESULT Test();
};