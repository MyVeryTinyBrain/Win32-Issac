#pragma once
#ifndef __ResourceLoader_h__
#define __ResourceLoader_h__

class ResourceLoader
{
private:
	static TCHAR g_Buffer[1024];

public:
	// Example
	// folderPath: ../Image/Character/
	// bmpName: player
	// result: ../Image/Character/player.bmp
	static const TCHAR* MakeFullPath(const TCHAR* folderPath, const TCHAR* bmpName);
	// Example
	// bmpName:: player
	// subText: motion01
	// result: player/motion01
	static const TCHAR* MakeSpriteKey(const TCHAR* bmpName, const TCHAR* subText);

public:
	static void LoadRoomResources(const TCHAR* folderPath, const TCHAR* bmpName);
	static void LoadDoorResources(const TCHAR* folderPath, const TCHAR* bmpName);
	static void LoadKeyResources(const TCHAR* folderPath, const TCHAR* bmpName);

	static void LoadPlayerResources(const TCHAR* folderPath, const TCHAR* bmpName);
	static void LoadBrimstonPlayerResources();

	static void LoadTearResources();
	static void LoadBloodTearResources();
	static void LoadBrimstonLaserResources();

	static void LoadBombResources();

	static void LoadItemBombResources();
	static void LoadItemKeyResources();
	static void LoadItemCoinResources();
	static void LoadItemHeartResources();

	static void LoadShadowResources();
	static void LoadTargetResources();
	static void LoadPoolResources();

	static void LoadSmallFlyResources();
	static void LoadGaperHeadResources();
	static void LoadMuliboomHeadResources();
	static void LoadBabyMonsterResources();

	static void LoadBabyPlumBossResources();
	static void LoadBlueBabayBossResources();

	static void LoadBloodPoofResources();
	static void LoadPoofResources();

	static void LoadObstacleResources();

	static void LoadItemResources();

	static void LoadUIResources();

	static void LoadIsaacFontResources();

	static void LoadStartRoomResources();

	static void LoadTestResources();

	static void Release();
};

#endif
