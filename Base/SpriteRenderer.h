#pragma once
#ifndef __SpriteRenderer_h__
#define __SpriteRenderer_h__

#include "Renderer2D.h"

class Sprite;

class SpriteRenderer : public Renderer2D
{
	virtual void LateAwake() override;
	virtual void Render(Camera2D* cam) override;

private:
	Sprite* m_sprite = nullptr;
	// Ȱ��ȭ �Ǿ������� Bitmap ũ�� �״�� �׸��ϴ�.
	// Ʈ�������� �������� ����Ǿ �׸��� ũ�⿡ ������ ��ġ�� �ʽ��ϴ�.
	// ���� ȿ���� ����ϰ� �˴ϴ�.
	bool m_fixedSize = false;
	// fixedSize�� ��Ȱ��ȭ �����϶� ��ȿ�� �÷����Դϴ�.
	// Ȱ��ȭ �Ǿ������� �̹����� ���� ũ�⿡ ���彺������ ���� ũ��� �̹����� �׸��ϴ�.
	// �ƴ϶�� ���彺������ ũ��� �̹����� �׸��ϴ�.
	bool m_originSizeWhenDefixedSize = false;
	// Ȱ��ȭ �Ǿ������� sprite�� ������ ������ ��� �κ��� fillColor������ �������Ͽ� �׸��ϴ�.
	bool m_fillMode = false;
	COLORREF m_fillColor = 0;
	bool m_alphaMode = false;
	// 0~1
	float m_alpha;

public:
	Sprite* sprite() const;
	void setSprite(Sprite* sprite);
	const bool& fixedSize() const;
	void setFixedSize(const bool& enable);
	const bool& originSizeWhenDefixedSize() const;
	void setOriginSizeWhenDefixedSize(const bool& enable);
	const bool& fillMode() const;
	void setFillMode(const bool& enable);
	const COLORREF& fillColor() const;
	void setFillColor(const COLORREF& color);
	const bool& alphaMode() const;
	void setAlphaMode(const bool& AlphaMode);
	const float& alpha() const;
	void setAlpha(const float& Alpha);
};

#endif
