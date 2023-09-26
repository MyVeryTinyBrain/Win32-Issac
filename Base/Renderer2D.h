#pragma once
#ifndef __Renderer_h__
#define __Renderer_h__

#include "Behavior.h"

class Camera2D;

class Renderer2D : public Behavior
{
	unsigned char m_renderTag = 0;
	int m_renderOrder = 0;
	// 활성화 되어있으면 y값에 따라 renderOrder를 조정합니다.
	// y값이 큰 오브젝트부터 y값이 작은 오브젝트 순으로 그려지게 됩니다.
	bool m_yOrder = false;
	// y값 정렬에 사용되는 y값에 더해질 값입니다.
	// 기본값은 0입니다.
	float m_yOrderAdjustment = 0;

public:
	virtual void LateAwake() = 0;
	virtual void Render(Camera2D* cam) = 0;

	const unsigned char& renderTag() const;
	void setRenderTag(unsigned char tag);
	const int& renderOrder() const;
	void setRenderOrder(int renderOrder);
	const bool& yOrder() const;
	void setYOrder(const bool& enable);
	const float& yOrderAdjustment() const;
	void setYOrderAdjustment(const float& yAdjustment);

protected:
	virtual void Awake() final override;
	virtual void Start() final override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() final override;
	virtual void OnDisable() final override;
	virtual void OnDestroy() override;
};

#endif
