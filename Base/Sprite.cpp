#include "BaseStdafx.h"
#include "Sprite.h"
#include "HDCEx.h"

Sprite::Sprite(HDCEx* hDCEx)
{
	m_HDCEx = new HDCEx(hDCEx->bitmapInfo().bmWidth, hDCEx->bitmapInfo().bmHeight);
	hDCEx->BitBlt(*m_HDCEx, 0, 0);
	m_transparent = false;
	m_transparentColor = 0;
}

Sprite::Sprite(HDCEx* hDCEx, COLORREF transparentColor)
{
	m_HDCEx = new HDCEx(hDCEx->bitmapInfo().bmWidth, hDCEx->bitmapInfo().bmHeight);
	hDCEx->BitBlt(*m_HDCEx, 0, 0);
	m_transparent = true;
	m_transparentColor = transparentColor;
}

Sprite::Sprite(HDCEx* hDCEx, float sheetStartX, float sheetStartY, float sheetW, float sheetH)
{
	m_HDCEx = new HDCEx((int)sheetW, (int)sheetH);
	hDCEx->BitBlt(*m_HDCEx, 0, 0, (int)sheetStartX, (int)sheetStartY);
	m_transparent = false;
	m_transparentColor = 0;
}

Sprite::Sprite(HDCEx* hDCEx, float sheetStartX, float sheetStartY, float sheetW, float sheetH, COLORREF transparentColor)
{
	m_HDCEx = new HDCEx((int)sheetW, (int)sheetH);
	hDCEx->BitBlt(*m_HDCEx, 0, 0, (int)sheetStartX, (int)sheetStartY);
	m_transparent = true;
	m_transparentColor = transparentColor;
}

Sprite::~Sprite()
{
	BASE_SAFE_DELETE(m_HDCEx);
}

void Sprite::Blt(float x, float y, HDC dest)
{
	m_HDCEx->setUseBltToCenter(true);
	m_HDCEx->setUseRotate(false);
	if (m_transparent)
	{
		m_HDCEx->TrsBlt(dest, (int)x, (int)y, m_transparentColor);
	}
	else
	{
		m_HDCEx->BitBlt(dest, (int)x, (int)y);
	}
}

void Sprite::Blt(float x, float y, float angle, HDC dest)
{
	m_HDCEx->setUseBltToCenter(true);
	m_HDCEx->setUseRotate(true);
	m_HDCEx->setRotateAngle(angle);
	if (m_transparent)
	{
		m_HDCEx->TrsBlt(dest, (int)x, (int)y, m_transparentColor);
	}
	else
	{
		m_HDCEx->BitBlt(dest, (int)x, (int)y);
	}
}

void Sprite::Blt(float x, float y, float angle, float cx, float cy, HDC dest)
{
	m_HDCEx->setUseBltToCenter(true);
	m_HDCEx->setUseRotate(true);
	m_HDCEx->setRotateAngle(angle);
	if (m_transparent)
	{
		m_HDCEx->TrsBlt(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, m_transparentColor);
	}
	else
	{
		m_HDCEx->StrBlt(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy);
	}
}

void Sprite::Blt(float x, float y, float angle, float cx, float cy, HDC dest, COLORREF fillColor)
{
	m_HDCEx->setUseBltToCenter(true);
	m_HDCEx->setUseRotate(true);
	m_HDCEx->setRotateAngle(angle);

	if (m_transparent)
	{
		m_HDCEx->FillBlt(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, m_transparentColor, fillColor);
	}
	else
	{
		m_HDCEx->FillBlt(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, fillColor);
	}
}

void Sprite::AlpBlt(float x, float y, float angle, float cx, float cy, HDC dest, float alpha)
{
	m_HDCEx->setUseBltToCenter(true);
	m_HDCEx->setUseRotate(true);
	m_HDCEx->setRotateAngle(angle);

	if (m_transparent)
	{
		m_HDCEx->AlpBlt2(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, m_transparentColor, alpha);
	}
	else
	{
		m_HDCEx->AlpBlt1(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, alpha);
	}
}

void Sprite::AlpBlt(float x, float y, float angle, float cx, float cy, HDC dest, COLORREF fillColor, float alpha)
{
	m_HDCEx->setUseBltToCenter(true);
	m_HDCEx->setUseRotate(true);
	m_HDCEx->setRotateAngle(angle);

	if (m_transparent)
	{
		m_HDCEx->AlpBlt4(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, m_transparentColor, alpha, fillColor);
	}
	else
	{
		m_HDCEx->AlpBlt3(dest, (int)x, (int)y, 0, 0, (int)cx, (int)cy, alpha, fillColor);
	}
}

float Sprite::width() const
{
	return (float)m_HDCEx->bitmapInfo().bmWidth;
}

float Sprite::height() const
{
	return (float)m_HDCEx->bitmapInfo().bmHeight;
}

HDCEx* Sprite::GetHDCEx() const
{
	return m_HDCEx;
}
