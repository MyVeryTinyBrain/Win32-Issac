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
	// 활성화 되어있으면 Bitmap 크기 그대로 그립니다.
	// 트랜스폼의 스케일이 변경되어도 그리는 크기에 영향을 미치지 않습니다.
	// 반전 효과만 사용하게 됩니다.
	bool m_fixedSize = false;
	// fixedSize가 비활성화 상태일때 유효한 플래그입니다.
	// 활성화 되어있으면 이미지의 원래 크기에 월드스케일을 곱한 크기로 이미지를 그립니다.
	// 아니라면 월드스케일의 크기로 이미지를 그립니다.
	bool m_originSizeWhenDefixedSize = false;
	// 활성화 되어있으면 sprite의 배경색을 제외한 모든 부분을 fillColor색으로 곱연산하여 그립니다.
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
