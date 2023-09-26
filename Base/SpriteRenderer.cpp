#include "BaseStdafx.h"
#include "SpriteRenderer.h"
#include "HDCEx.h"
#include "Sprite.h"
#include "Transform.h"
#include "Camera2D.h"

void SpriteRenderer::LateAwake()
{
	m_sprite = nullptr;
	m_fixedSize = true;
	m_originSizeWhenDefixedSize = true;
	m_fillMode = false;
	m_fillColor = RGB(255, 255, 255);
	m_alphaMode = false;
	m_alpha = 1;
}

void SpriteRenderer::Render(Camera2D* cam)
{
	if (m_sprite == nullptr)
		return;
	
	Vector2 worldPos = transform()->position();
	float worldAng = transform()->angle();
	Vector2 worldSz = transform()->size();

	// 화면상의 좌표로 변환한다.
	Vector2 winSpacePos = cam->worldToCameraMatrix() * worldPos;

	// 화면상의 각도로 변환한다.
	float winSpaceAng = worldAng - cam->transform()->angle();
	// 윈도우에선 반대로 회전하므로 음수를 곱한다.
	winSpaceAng *= -1;

	Vector2 size = transform()->size();

	float width = 0;
	float height = 0;
	if (m_fixedSize)
	{
		width = m_sprite->width();
		height = m_sprite->height();
		if (size.x < 0) width *= -1;
		if (size.y < 0) height *= -1;
	}
	else
	{
		if (m_originSizeWhenDefixedSize)
		{
			width = m_sprite->width() * size.x;
			height = m_sprite->height() * size.y;
		}
		else
		{
			width = size.x;
			height = size.y;
		}
	}
	if (!m_fillMode && !m_alphaMode)
		m_sprite->Blt(winSpacePos.x, winSpacePos.y, winSpaceAng, width, height, *cam->hDCEx());
	else if (m_fillMode && m_alphaMode) 
		m_sprite->AlpBlt(winSpacePos.x, winSpacePos.y, winSpaceAng, width, height, *cam->hDCEx(), m_fillColor, m_alpha);
	else if (m_fillMode) 
		m_sprite->Blt(winSpacePos.x, winSpacePos.y, winSpaceAng, width, height, *cam->hDCEx(), m_fillColor);
	else if (m_alphaMode) 
		m_sprite->AlpBlt(winSpacePos.x, winSpacePos.y, winSpaceAng, width, height, *cam->hDCEx(), m_alpha);
}

Sprite* SpriteRenderer::sprite() const
{
	return m_sprite;
}

void SpriteRenderer::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

const bool& SpriteRenderer::fixedSize() const
{
	return m_fixedSize;
}

void SpriteRenderer::setFixedSize(const bool& enable)
{
	m_fixedSize = enable;
}

const bool& SpriteRenderer::originSizeWhenDefixedSize() const
{
	return m_originSizeWhenDefixedSize;
}

void SpriteRenderer::setOriginSizeWhenDefixedSize(const bool& enable)
{
	m_originSizeWhenDefixedSize = enable;
}

const bool& SpriteRenderer::fillMode() const
{
	return m_fillMode;
}

void SpriteRenderer::setFillMode(const bool& enable)
{
	m_fillMode = enable;
}

const COLORREF& SpriteRenderer::fillColor() const
{
	return m_fillColor;
}

void SpriteRenderer::setFillColor(const COLORREF& color)
{
	m_fillColor = color;
}

const bool& SpriteRenderer::alphaMode() const
{
	return m_alphaMode;
}

void SpriteRenderer::setAlphaMode(const bool& AlphaMode)
{
	m_alphaMode = AlphaMode;
}

const float& SpriteRenderer::alpha() const
{
	return m_alpha;
}

void SpriteRenderer::setAlpha(const float& Alpha)
{
	m_alpha = Alpha;
}
