#pragma once
#ifndef __TextRenderer_h__
#define __TextRenderer_h__

#include "Renderer2D.h"

enum class TextRendererAlignment
{
	LeftTop, CenterTop, RightTop,
	LeftMiddle, CenterMiddle, RightMiddle,
	LeftBottom, CenterBottom, RightBottom,
};

class TextRenderer : public Renderer2D
{
	virtual void LateAwake() override;
	virtual void Render(Camera2D* cam) override;
	virtual void OnDestroy() override;

private:
	bool m_fixedSize;

	size_t m_len;
	TCHAR* m_text;
	COLORREF m_color;
	float m_fontSize;
	float m_fontWidth; // 0 = auto (0~1000)
	TextRendererAlignment m_alignment;
	TCHAR* m_fontName; // NULL = auto

	float m_createdFontSizeX;
	float m_createdFontSizeY;
	float m_createFontAngle;
	float m_createdFontWidth;
	bool m_fontNameChanged;
	HFONT m_font;

public:
	const bool& fixedSize() const;
	void setFixedSize(const bool& enable);
	const size_t& length() const;
	void setText(const TCHAR* text);
	const TCHAR* text() const;
	void setColor(const COLORREF& Color);
	const COLORREF& color() const;
	void setFontSize(const float& FontSize);
	const float& fontSize() const;
	void setAlignment(const TextRendererAlignment& Alignment);
	const TextRendererAlignment& alignment() const;
	void setFontWidth(const float& Width);
	const float& fontWidth() const;
	void setFontName(const TCHAR* fontName);
	const TCHAR* fontName() const;

private:
	void CreateMyFont(const float& sizeX, const float& sizeY, const float& angle, const float& width);
	int CreateAlignmentNumber(const float& fontSizeY, Vector2* pAdjustment);
};

#endif
