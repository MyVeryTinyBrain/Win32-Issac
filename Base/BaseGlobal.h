#pragma once
#ifndef __BaseGlobal_h__
#define __BaseGlobal_h__

class HDCEx;

namespace BaseGlobal
{
	extern HWND* pHWND;
	extern HDCEx* pHDCEx;
	extern ULONG* pCX;
	extern ULONG* pCY;
	extern float* pDeltaTime;
	extern float* pUnscaledDeltaTime;

	// Base 라이브러리를 사용하기 전에 꼭 한번 호출해 줘야 합니다.
	extern void Init(HWND* pHWND, HDCEx* pMainHDCEx, ULONG* pWinCX, ULONG* pWinCY, float* pDeltaTime, float* pUnscaledDeltaTime);
}

#endif
