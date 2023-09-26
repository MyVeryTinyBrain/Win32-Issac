#include "BaseStdafx.h"
#include "BitmapManager.h"
#include "HDCEx.h"

BitmapManager BitmapManager::g_instance;

BitmapManager* BitmapManager::instance()
{
	return &g_instance;
}

BitmapManager::BitmapManager()
{
}

BitmapManager::~BitmapManager()
{
	Clear();
}

void BitmapManager::Clear()
{
	for (auto& pair : g_instance.m_bitmaps)
	{
		TCHAR* str = pair.first;
		BASE_SAFE_DELETE_ARR(str);
		BASE_SAFE_DELETE(pair.second);
	}
	g_instance.m_bitmaps.clear();
}

HDCEx* BitmapManager::Load(const TCHAR* bitmapPath, const TCHAR* key)
{
	HDCEx* find = Find(key);
	if (find)
		return find;
	HDCEx* hDCEx = new HDCEx(bitmapPath);

	size_t len = _tcslen(key);
	TCHAR* str = new TCHAR[len + 1]{};
	_tcscpy_s(str, len + 1, key);

	g_instance.m_bitmaps.emplace(str, hDCEx);
	return hDCEx;
}

HDCEx* BitmapManager::Find(const TCHAR* key)
{
	auto iter = std::find_if(g_instance.m_bitmaps.begin(), g_instance.m_bitmaps.end(),
		[&](auto& pair) -> bool
		{
			return !_tcscmp(pair.first, key);
		});
	if (iter == g_instance.m_bitmaps.end())
		return nullptr;
	else
		return iter->second;
}
