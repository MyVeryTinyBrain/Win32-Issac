#pragma once
#ifndef __Collider2DRenderer_h__
#define __Collider2DRenderer_h__

#include "Renderer2D.h"

class Collider2D;

class Collider2DRenderer : public Renderer2D
{
	virtual void LateAwake() override;
	virtual void Render(Camera2D* cam) override;

private:
	Collider2D* m_collider2D = nullptr;

public:
	Collider2D* collider2D() const;
	void setCollider2D(Collider2D* shape2D);
};

#endif
