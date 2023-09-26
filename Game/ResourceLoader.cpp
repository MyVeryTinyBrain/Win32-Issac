#include "stdafx.h"
#include "ResourceLoader.h"

TCHAR ResourceLoader::g_Buffer[1024] = {};

const TCHAR* ResourceLoader::MakeFullPath(const TCHAR* folderPath, const TCHAR* bmpName)
{
	ZeroMemory(g_Buffer, sizeof(g_Buffer));
	_tcscpy_s(g_Buffer, folderPath);
	_tcscat_s(g_Buffer, bmpName);
	_tcscat_s(g_Buffer, TEXT(".bmp"));
	return g_Buffer;
}

const TCHAR* ResourceLoader::MakeSpriteKey(const TCHAR* bmpName, const TCHAR* subText)
{
	ZeroMemory(g_Buffer, sizeof(g_Buffer));
	_tcscpy_s(g_Buffer, bmpName);
	_tcscat_s(g_Buffer, TEXT("/"));
	_tcscat_s(g_Buffer, subText);
	return g_Buffer;
}

void ResourceLoader::LoadRoomResources(const TCHAR* folderPath, const TCHAR* bmpName)
{
	HDCEx* bmp = BitmapManager::Load(MakeFullPath(folderPath, bmpName), bmpName);

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 234, 156, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall01")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 234, 0, 234, 156, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall02")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 156, 234, 156, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall03")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 234, 156, 234, 156, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall04")));
	
	SpriteManager::MakeNewInSheet(bmp, 52, 364, 182, 104, MakeSpriteKey(bmpName, TEXT("floor01")));
	SpriteManager::MakeNewInSheet(bmp, 286, 364, 182, 104, MakeSpriteKey(bmpName, TEXT("floor02")));
	
	SpriteManager::MakeNewInSheet(bmp, 468, 0, 52, 52, MakeSpriteKey(bmpName, TEXT("corner01")));
	SpriteManager::MakeNewInSheet(bmp, 468, 52, 52, 52, MakeSpriteKey(bmpName, TEXT("corner02")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 52, 0, 182, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_hor_01")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 52, 52, 104, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_ver_01")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 286, 0, 182, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_hor_02")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 234, 52, 52, 104, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_ver_02")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 52, 156, 182, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_hor_03")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 208, 52, 104, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_ver_03")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 286, 156, 182, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_hor_04")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 234, 208, 52, 104, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("wall_sliced_ver_04")));
}

void ResourceLoader::LoadDoorResources(const TCHAR* folderPath, const TCHAR* bmpName)
{
	HDCEx* bmp = BitmapManager::Load(MakeFullPath(folderPath, bmpName), bmpName);

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 64, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("frame")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 0, 64, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("inside")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 52, 64, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("left1")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 22, 52, 24, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("left2")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 26, 52, 22, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("left3")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 30, 52, 22, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("left4")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 52, 64, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right1")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 82, 52, 25, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right2")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 80, 52, 23, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right3")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 77, 52, 23, 52, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right4")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 106, 64, 40, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right_locked1")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 82, 106, 25, 40, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right_locked2")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 80, 106, 23, 40, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right_locked3")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 77, 106, 23, 40, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("right_locked4")));
}

void ResourceLoader::LoadKeyResources(const TCHAR* folderPath, const TCHAR* bmpName)
{
	HDCEx* bmp = BitmapManager::Load(MakeFullPath(folderPath, bmpName), bmpName);

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 145, 32, 16, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("keyanim_01")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 145, 32, 16, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("keyanim_02")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 145, 32, 16, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("keyanim_03")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 145, 32, 16, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("keyanim_04")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 104, 166, 17, 24, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("key")));
}

void ResourceLoader::LoadPlayerResources(const TCHAR* folderPath, const TCHAR* bmpName)
{
	HDCEx* bmp = BitmapManager::Load(MakeFullPath(folderPath, bmpName), bmpName);

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 32, 29, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("head_forward")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 0, 32, 29, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("head_forward_close")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 0, 32, 29, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("head_right")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 0, 32, 29, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("head_right_close")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 0, 32, 29, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("head_back")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 160, 0, 32, 29, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("head_back_close")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 7, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward1")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 224, 7, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward2")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward3")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward4")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward5")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward6")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward7")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 160, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward8")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward9")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 224, 39, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_forward10")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right1")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right2")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right3")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right4")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right5")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 160, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right6")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right7")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 224, 71, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right8")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 102, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right9")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 102, 32, 23, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("body_right10")));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 198, 64, 64, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("got_item")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 262, 64, 64, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("jump1")));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 262, 64, 64, RGB(255, 0, 0), MakeSpriteKey(bmpName, TEXT("jump2")));
}

