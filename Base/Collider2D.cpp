#include "BaseStdafx.h"
#include "Collider2D.h"
#include "Shape2D.h"
#include "Transform.h"
#include "Collider2D.h"
#include "ExecutionOrder.h"

void Collider2D::Awake()
{
    m_isCollider2D = true;

    m_isTrigger = false;
    m_body2D = nullptr;


    SetExecutionOrder(EX_ORDER_COLLIDER2D);
    SetShape2DOnAwake(&m_shape2D);

    UpdateShapeVertices();
}

void Collider2D::Start()
{
}

void Collider2D::Update()
{
}

void Collider2D::LateUpdate()
{
    UpdateShapeVertices();
}

void Collider2D::OnEnable()
{
}

void Collider2D::OnDisable()
{
}

void Collider2D::OnDestroy()
{
}

void Collider2D::UpdateShapeVertices()
{
    const Vector2& p = transform()->position();
    const float& a = transform()->angle();
    const Vector2& s = transform()->size();
    m_shape2D->setWorldTransform(p, a, s);
}

Shape2D* Collider2D::shape2D() const
{
    return m_shape2D;
}

const bool& Collider2D::isTrigger() const
{
    return m_isTrigger;
}

void Collider2D::setIsTrigger(const bool& IsTrigger)
{
    m_isTrigger = IsTrigger;
}

Body2D* Collider2D::body2D() const
{
    return m_body2D;
}
