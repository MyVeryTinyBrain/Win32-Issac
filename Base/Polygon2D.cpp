#include "BaseStdafx.h"
#include "Polygon2D.h"

void Polygon2D::UpdateShape()
{
	Vector2* v = vertices();
    const size_t& n = vertexCount();
    const float& r = radius();
    const Vector2& p = worldPosition();
    const float& a = worldAngle();
    const Vector2& s = worldSize();
    Matrix3x3 TRS = Matrix3x3::TRS(p, a, s);
    for (size_t i = 0; i < n; ++i)
    {
        float percent = (-1) * (float)i / (float)n;
        float angle = percent * TAU + m_begAngle;
        Vector2 direction = Vector2::Direction(angle);
        Vector2 localPos = direction * r;
        v[i] = TRS * localPos;
    }
}

Polygon2D::Polygon2D(const size_t& vertexCount, const float& radius, const float& begAngle) :
    m_begAngle(begAngle),
    Shape2D(vertexCount, radius)
{
    UpdateShape();
}

Polygon2D::Polygon2D(const size_t& vertexCount, const float& radius) : Polygon2D(vertexCount, radius, 0)
{
}

Polygon2D::~Polygon2D()
{
}

void Polygon2D::setVertexCount(const size_t& vertexCount)
{
    BASE_SAFE_DELETE_ARR(m_vertices);
    m_vertexCount = vertexCount;
    m_vertices = new Vector2[vertexCount];
    UpdateShape();
}
