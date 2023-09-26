#pragma once
#ifndef __Line2D_h__
#define __Line2D_h__

#include "Shape2D.h"

class Line2D : public Shape2D
{
	virtual void UpdateShape() override;

private:
	Vector2 m_dir;
	float m_len;

public:
	Line2D(const Vector2& dir, const float& len);
	virtual ~Line2D();

	const Vector2& direction() const;
	void setDirection(const Vector2& Direction);
	const float& length() const;
	void setLength(const float& Length);
};

#endif
