#include "stdafx.h"
#include "Global.h"

namespace Global
{
	HDC hdc = NULL;
	HWND hWnd = NULL;
	float fps = 60.0f;
	ULONG cx = 936;
	ULONG cy = 624;
	float deltaTime = 0;
	float unscaledDeltaTime = 0;
	float timeScale = 1;
}