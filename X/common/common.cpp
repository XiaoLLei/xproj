// common.cpp : Implementation of DLL Exports.


#include "stdafx.h"


// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{109DF5F0-678C-4032-AFCE-AA3A29417705}", 
		 name = "common", 
		 helpstring = "common 1.0 Type Library") ]
class CcommonModule
{
public:
	// Override CAtlDllModuleT members
};