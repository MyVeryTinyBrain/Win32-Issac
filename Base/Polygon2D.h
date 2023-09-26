#pragma once
#ifndef __Polygon2D_h__
#define __Polygon2D_h__

#include "Shape2D.h"

class Polygon2D : public Shape2D
{
	virtual void UpdateShape() override;

private:
	float m_begAngle; // Radian

public:
	Polygon2D(const size_t& vertexCount, const float& radius, const float& begAngle);
	Polygon2D(const size_t& vertexCount, const float& radius);
	virtual ~Polygon2D();

	void setVertexCount(const size_t& vertexCount);
};

#endif
