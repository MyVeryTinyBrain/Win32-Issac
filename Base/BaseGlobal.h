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

	// Base ���̺귯���� ����ϱ� ���� �� �ѹ� ȣ���� ��� �մϴ�.
	extern void Init(HWND* pHWND, HDCEx* pMainHDCEx, ULONG* pWinCX, ULONG* pWinCY, float* pDeltaTime, float* pUnscaledDeltaTime);
}

#endif
