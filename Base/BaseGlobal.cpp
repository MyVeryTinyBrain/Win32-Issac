#include "BaseStdafx.h"
#include "BaseGlobal.h"
#include <time.h>
#include <random>

namespace BaseGlobal
{
	HWND* pHWND = NULL;
	HDCEx* pHDCEx = NULL;
	ULONG* pCX = nullptr;
	ULONG* pCY = nullptr;
	float* pDeltaTime = nullptr;
	float* pUnscaledDeltaTime = nullptr;

	void Init(HWND* pHWND, HDCEx* pMainHDCEx, ULONG* pWinCX, ULONG* pWinCY, float* pDeltaTime, float* pUnscaledDeltaTime)
	{
		BaseGlobal::pHWND = pHWND;
		BaseGlobal::pHDCEx = pMainHDCEx;
		BaseGlobal::pCX = pWinCX;
		BaseGlobal::pCY = pWinCY;
		BaseGlobal::pDeltaTime = pDeltaTime;
		BaseGlobal::pUnscaledDeltaTime = pUnscaledDeltaTime;
		srand((unsigned int)time(NULL));
	}
}