void ResourceLoader::LoadBrimstonPlayerResources()
{
	HDCEx* head2 = BitmapManager::Load(TEXT("../Image/Character/costume_019_brimstone2.bmp"), TEXT("Character/costume_019_brimstone2"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 0, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward1"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 64, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward2"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 128, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward3"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 192, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward4"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 256, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward5"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 320, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward6"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 384, 0, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward7"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 0, 192, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_forward_fire"));

	SpriteManager::MakeNewToTransparentInSheet(head2, 0, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right1"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 64, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right2"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 128, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right3"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 192, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right4"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 256, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right5"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 320, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right6"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 384, 64, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right7"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 0, 256, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_right_fire"));

	SpriteManager::MakeNewToTransparentInSheet(head2, 0, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back1"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 64, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back2"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 128, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back3"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 192, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back4"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 256, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back5"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 320, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back6"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 384, 128, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back7"));
	SpriteManager::MakeNewToTransparentInSheet(head2, 0, 320, 64, 64, RGB(255, 0, 0), TEXT("costume_019_brimstone2/head_back_fire"));

	HDCEx* body = BitmapManager::Load(TEXT("../Image/Character/costume_019_brimstone body.bmp"), TEXT("Character/costume_019_brimstone body"));

	SpriteManager::MakeNewToTransparentInSheet(body, 0, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right1"));
	SpriteManager::MakeNewToTransparentInSheet(body, 32, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right2"));
	SpriteManager::MakeNewToTransparentInSheet(body, 64, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right3"));
	SpriteManager::MakeNewToTransparentInSheet(body, 96, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right4"));
	SpriteManager::MakeNewToTransparentInSheet(body, 128, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right5"));
	SpriteManager::MakeNewToTransparentInSheet(body, 160, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right6"));
	SpriteManager::MakeNewToTransparentInSheet(body, 192, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right7"));
	SpriteManager::MakeNewToTransparentInSheet(body, 224, 0, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right8"));
	SpriteManager::MakeNewToTransparentInSheet(body, 0, 32, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right9"));
	SpriteManager::MakeNewToTransparentInSheet(body, 32, 32, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_right10"));

	SpriteManager::MakeNewToTransparentInSheet(body, 0, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward1"));
	SpriteManager::MakeNewToTransparentInSheet(body, 32, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward2"));
	SpriteManager::MakeNewToTransparentInSheet(body, 64, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward3"));
	SpriteManager::MakeNewToTransparentInSheet(body, 96, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward4"));
	SpriteManager::MakeNewToTransparentInSheet(body, 128, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward5"));
	SpriteManager::MakeNewToTransparentInSheet(body, 160, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward6"));
	SpriteManager::MakeNewToTransparentInSheet(body, 192, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward7"));
	SpriteManager::MakeNewToTransparentInSheet(body, 224, 64, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward8"));
	SpriteManager::MakeNewToTransparentInSheet(body, 0, 96, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward9"));
	SpriteManager::MakeNewToTransparentInSheet(body, 32, 96, 32, 32, RGB(255, 0, 0), TEXT("costume_019_brimstone2/body_forward10"));
}

void ResourceLoader::LoadTearResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Effect/effect_015_tearpoofa.bmp"), TEXT("Effect/effect_015_tearpoofa"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/03"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/04"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/05"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/06"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/07"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/08"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/09"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/10"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/11"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/12"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/13"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/14"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/15"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_015_tearpoofa/16"));
}

void ResourceLoader::LoadBloodTearResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Effect/effect_003_bloodtear.bmp"), TEXT("Effect/effect_003_bloodtear"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/03"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 0, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/04"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/05"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/06"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/07"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 64, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/08"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/09"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/10"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/11"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 128, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/12"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/13"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/14"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/15"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 192, 64, 64, RGB(255, 0, 0), TEXT("effect_003_bloodtear/16"));
}

void ResourceLoader::LoadBrimstonLaserResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Effect/effect_018_brimstonelaser.bmp"), TEXT("Effect/effect_018_brimstonelaser"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 112, 256, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/1"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 112, 0, 112, 256, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/2"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 224, 0, 112, 256, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/3"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 336, 0, 112, 256, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/4"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 457, 0, 92, 96, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/sphere1"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 551, 0, 92, 96, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/sphere2"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 457, 97, 92, 96, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/sphere3"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 551, 97, 92, 96, RGB(255, 255, 255), TEXT("effect_018_brimstonelaser/sphere4"));

	HDCEx* hitBmp = BitmapManager::Load(TEXT("../Image/Effect/effect_brimstoneimpact.bmp"), TEXT("Effect/effect_brimstoneimpact"));
	SpriteManager::MakeNewToTransparentInSheet(hitBmp, 0, 0, 64, 64, RGB(255, 255, 255), TEXT("effect_brimstoneimpact/1"));
	SpriteManager::MakeNewToTransparentInSheet(hitBmp, 64, 0, 64, 64, RGB(255, 255, 255), TEXT("effect_brimstoneimpact/2"));
	SpriteManager::MakeNewToTransparentInSheet(hitBmp, 0, 64, 64, 64, RGB(255, 255, 255), TEXT("effect_brimstoneimpact/3"));
	SpriteManager::MakeNewToTransparentInSheet(hitBmp, 64, 64, 64, 64, RGB(255, 255, 255), TEXT("effect_brimstoneimpact/4"));
}

void ResourceLoader::LoadBombResources()
{
	HDCEx* bombBmp = BitmapManager::Load(TEXT("../Image/Item/pickup_016_bomb.bmp"), TEXT("Item/pickup_016_bomb"));

	SpriteManager::MakeNewToTransparentInSheet(bombBmp, 0, 0, 32, 32, RGB(255, 0, 0), TEXT("pickup_016_bomb/default"));
	SpriteManager::MakeNewToTransparentInSheet(bombBmp, 32, 31, 33, 35, RGB(255, 0, 0), TEXT("pickup_016_bomb/trol"));

	HDCEx* bombRadBmp = BitmapManager::Load(TEXT("../Image/Effect/effect_017_bombradius.bmp"), TEXT("Effect/effect_017_bombradius"));

	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 0, 0, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/01"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 96, 0, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/02"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 0, 64, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/03"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 96, 64, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/04"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 0, 128, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/05"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 96, 128, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/06"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 0, 192, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/07"));
	SpriteManager::MakeNewToTransparentInSheet(bombRadBmp, 96, 192, 96, 64, RGB(255, 255, 255), TEXT("effect_017_bombradius/08"));

	HDCEx* bombExpl = BitmapManager::Load(TEXT("../Image/Effect/effect_029_explosion.bmp"), TEXT("Effect/effect_029_explosion"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 0, 0, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/01"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 96, 0, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/02"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 192, 0, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/03"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 288, 0, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/04"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 0, 96, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/05"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 96, 96, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/06"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 192, 96, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/07"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 288, 96, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/08"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 0, 192, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/09"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 96, 192, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/10"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 192, 192, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/11"));
	SpriteManager::MakeNewToTransparentInSheet(bombExpl, 288, 192, 96, 96, RGB(255, 255, 255), TEXT("effect_029_explosion/12"));
}

void ResourceLoader::LoadItemBombResources()
{
	//LoadBombResources();
}

void ResourceLoader::LoadItemKeyResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Item/pickup_003_charged_key.bmp"), TEXT("Item/pickup_003_charged_key"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 5, 15, 20, RGB(255, 0, 0), TEXT("pickup_003_charged_key"));
}

void ResourceLoader::LoadItemCoinResources()
{
	HDCEx* yelCoin = BitmapManager::Load(TEXT("../Image/Item/pickup_002_coin.bmp"), TEXT("Item/pickup_002_coin"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 0, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/01"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 18, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/02"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 0, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/03"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 18, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/04"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 0, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/05"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 18, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/06"));

	HDCEx* blkCoin = BitmapManager::Load(TEXT("../Image/Item/pickup_002_coinblack.bmp"), TEXT("Item/pickup_002_coinblack"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 0, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/01"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 18, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/02"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 0, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/03"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 18, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/04"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 0, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/05"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 18, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/06"));
}

void ResourceLoader::LoadItemHeartResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Item/pickup_001_heart.bmp"), TEXT("Item/pickup_001_heart"));
}

void ResourceLoader::LoadShadowResources()
{
	HDCEx* shadowBmp = BitmapManager::Load(TEXT("../Image/Effect/shadow.bmp"), TEXT("Effect/shadow"));

	SpriteManager::MakeToTransparent(shadowBmp, RGB(255, 255, 255), TEXT("shadow"));
}

void ResourceLoader::LoadTargetResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Effect/target.bmp"), TEXT("Effect/target"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 32, 32, RGB(0, 0, 0), TEXT("target"));
}

void ResourceLoader::LoadPoolResources()
{
	HDCEx* smallPool = BitmapManager::Load(TEXT("../Image/Effect/effect_016_pool_small.bmp"), TEXT("Effect/effect_016_pool_small"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 0, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/1"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 32, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/2"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 0, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/3"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 32, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/4"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 0, 64, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/5"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 32, 64, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/6"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 0, 96, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/7"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 32, 96, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/8"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 0, 128, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/9"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 32, 128, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/10"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 0, 160, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/11"));
	SpriteManager::MakeNewToTransparentInSheet(smallPool, 32, 160, 32, 32, RGB(255, 255, 255), TEXT("effect_016_pool_small/12"));

	HDCEx* regularPool = BitmapManager::Load(TEXT("../Image/Effect/effect_016_pool_regular.bmp"), TEXT("Effect/effect_016_pool_regular"));
	SpriteManager::MakeNewToTransparentInSheet(regularPool, 0, 0, 48, 47, RGB(255, 255, 255), TEXT("effect_016_pool_regular/1"));
	SpriteManager::MakeNewToTransparentInSheet(regularPool, 48, 0, 48, 47, RGB(255, 255, 255), TEXT("effect_016_pool_regular/2"));
	SpriteManager::MakeNewToTransparentInSheet(regularPool, 0, 47, 48, 47, RGB(255, 255, 255), TEXT("effect_016_pool_regular/3"));
	SpriteManager::MakeNewToTransparentInSheet(regularPool, 48, 47, 48, 47, RGB(255, 255, 255), TEXT("effect_016_pool_regular/4"));
	SpriteManager::MakeNewToTransparentInSheet(regularPool, 0, 94, 48, 47, RGB(255, 255, 255), TEXT("effect_016_pool_regular/5"));
	SpriteManager::MakeNewToTransparentInSheet(regularPool, 48, 94, 48, 47, RGB(255, 255, 255), TEXT("effect_016_pool_regular/6"));

	HDCEx* largePool = BitmapManager::Load(TEXT("../Image/Effect/effect_016_pool_large.bmp"), TEXT("Effect/effect_016_pool_large"));
	SpriteManager::MakeNewToTransparentInSheet(largePool, 0, 0, 98, 96, RGB(255, 255, 255), TEXT("effect_016_pool_large/1"));
	SpriteManager::MakeNewToTransparentInSheet(largePool, 98, 0, 98, 96, RGB(255, 255, 255), TEXT("effect_016_pool_large/2"));
	SpriteManager::MakeNewToTransparentInSheet(largePool, 196, 0, 98, 96, RGB(255, 255, 255), TEXT("effect_016_pool_large/3"));
	SpriteManager::MakeNewToTransparentInSheet(largePool, 0, 98, 98, 94, RGB(255, 255, 255), TEXT("effect_016_pool_large/4"));
	SpriteManager::MakeNewToTransparentInSheet(largePool, 98, 98, 98, 94, RGB(255, 255, 255), TEXT("effect_016_pool_large/5"));
	SpriteManager::MakeNewToTransparentInSheet(largePool, 196, 98, 98, 94, RGB(255, 255, 255), TEXT("effect_016_pool_large/6"));


	HDCEx* smallBPool = BitmapManager::Load(TEXT("../Image/Effect/effect_016_bloodpool_small.bmp"), TEXT("Effect/effect_016_bloodpool_small"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 0, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/1"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 32, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/2"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 0, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/3"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 32, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/4"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 0, 64, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/5"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 32, 64, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/6"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 0, 96, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/7"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 32, 96, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/8"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 0, 128, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/9"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 32, 128, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/10"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 0, 160, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/11"));
	SpriteManager::MakeNewToTransparentInSheet(smallBPool, 32, 160, 32, 32, RGB(255, 255, 255), TEXT("effect_016_bloodpool_small/12"));

	HDCEx* regularBPool = BitmapManager::Load(TEXT("../Image/Effect/effect_016_bloodpool_regular.bmp"), TEXT("Effect/effect_016_bloodpool_regular"));
	SpriteManager::MakeNewToTransparentInSheet(regularBPool, 0, 0, 48, 47, RGB(255, 255, 255), TEXT("effect_016_bloodpool_regular/1"));
	SpriteManager::MakeNewToTransparentInSheet(regularBPool, 48, 0, 48, 47, RGB(255, 255, 255), TEXT("effect_016_bloodpool_regular/2"));
	SpriteManager::MakeNewToTransparentInSheet(regularBPool, 0, 47, 48, 47, RGB(255, 255, 255), TEXT("effect_016_bloodpool_regular/3"));
	SpriteManager::MakeNewToTransparentInSheet(regularBPool, 48, 47, 48, 47, RGB(255, 255, 255), TEXT("effect_016_bloodpool_regular/4"));
	SpriteManager::MakeNewToTransparentInSheet(regularBPool, 0, 94, 48, 47, RGB(255, 255, 255), TEXT("effect_016_bloodpool_regular/5"));
	SpriteManager::MakeNewToTransparentInSheet(regularBPool, 48, 94, 48, 47, RGB(255, 255, 255), TEXT("effect_016_bloodpool_regular/6"));

	HDCEx* largeBPool = BitmapManager::Load(TEXT("../Image/Effect/effect_016_bloodpool_large.bmp"), TEXT("Effect/effect_016_bloodpool_large"));
	SpriteManager::MakeNewToTransparentInSheet(largeBPool, 0, 0, 98, 96, RGB(255, 255, 255), TEXT("effect_016_bloodpool_large/1"));
	SpriteManager::MakeNewToTransparentInSheet(largeBPool, 98, 0, 98, 96, RGB(255, 255, 255), TEXT("effect_016_bloodpool_large/2"));
	SpriteManager::MakeNewToTransparentInSheet(largeBPool, 196, 0, 98, 96, RGB(255, 255, 255), TEXT("effect_016_bloodpool_large/3"));
	SpriteManager::MakeNewToTransparentInSheet(largeBPool, 0, 98, 98, 94, RGB(255, 255, 255), TEXT("effect_016_bloodpool_large/4"));
	SpriteManager::MakeNewToTransparentInSheet(largeBPool, 98, 98, 98, 94, RGB(255, 255, 255), TEXT("effect_016_bloodpool_large/5"));
	SpriteManager::MakeNewToTransparentInSheet(largeBPool, 196, 98, 98, 94, RGB(255, 255, 255), TEXT("effect_016_bloodpool_large/6"));
}

void ResourceLoader::LoadSmallFlyResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Monster/monster_010_eternalfly.bmp"), TEXT("Monster/monster_010_eternalfly"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 32, 32, RGB(255, 255, 255), TEXT("monster_010_eternalfly/black01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 0, 32, 32, RGB(255, 255, 255), TEXT("monster_010_eternalfly/black02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 32, 32, 32, RGB(255, 255, 255), TEXT("monster_010_eternalfly/red01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 32, 32, 32, RGB(255, 255, 255), TEXT("monster_010_eternalfly/red02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 64, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 64, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 64, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead03"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 64, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead04"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 128, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead05"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 128, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead06"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 128, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead07"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 128, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead08"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 192, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead09"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 192, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead10"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 128, 192, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead11"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 192, 192, 64, 64, RGB(255, 255, 255), TEXT("monster_010_eternalfly/dead012"));
}

void ResourceLoader::LoadGaperHeadResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Monster/monster_017_gaper.bmp"), TEXT("Monster/monster_017_gaper"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 32, 32, RGB(255, 0, 0), TEXT("monster_017_gaper/close_01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 32, 32, 32, RGB(255, 0, 0), TEXT("monster_017_gaper/close_02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 0, 32, 32, RGB(255, 0, 0), TEXT("monster_017_gaper/open_01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 32, 32, 32, RGB(255, 0, 0), TEXT("monster_017_gaper/open_02"));
}

void ResourceLoader::LoadMuliboomHeadResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Monster/monster_061_muliboom.bmp"), TEXT("Monster/monster_061_muliboom"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 48, 50, RGB(255, 0, 0), TEXT("monster_061_muliboom/01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 48, 0, 48, 50, RGB(255, 0, 0), TEXT("monster_061_muliboom/02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 0, 48, 50, RGB(255, 0, 0), TEXT("monster_061_muliboom/03"));
}

void ResourceLoader::LoadBabyMonsterResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Monster/monster_155_baby_champion.bmp"), TEXT("Monster/monster_155_baby_champion"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 32, 32, RGB(255, 0, 0), TEXT("monster_155_baby_champion/default"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 32, 32, 32, RGB(255, 0, 0), TEXT("monster_155_baby_champion/scream"));
}

void ResourceLoader::LoadBabyPlumBossResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Monster/boss_baby_plum.bmp"), TEXT("Monster/boss_baby_plum"));

	auto left = [](const size_t& x) -> float { return 64 * (float)x; };
	auto top = [](const size_t& y) -> float { return 64 * (float)y; };

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(0), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/idle01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(1), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/idle02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(0), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin00"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(1), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(2), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(3), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin03"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin04"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(5), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin05"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(0), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin06"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(1), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin07"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(2), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin08"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(3), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin09"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/spin10"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(0), top(6), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/reflect_wait01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(1), top(6), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/reflect_wait02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(6), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/reflect_up01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(5), top(6), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/reflect_up02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(6), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/reflect_down01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(6), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/reflect_down02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(5), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/stamp_wait01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/stamp_wait02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(5), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/stamp_stamp"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(3), top(0), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/landing01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(0), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/landing02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(0), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/hello01_01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(0), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/hello01_02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(1), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/hello02_01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(1), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/hello02_02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/hold01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/hold02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/flyaway01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(7), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/flyaway02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(1), top(1), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake_sit"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(0), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(1), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(2), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake03"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(3), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake04"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake05"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(5), top(2), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake06"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(0), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake07"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(1), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake08"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(2), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake09"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(3), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake10"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(4), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake11"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(5), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake12"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(3), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/awake13"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, left(6), top(4), 64, 64, RGB(255, 0, 0), TEXT("boss_baby_plum/crying"));
}

void ResourceLoader::LoadBlueBabayBossResources()
{
	HDCEx* bmp1 = BitmapManager::Load(TEXT("../Image/Monster/boss_078_bluebaby_01.bmp"), TEXT("Monster/boss_078_bluebaby_01"));
	HDCEx* bmp2 = BitmapManager::Load(TEXT("../Image/Monster/boss_078_bluebaby_02.bmp"), TEXT("Monster/boss_078_bluebaby_02"));
	HDCEx* bmp3 = BitmapManager::Load(TEXT("../Image/Monster/boss_078_bluebaby_03.bmp"), TEXT("Monster/boss_078_bluebaby_03"));

	SpriteManager::MakeNewToTransparentInSheet(bmp1, 0, 0, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_01/stand"));
	SpriteManager::MakeNewToTransparentInSheet(bmp1, 64, 0, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_01/stand_white"));
	SpriteManager::MakeNewToTransparentInSheet(bmp1, 64, 64, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_01/crouch"));
	SpriteManager::MakeNewToTransparentInSheet(bmp1, 192, 64, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_01/lie"));
	SpriteManager::MakeNewToTransparentInSheet(bmp1, 0, 128, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_01/wing_hide"));

	SpriteManager::MakeNewToTransparentInSheet(bmp2, 0, 0, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing1"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 64, 0, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing2"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 128, 0, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing3"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 192, 0, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing4"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 0, 64, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing5"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 64, 64, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing6"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 128, 64, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing7"));
	SpriteManager::MakeNewToTransparentInSheet(bmp2, 192, 64, 64, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_02/wing8"));

	SpriteManager::MakeNewToTransparentInSheet(bmp3, 0, 0, 80, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_03/unfold1"));
	SpriteManager::MakeNewToTransparentInSheet(bmp3, 80, 0, 80, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_03/unfold2"));
	SpriteManager::MakeNewToTransparentInSheet(bmp3, 160, 0, 80, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_03/unfold3"));
	SpriteManager::MakeNewToTransparentInSheet(bmp3, 0, 64, 80, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_03/unfold_white1"));
	SpriteManager::MakeNewToTransparentInSheet(bmp3, 80, 64, 80, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_03/unfold_white2"));
	SpriteManager::MakeNewToTransparentInSheet(bmp3, 160, 64, 80, 64, RGB(255, 0, 0), TEXT("boss_078_bluebaby_03/unfold_white3"));
}

void ResourceLoader::LoadBloodPoofResources()
{
	HDCEx* smallBmp = BitmapManager::Load(TEXT("../Image/Effect/effect_002_bloodpoof_small.bmp"), TEXT("Effect/effect_002_bloodpoof_small"));

	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 0, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/01"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 32, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/02"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 64, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/03"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 96, 0, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/04"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 0, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/05"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 32, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/06"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 64, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/07"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 96, 32, 32, 32, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_small/08"));

	HDCEx* regularBmp = BitmapManager::Load(TEXT("../Image/Effect/effect_002_bloodpoof_regular.bmp"), TEXT("Effect/effect_002_bloodpoof_regular"));

	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 0, 0, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/01"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 80, 0, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/02"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 160, 0, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/03"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 240, 0, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/04"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 0, 80, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/05"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 80, 80, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/06"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 160, 80, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/07"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 240, 80, 80, 80, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_regular/08"));

	HDCEx* largeBmp = BitmapManager::Load(TEXT("../Image/Effect/effect_002_bloodpoof_large.bmp"), TEXT("Effect/effect_002_bloodpoof_large"));

	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 0, 0, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/01"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 120, 0, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/02"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 240, 0, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/03"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 360, 0, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/04"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 0, 120, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/05"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 120, 120, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/06"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 240, 120, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/07"));
	SpriteManager::MakeNewToTransparentInSheet(regularBmp, 360, 120, 120, 120, RGB(255, 255, 255), TEXT("effect_002_bloodpoof_large/08"));
}

void ResourceLoader::LoadPoofResources()
{
	HDCEx* smallBmp = BitmapManager::Load(TEXT("../Image/Effect/effect_009_poof01_small.bmp"), TEXT("Effect/effect_009_poof01_small"));

	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 0, 0, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/01"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 48, 0, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/02"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 96, 0, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/03"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 144, 0, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/04"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 192, 0, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/05"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 0, 49, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/06"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 48, 49, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/07"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 96, 49, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/08"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 144, 49, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/09"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 192, 49, 48, 43, RGB(255, 255, 255), TEXT("effect_009_poof01_small/10"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 0, 99, 48, 39, RGB(255, 255, 255), TEXT("effect_009_poof01_small/11"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 48, 99, 48, 39, RGB(255, 255, 255), TEXT("effect_009_poof01_small/12"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 96, 99, 48, 39, RGB(255, 255, 255), TEXT("effect_009_poof01_small/13"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 144, 99, 48, 39, RGB(255, 255, 255), TEXT("effect_009_poof01_small/14"));
	SpriteManager::MakeNewToTransparentInSheet(smallBmp, 192, 99, 48, 39, RGB(255, 255, 255), TEXT("effect_009_poof01_small/15"));
}

void ResourceLoader::LoadObstacleResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Grid/rocks_basement.bmp"), TEXT("Grid/rocks_basement"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 0, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/brown01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 0, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/brown02"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 0, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/brown03"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 0, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/brown_destroyed"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 32, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/iron"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 32, 32, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/blue"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 32, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/bowl_black01"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 32, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/blue_destroyed"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 0, 64, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/brown_bomb"));
	SpriteManager::MakeNewToTransparentInSheet(bmp, 64, 64, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/bowl_black02"));

	SpriteManager::MakeNewToTransparentInSheet(bmp, 96, 96, 32, 32, RGB(255, 255, 255), TEXT("rocks_basement/bowl_white01"));
}

void ResourceLoader::LoadItemResources()
{
	HDCEx* itemTable = BitmapManager::Load(TEXT("../Image/Item/itemtable.bmp"), TEXT("Item/itemtable"));
	
	SpriteManager::MakeToTransparent(itemTable, RGB(255, 255, 255), TEXT("itemtable"));

	HDCEx* chest = BitmapManager::Load(TEXT("../Image/Item/pickup_005_chests.bmp"), TEXT("Item/pickup_005_chests"));

	SpriteManager::MakeNewToTransparentInSheet(chest, 0, 0, 30, 23, RGB(255, 0, 0), TEXT("pickup_005_chests/normal_closed"));
	SpriteManager::MakeNewToTransparentInSheet(chest, 30, 0, 28, 23, RGB(255, 0, 0), TEXT("pickup_005_chests/normal_open"));
	SpriteManager::MakeNewToTransparentInSheet(chest, 0, 23, 30, 23, RGB(255, 0, 0), TEXT("pickup_005_chests/gold_closed"));
	SpriteManager::MakeNewToTransparentInSheet(chest, 30, 23, 28, 23, RGB(255, 0, 0), TEXT("pickup_005_chests/gold_open"));

	HDCEx* heart = BitmapManager::Load(TEXT("../Image/Item/pickup_001_heart.bmp"), TEXT("Item/pickup_001_heart"));

	SpriteManager::MakeNewToTransparentInSheet(heart, 0, 0, 32, 32, RGB(255, 0, 0), TEXT("redheart_full"));
	SpriteManager::MakeNewToTransparentInSheet(heart, 32, 0, 32, 32, RGB(255, 0, 0), TEXT("redheart_half"));
	SpriteManager::MakeNewToTransparentInSheet(heart, 0, 32, 32, 32, RGB(255, 0, 0), TEXT("blueheart_full"));
	SpriteManager::MakeNewToTransparentInSheet(heart, 32, 32, 32, 32, RGB(255, 0, 0), TEXT("blueheart_half"));

	HDCEx* yelCoin = BitmapManager::Load(TEXT("../Image/Item/pickup_002_coin.bmp"), TEXT("Item/pickup_002_coin"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 0, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/01"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 18, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/02"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 0, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/03"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 18, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/04"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 0, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/05"));
	SpriteManager::MakeNewToTransparentInSheet(yelCoin, 18, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coin/06"));

	HDCEx* blkCoin = BitmapManager::Load(TEXT("../Image/Item/pickup_002_coinblack.bmp"), TEXT("Item/pickup_002_coinblack"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 0, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/01"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 18, 0, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/02"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 0, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/03"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 18, 12, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/04"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 0, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/05"));
	SpriteManager::MakeNewToTransparentInSheet(blkCoin, 18, 24, 18, 12, RGB(255, 0, 0), TEXT("pickup_002_coinblack/06"));

	// SpriteManager::MakeNewToTransparentInSheet(bmp, 104, 166, 17, 24, RGB(255, 255, 255), MakeSpriteKey(bmpName, TEXT("pickup_003_charged_key")));

	// SpriteManager::MakeNewToTransparentInSheet(bombBmp, 0, 0, 32, 32, RGB(255, 0, 0), TEXT("pickup_016_bomb/default"));

	SpriteManager::MakeToTransparent(
		BitmapManager::Load(TEXT("../Image/Item/collectibles_001_thesadonion.bmp"), TEXT("Item/collectibles_001_thesadonion")), 
		RGB(255, 0, 0), TEXT("collectibles_001_thesadonion"));
	SpriteManager::MakeToTransparent(
		BitmapManager::Load(TEXT("../Image/Item/collectibles_007_bloodofthemartyr.bmp"), TEXT("Item/collectibles_007_bloodofthemartyr")),
		RGB(255, 0, 0), TEXT("collectibles_007_bloodofthemartyr")
	);
	SpriteManager::MakeToTransparent(
		BitmapManager::Load(TEXT("../Image/Item/collectibles_015_heart.bmp"), TEXT("Item/collectibles_015_heart")),
		RGB(255, 255, 255), TEXT("collectibles_015_heart")
	);
	SpriteManager::MakeToTransparent(
		BitmapManager::Load(TEXT("../Image/Item/collectibles_030_momsheels.bmp"), TEXT("Item/collectibles_030_momsheels")),
		RGB(255, 0, 0), TEXT("collectibles_030_momsheels")
	);
	SpriteManager::MakeToTransparent(
		BitmapManager::Load(TEXT("../Image/Item/collectibles_031_momslipstick.bmp"), TEXT("Item/collectibles_031_momslipstick")),
		RGB(255, 0, 0), TEXT("collectibles_031_momslipstick")
	);
	SpriteManager::MakeToTransparent(
		BitmapManager::Load(TEXT("../Image/Item/collectibles_118_brimstone.bmp"), TEXT("Item/collectibles_118_brimstone")),
		RGB(255, 0, 0), TEXT("collectibles_118_brimstone")
	);
}

void ResourceLoader::LoadUIResources()
{
	HDCEx* bossHealthBmp = BitmapManager::Load(TEXT("../Image/UI/ui_bosshealthbar.bmp"), TEXT("UI/ui_bosshealthbar"));

	SpriteManager::MakeNewToTransparentInSheet(bossHealthBmp, 0, 0, 19, 18, RGB(255, 255, 255), TEXT("ui_bosshealthbar/skull"));
	SpriteManager::MakeNewToTransparentInSheet(bossHealthBmp, 0, 18, 116, 8, RGB(255, 255, 255), TEXT("ui_bosshealthbar/hp"));
	SpriteManager::MakeNewToTransparentInSheet(bossHealthBmp, 0, 26, 121, 12, RGB(255, 255, 255), TEXT("ui_bosshealthbar/bar"));

	HDCEx* heartBmp = BitmapManager::Load(TEXT("../Image/UI/ui_hearts.bmp"), TEXT("UI/ui_hearts"));

	SpriteManager::MakeNewToTransparentInSheet(heartBmp, 0, 0, 16, 16, RGB(255, 0, 0), TEXT("ui_hearts/red_full"));
	SpriteManager::MakeNewToTransparentInSheet(heartBmp, 16, 0, 16, 16, RGB(255, 0, 0), TEXT("ui_hearts/red_half"));
	SpriteManager::MakeNewToTransparentInSheet(heartBmp, 32, 0, 16, 16, RGB(255, 0, 0), TEXT("ui_hearts/red_empty"));

	SpriteManager::MakeNewToTransparentInSheet(heartBmp, 0, 16, 16, 16, RGB(255, 0, 0), TEXT("ui_hearts/blue_full"));
	SpriteManager::MakeNewToTransparentInSheet(heartBmp, 16, 16, 16, 16, RGB(255, 0, 0), TEXT("ui_hearts/blue_half"));
}

void ResourceLoader::LoadIsaacFontResources()
{
	FontManager::AddFont(TEXT("../Font/Upheaval.fon"));
}

void ResourceLoader::LoadStartRoomResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Effect/controls.bmp"), TEXT("Effect/controls"));
	
	SpriteManager::MakeToTransparent(bmp, RGB(255, 255, 255), TEXT("controls"));
}

void ResourceLoader::LoadTestResources()
{
	HDCEx* bmp = BitmapManager::Load(TEXT("../Image/Test/Test.bmp"), TEXT("Test/Test"));

	SpriteManager::Make(bmp, TEXT("Test"));
}

void ResourceLoader::Release()
{
	BitmapManager::Clear();
	SpriteManager::Clear();
	FontManager::Clear();
}
