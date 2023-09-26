#include "BaseStdafx.h"
#include "Circle2D.h"

void Circle2D::UpdateShape()
{
	float max = 0;
	if (fabsf(worldSize().x) > max) max = fabsf(worldSize().x);
	if (fabsf(worldSize().y) > max) max = fabsf(worldSize().y);
	m_scaledRadius = radius() * max;
}

Circle2D::Circle2D(const float& radius) :
	m_scaledRadius(radius),
	Shape2D(0, radius)
{
	UpdateShape();
}

Circle2D::~Circle2D()
{
}

const float& Circle2D::scaledRadius() const
{
	return m_scaledRadius;
}
