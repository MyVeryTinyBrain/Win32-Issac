#pragma once
#ifndef __FontManager_h__
#define __FontManager_h__

class FontManager
{
	std::vector<const TCHAR*> m_fonts;

public:
	static FontManager* instance();

private:
	static FontManager g_instance;

private:
	FontManager();
	~FontManager();

public:
	static void Clear();
	static void AddFont(const TCHAR* fontPath);
};

#endif
