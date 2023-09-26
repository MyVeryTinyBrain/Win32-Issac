#pragma once
#ifndef __Renderer_h__
#define __Renderer_h__

#include "Behavior.h"

class Camera2D;

class Renderer2D : public Behavior
{
	unsigned char m_renderTag = 0;
	int m_renderOrder = 0;
	// Ȱ��ȭ �Ǿ������� y���� ���� renderOrder�� �����մϴ�.
	// y���� ū ������Ʈ���� y���� ���� ������Ʈ ������ �׷����� �˴ϴ�.
	bool m_yOrder = false;
	// y�� ���Ŀ� ���Ǵ� y���� ������ ���Դϴ�.
	// �⺻���� 0�Դϴ�.
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
