#include "BaseStdafx.h"
#include "LineCollider2D.h"
#include "Line2D.h"

void LineCollider2D::SetShape2DOnAwake(Shape2D** pColliderShape2D)
{
	*pColliderShape2D = new Line2D(Vector2::right(), 1.0f);
}

Line2D* LineCollider2D::line() const
{
	return static_cast<Line2D*>(shape2D());
}
