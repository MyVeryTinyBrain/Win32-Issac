#include "BaseStdafx.h"
#include "CircleRenderer.h"
#include "Camera2D.h"
#include "HDCEx.h"
#include "Transform.h"

void CircleRenderer::LateAwake()
{
	m_radius = 1;
}

void CircleRenderer::Render(Camera2D* cam)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN oldHPen = (HPEN)SelectObject(*cam->hDCEx(), hPen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldHBrush = (HBRUSH)SelectObject(*cam->hDCEx(), hBrush);

	const Matrix3x3& worldToCamera = cam->worldToCameraMatrix();
	Vector2 p = worldToCamera * transform()->position();
	float max = 0;
	if (fabsf(transform()->size().x) > max) max = fabsf(transform()->size().x);
	if (fabsf(transform()->size().y) > max) max = fabsf(transform()->size().y);
	float r = max * m_radius;
	Ellipse(
		*cam->hDCEx(), 
		(int)(p.x - r), 
		(int)(p.y - r),
		(int)(p.x + r),
		(int)(p.y + r)
	);

	DeleteObject(SelectObject(*cam->hDCEx(), oldHPen));
	DeleteObject(SelectObject(*cam->hDCEx(), oldHBrush));
}

void CircleRenderer::setRadius(const float& radius)
{
	m_radius = radius;
}

const float& CircleRenderer::radius() const
{
	return m_radius;
}
