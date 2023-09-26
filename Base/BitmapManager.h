#pragma once
#ifndef __BitmapManager_h__
#define __BitmapManager_h__

class HDCEx;

class BitmapManager
{
	static BitmapManager g_instance;

public:
	static BitmapManager* instance();

private:
	std::map<TCHAR*, HDCEx*> m_bitmaps;

private:
	BitmapManager();
	~BitmapManager();

public:
	static void Clear();
	static HDCEx* Load(const TCHAR* bitmapPath, const TCHAR* key);
	static HDCEx* Find(const TCHAR* key);
};

#endif
