#pragma once
#ifndef __SpriteManager_h__
#define __SpriteManager_h__

class Sprite;
class HDCEx;

class SpriteManager
{
	static SpriteManager g_instance;

public:
	static SpriteManager* instance();

private:
	std::map<TCHAR*, Sprite*> m_sprites;

private:
	SpriteManager();
	~SpriteManager();

public:
	static void Clear();
	static Sprite* Make(HDCEx* bitmap, const TCHAR* key);
	static Sprite* MakeToTransparent(HDCEx* bitmap, COLORREF transparentColor, const TCHAR* key);
	static Sprite* MakeNewInSheet(HDCEx* bitmap, float x, float y, float w, float h, const TCHAR* key);
	static Sprite* MakeNewToTransparentInSheet(HDCEx* bitmap, float x, float y, float w, float h, COLORREF transparentColor, const TCHAR* key);
	static Sprite* Find(const TCHAR* key);
};

#endif
