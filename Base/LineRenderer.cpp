#include "BaseStdafx.h"
#include "Camera2D.h"
#include "LineRenderer.h"
#include "HDCEx.h"
#include "Transform.h"

void LineRenderer::LateAwake()
{
    m_min = {};
    m_max = {};
}

void LineRenderer::Render(Camera2D* cam)
{
    if (m_localVertices.size() < 2 && m_worldVertices.size() < 2)
        return;

    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HPEN oldHPen = (HPEN)SelectObject(*cam->hDCEx(), hPen);

    const Matrix3x3& worldToCamera = cam->worldToCameraMatrix();
    const Matrix3x3& localToWorld = transform()->localToWorldMatrix();
    Vector2 prevVertexInCamera;

    if (m_localVertices.size() >= 2)
    {
        prevVertexInCamera = worldToCamera * localToWorld * m_localVertices[0];
        for (auto& vertex : m_localVertices)
        {
            Vector2 current = worldToCamera * localToWorld * vertex;
            MoveToEx(*cam->hDCEx(), (int)prevVertexInCamera.x, (int)prevVertexInCamera.y, NULL);
            LineTo(*cam->hDCEx(), (int)current.x, (int)current.y);
            prevVertexInCamera = current;
        }
    }

    if (m_worldVertices.size() >= 2)
    {
        prevVertexInCamera = worldToCamera * m_worldVertices[0];
        for (auto& vertex : m_worldVertices)
        {
            Vector2 current = worldToCamera * vertex;
            MoveToEx(*cam->hDCEx(), (int)prevVertexInCamera.x, (int)prevVertexInCamera.y, NULL);
            LineTo(*cam->hDCEx(), (int)current.x, (int)current.y);
            prevVertexInCamera = current;
        }
    }

    DeleteObject(SelectObject(*cam->hDCEx(), oldHPen));
}

void LineRenderer::addLocalVertex(const Vector2& localPosition)
{
    m_localVertices.push_back(localPosition * 0.5f);
    if (localPosition.x < m_min.x)  m_min.x = localPosition.x;
    if (localPosition.x > m_max.x)  m_max.x = localPosition.x;
    if (localPosition.y < m_min.y)  m_min.y = localPosition.y;
    if (localPosition.y > m_max.y)  m_max.y = localPosition.y;
}

void LineRenderer::addWorldVertex(const Vector2& worldPosition)
{
    m_worldVertices.push_back(worldPosition);
}

void LineRenderer::ClearLocalVertex()
{
    m_localVertices.clear();
}

void LineRenderer::ClearWorldVertex()
{
    m_worldVertices.clear();
}