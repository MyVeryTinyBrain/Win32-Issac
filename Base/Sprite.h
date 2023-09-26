#pragma once
#ifndef __Sprite_h__
#define __Sprite_h__

class HDCEx;

class Sprite
{
	HDCEx* m_HDCEx;
	bool m_transparent;
	COLORREF m_transparentColor;

public:
	Sprite(HDCEx* hDCEx);
	Sprite(HDCEx* hDCEx, COLORREF transparentColor);
	Sprite(HDCEx* hDCEx, float sheetStartX, float sheetStartY, float sheetW, float sheetH);
	Sprite(HDCEx* hDCEx, float sheetStartX, float sheetStartY, float sheetW, float sheetH, COLORREF transparentColor);
	~Sprite();

	void Blt(float x, float y, HDC dest);
	void Blt(float x, float y, float angle, HDC dest);
	void Blt(float x, float y, float angle, float cx, float cy, HDC dest);
	void Blt(float x, float y, float angle, float cx, float cy, HDC dest, COLORREF fillColor);
	void AlpBlt(float x, float y, float angle, float cx, float cy, HDC dest, float alpha);
	void AlpBlt(float x, float y, float angle, float cx, float cy, HDC dest, COLORREF fillColor, float alpha);

	float width() const;
	float height() const;

	HDCEx* GetHDCEx() const;
};

#endif
