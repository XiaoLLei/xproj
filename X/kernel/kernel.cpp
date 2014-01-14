// kernel.cpp : Implementation of DLL Exports.


#include "stdafx.h"


// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{02EEDAF3-A0E2-41A3-872F-B75FE971F070}", 
         name = "kernel", 
         helpstring = "kernel 1.0 Type Library") ]
class CkernelModule
{
public:
    // Override CAtlDllModuleT members
};