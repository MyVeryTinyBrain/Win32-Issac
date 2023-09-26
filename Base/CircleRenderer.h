#pragma once
#ifndef __CircleRenderer_h__
#define __CircleRenderer_h__

#include "Renderer2D.h"

class CircleRenderer : public Renderer2D
{
	virtual void LateAwake() override;
	virtual void Render(Camera2D* cam) override;

private:
	float m_radius;

public:
	void setRadius(const float& radius);
	const float& radius() const;
};

#endif
