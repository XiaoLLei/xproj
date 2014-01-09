#include "stdafx.h"
#include "AutoDo.h"

CxAutoDo::CxAutoDo()
{
    ::CoInitialize(NULL);
    ::OleInitialize(NULL);
}

CxAutoDo::~CxAutoDo()
{
    ::OleUninitialize();
    ::CoUninitialize();
}