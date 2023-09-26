#pragma once
#ifndef __RectCollider2D_h__
#define __RectCollider2D_h__

#include "Collider2D.h"

class Rect2D;

class RectCollider2D : public Collider2D
{
	virtual void SetShape2DOnAwake(Shape2D** pColliderShape2D) override;

public:
	Rect2D* rect() const;
};

#endif
