#pragma once
#ifndef __CircleCollider2D_h__
#define __CircleCollider2D_h__

#include "Collider2D.h"

class Circle2D;

class CircleCollider2D : public Collider2D
{
	virtual void SetShape2DOnAwake(Shape2D** pColliderShape2D) override;

public:
	Circle2D* circle() const;
};

#endif
