#include "BaseStdafx.h"
#include "Rect2D.h"

void Rect2D::UpdateShape()
{
	const Vector2& p = worldPosition();
	const float& a = worldAngle();
	const Vector2& s = worldSize();
	Matrix3x3 TRS = Matrix3x3::TRS(p, a, s);
	Vector2* v = vertices();
	v[0] = TRS * Vector2(-m_width, +m_height);
	v[1] = TRS * Vector2(+m_width, +m_height);
	v[2] = TRS * Vector2(+m_width, -m_height);
	v[3] = TRS * Vector2(-m_width, -m_height);
}

Rect2D::Rect2D(const float& width, const float& height) :
	m_width(width),
	m_height(height), 
	Shape2D(4, 0)
{
	UpdateShape();
}

Rect2D::~Rect2D()
{
}

const float& Rect2D::width() const
{
	return m_width;
}

void Rect2D::setWidth(const float& Width)
{
	m_width = Width;
	UpdateShape();
}

const float& Rect2D::height() const
{
	return m_height;
}

void Rect2D::setHeight(const float& Height)
{
	m_height = Height;
	UpdateShape();
}
