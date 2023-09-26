#pragma once
#ifndef __LineCollider2D_h__
#define __LineCollider2D_h__

#include "Collider2D.h"

class Line2D;

class LineCollider2D : public Collider2D
{
	virtual void SetShape2DOnAwake(Shape2D** pColliderShape2D) override;

public:
	Line2D* line() const;
};

#endif
