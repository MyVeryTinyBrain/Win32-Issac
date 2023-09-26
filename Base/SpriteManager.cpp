#include "BaseStdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "HDCEx.h"

SpriteManager SpriteManager::g_instance;

SpriteManager* SpriteManager::instance()
{
	return &g_instance;
}

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
	Clear();
}

void SpriteManager::Clear()
{
	for (auto& pair : g_instance.m_sprites)
	{
		TCHAR* str = pair.first;
		BASE_SAFE_DELETE_ARR(str);
		BASE_SAFE_DELETE(pair.second);
	}
	g_instance.m_sprites.clear();
}

Sprite* SpriteManager::Make(HDCEx* bitmap, const TCHAR* key)
{
	Sprite* find = Find(key);
	if (find)
		return find;
	Sprite* sprite = new Sprite(bitmap);

	size_t len = _tcslen(key);
	TCHAR* str = new TCHAR[len + 1]{};
	_tcscpy_s(str, len + 1, key);

	g_instance.m_sprites.emplace(str, sprite);
	return sprite;
}

Sprite* SpriteManager::MakeToTransparent(HDCEx* bitmap, COLORREF transparentColor, const TCHAR* key)
{
	Sprite* find = Find(key);
	if (find)
		return find;
	Sprite* sprite = new Sprite(bitmap, transparentColor);

	size_t len = _tcslen(key);
	TCHAR* str = new TCHAR[len + 1]{};
	_tcscpy_s(str, len + 1, key);

	g_instance.m_sprites.emplace(str, sprite);
	return sprite;
}

Sprite* SpriteManager::MakeNewInSheet(HDCEx* bitmap, float x, float y, float w, float h, const TCHAR* key)
{
	Sprite* find = Find(key);
	if (find)
		return find;
	Sprite* sprite = new Sprite(bitmap, x, y, w, h);

	size_t len = _tcslen(key);
	TCHAR* str = new TCHAR[len + 1]{};
	_tcscpy_s(str, len + 1, key);

	g_instance.m_sprites.emplace(str, sprite);
	return sprite;
}

Sprite* SpriteManager::MakeNewToTransparentInSheet(HDCEx* bitmap, float x, float y, float w, float h, COLORREF transparentColor, const TCHAR* key)
{
	Sprite* find = Find(key);
	if (find)
		return find;
	Sprite* sprite = new Sprite(bitmap, x, y, w, h, transparentColor);

	size_t len = _tcslen(key);
	TCHAR* str = new TCHAR[len + 1]{};
	_tcscpy_s(str, len + 1, key);

	g_instance.m_sprites.emplace(str, sprite);
	return sprite;
}

Sprite* SpriteManager::Find(const TCHAR* key)
{
	auto iter = std::find_if(g_instance.m_sprites.begin(), g_instance.m_sprites.end(),
		[&](auto& pair) -> bool
		{
			return !_tcscmp(pair.first, key);
		});
	if (iter == g_instance.m_sprites.end())
		return nullptr;
	else
		return iter->second;
}
