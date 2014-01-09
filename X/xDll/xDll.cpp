// xDll.cpp : Implementation of DLL Exports.


#include "stdafx.h"


// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{05AB2818-AD54-42F8-8CC2-75038DCB8349}", 
         name = "xDll", 
         helpstring = "xDll 1.0 Type Library") ]
class CxDllModule
{
public:
    // Override CAtlDllModuleT members
};