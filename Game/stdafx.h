#pragma once
#ifndef __stdafx_h__
#define __stdafx_h__

#define SAFE_DELETE(PTR) {if(PTR) delete PTR; PTR = nullptr;}
#define SAFE_DELETE_ARR(ARR) {if(ARR) delete[] ARR; ARR = nullptr;}

#include "framework.h"
#include "Global.h"

#include "../Base/Base.h"
#include "../Base/BaseStdafx.h"
#include "CompGenerator.h"

#include <map>
#include <io.h>
#include "fmod.h"
#pragma comment (lib, "fmodex_vc.lib")

#endif
