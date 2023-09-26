#pragma once
#ifndef __Rect2D_h__
#define __Rect2D_h__

#include "Shape2D.h"

class Rect2D : public Shape2D
{
	virtual void UpdateShape() override;

private:
	float m_width;
	float m_height;

public:
	Rect2D(const float& width, const float& height);
	virtual ~Rect2D();

	const float& width() const;
	void setWidth(const float& Width);
	const float& height() const;
	void setHeight(const float& Height);
};

#endif
