#include "xDll/IxTestService.h"

[
    default(IxTestService),
    threading(free),
    uuid("C387536E-8971-4aa4-8218-6F1E52019A9C"),
    coclass
]
class CxTestService : public IxTestService
{
public:
    HRESULT Test();
};