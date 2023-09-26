#include "BaseStdafx.h"
#include "Line2D.h"

void Line2D::UpdateShape()
{
    Vector2* v = vertices();
    const size_t& n = vertexCount();
    const float& r = radius();
    const Vector2& p = worldPosition();
    const float& a = worldAngle();
    const Vector2& s = worldSize();
    Matrix3x3 TRS = Matrix3x3::TRS(p, a, s);
    v[0] = TRS * (m_dir * m_len * 0.5f * -1);
    v[1] = TRS * (m_dir * m_len * 0.5f);
}

Line2D::Line2D(const Vector2& dir, const float& len) : Shape2D(2, 0)
{
    m_dir = dir;
    m_len = len;

    UpdateShape();
}

Line2D::~Line2D()
{
}

const Vector2& Line2D::direction() const
{
    return m_dir;
}

void Line2D::setDirection(const Vector2& Direction)
{
    m_dir = Direction;
    UpdateShape();
}

const float& Line2D::length() const
{
    return m_len;
}

void Line2D::setLength(const float& Length)
{
    m_len = Length;
    UpdateShape();
}

