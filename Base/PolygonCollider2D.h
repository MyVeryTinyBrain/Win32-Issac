#pragma once
#ifndef __PolygonCollider2D_h__
#define __PolygonCollider2D_h__

#include "Collider2D.h"

class Polygon2D;

class PolygonCollider2D : public Collider2D
{
	virtual void SetShape2DOnAwake(Shape2D** pColliderShape2D) override;

public:
	Polygon2D* polygon() const;
	void setPolygonVertexCount(const size_t& vertexCount);
};

#endif
