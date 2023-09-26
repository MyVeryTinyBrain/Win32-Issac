#include "BaseStdafx.h"
#include "PolygonCollider2D.h"
#include "Polygon2D.h"
#include "Transform.h"

void PolygonCollider2D::SetShape2DOnAwake(Shape2D** pColliderShape2D)
{
	*pColliderShape2D = new Polygon2D(6, 1, 0);
}

Polygon2D* PolygonCollider2D::polygon() const
{
	return static_cast<Polygon2D*>(shape2D());
}

void PolygonCollider2D::setPolygonVertexCount(const size_t& vertexCount)
{
	polygon()->setVertexCount(vertexCount);
	const Vector2& p = transform()->position();
	const float& a = transform()->angle();
	const Vector2& s = transform()->size();
	polygon()->setWorldTransform(p, a, s);
}
