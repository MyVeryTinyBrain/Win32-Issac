#pragma once
#ifndef __BaseStdafx_h__
#define __BaseStdafx_h__

#define USE_CONSOLE
#ifdef USE_CONSOLE
#include <iostream>
using std::cout;
using std::endl;
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#endif

#define BASE_SAFE_DELETE(PTR) {if(PTR) delete PTR; PTR = nullptr;}
#define BASE_SAFE_DELETE_ARR(ARR) {if(ARR) delete[] ARR; ARR = nullptr;}

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>

#include "Math.h"
#include "Delegate.h"
#include "BaseGlobal.h"

#endif
