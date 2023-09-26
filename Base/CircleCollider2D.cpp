#include "BaseStdafx.h"
#include "CircleCollider2D.h"
#include "Circle2D.h"

void CircleCollider2D::SetShape2DOnAwake(Shape2D** pColliderShape2D)
{
	*pColliderShape2D = new Circle2D(1);
}

Circle2D* CircleCollider2D::circle() const
{
	return static_cast<Circle2D*>(shape2D());
}
