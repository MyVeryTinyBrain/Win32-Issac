#include "BaseStdafx.h"
#include "FontManager.h"

FontManager FontManager::g_instance;

FontManager* FontManager::instance()
{
	return &g_instance;
}

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	Clear();
}

void FontManager::Clear()
{
	for (auto& fontPath : g_instance.m_fonts)
		RemoveFontResource(fontPath);
	g_instance.m_fonts.clear();
}

void FontManager::AddFont(const TCHAR* fontPath)
{
	auto it = std::find_if(g_instance.m_fonts.begin(), g_instance.m_fonts.end(),
		[&](const TCHAR* path) -> bool
		{
			return !_tcscmp(path, fontPath);
		});
	if (it != g_instance.m_fonts.end())
		return;

	size_t len = _tcslen(fontPath);
	TCHAR* str = new TCHAR[len + 1];
	_tcscpy_s(str, len + 1, fontPath);

	int result = AddFontResource(fontPath);

	if (result != 0)
		g_instance.m_fonts.push_back(str);
}
