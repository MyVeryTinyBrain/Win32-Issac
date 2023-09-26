#pragma once
#ifndef __Circle2D_h__
#define __Circle2D_h__

#include "Shape2D.h"

class Circle2D : public Shape2D
{
	virtual void UpdateShape() override;

private:
	float m_scaledRadius;

public:
	Circle2D(const float& radius);
	virtual ~Circle2D();

	const float& scaledRadius() const;
};

#endif
