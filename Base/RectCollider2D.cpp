#include "BaseStdafx.h"
#include "RectCollider2D.h"
#include "Rect2D.h"

void RectCollider2D::SetShape2DOnAwake(Shape2D** pColliderShape2D)
{
	*pColliderShape2D = new Rect2D(1, 1);
}

Rect2D* RectCollider2D::rect() const
{
	return static_cast<Rect2D*>(shape2D());
}
