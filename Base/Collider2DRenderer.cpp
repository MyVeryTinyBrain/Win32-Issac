#include "BaseStdafx.h"
#include "Collider2DRenderer.h"
#include "Collider2D.h"
#include "Shape2D.h"
#include "Camera2D.h"
#include "HDCEx.h"
#include "Transform.h"
#include "Circle2D.h"
#include "GameObject.h"
#include "Renderer2DTag.h"

void Collider2DRenderer::LateAwake()
{
    setRenderTag(RD_TAG_DEBUG);
    m_collider2D = gameObject()->GetComponent<Collider2D>();
}

void Collider2DRenderer::Render(Camera2D* cam)
{
    return;
    if (!m_collider2D) return;
    if (!m_collider2D->gameObject()->active() || !m_collider2D->enable()) return;
    Shape2D* shape = m_collider2D->shape2D();

    // If not update, It draw not adjusstment line when it was disabled
    m_collider2D->UpdateShapeVertices();

    HPEN oldHPen = NULL;
    if (m_collider2D->isTrigger())
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
        oldHPen = (HPEN)SelectObject(*cam->hDCEx(), hPen);
    }
    else
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
        oldHPen = (HPEN)SelectObject(*cam->hDCEx(), hPen);
    }
    HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldHBrush = (HBRUSH)SelectObject(*cam->hDCEx(), hBrush);

    if (shape->vertexCount() == 0)
    {
        Circle2D* circle = static_cast<Circle2D*>(shape);
        const Matrix3x3& worldToCamera = cam->worldToCameraMatrix();
        Vector2 center = worldToCamera * shape->worldPosition();
        const float& r = circle->scaledRadius();
        Ellipse(
            *cam->hDCEx(), 
            (int)(center.x - r),
            (int)(center.y - r),
            (int)(center.x + r),
            (int)(center.y + r)
        );
    }
    else
    {
        const Matrix3x3& worldToCamera = cam->worldToCameraMatrix();;
        for (size_t i = 0; i < shape->vertexCount(); ++i)
        {
            size_t next = i + 1;
            if (next == shape->vertexCount()) next = 0;
            Vector2 p1 = worldToCamera * shape->vertex(i);
            Vector2 p2 = worldToCamera * shape->vertex(next);
            MoveToEx(
                *cam->hDCEx(), 
                (int)p1.x,
                (int)p1.y,
                NULL
            );
            LineTo(
                *cam->hDCEx(), 
                (int)p2.x,
                (int)p2.y
            );
        }
    }

    DeleteObject(SelectObject(*cam->hDCEx(), oldHPen));
    DeleteObject(SelectObject(*cam->hDCEx(), oldHBrush));
}

Collider2D* Collider2DRenderer::collider2D() const
{
    return m_collider2D;
}

void Collider2DRenderer::setCollider2D(Collider2D* shape2D)
{
    m_collider2D = shape2D;
}
