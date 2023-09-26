#include "BaseStdafx.h"
#include "Body2D.h"
#include "Transform.h"
#include "Collider2D.h"
#include "ExecutionOrder.h"

void Body2D::Awake()
{
	SetExecutionOrder(EX_ORDER_BODY2D);

	m_isBody2D = true;

	m_velcoity = Vector2::zero();
	m_mass = 1;
	m_invMass = 1;
	m_elasticity = 0.5f;
	m_friction = 7.0f;

	m_justCollider = false;
	
	g_bodies.push_back(this);
}

void Body2D::Start()
{
}

void Body2D::Update()
{
}

void Body2D::LateUpdate()
{
}

void Body2D::OnEnable()
{
}

void Body2D::OnDisable()
{

}

void Body2D::OnDestroy()
{
	// 모든 콜라이더 참조 해제
	while (m_colliders.size() > 0)
		DeregisterCollider(m_colliders.back());

	// 리스트에서 해당 Body2D 삭제
	auto it = std::find(g_bodies.begin(), g_bodies.end(), this);
	g_bodies.erase(it);
}

void Body2D::ApplyVelocity()
{
	const float& dt = (*BaseGlobal::pDeltaTime);

	const Vector2& pos = transform()->position();
	Vector2 newPos = pos + m_velcoity * dt;
	transform()->setPosition(newPos);
	UpdateColliderVertices();

	m_velcoity -= m_velcoity * m_friction * dt;
}

void Body2D::UpdateColliderVertices()
{
	for (auto& collider : m_colliders)
	{
		collider->UpdateShapeVertices();
	}
}

const Vector2& Body2D::velocity() const
{
	return m_velcoity;
}

void Body2D::setVelocity(const Vector2& velocity)
{
	m_velcoity = velocity;
}

float Body2D::mass() const
{
	if (m_justCollider) return 0;
	return m_mass;
}

void Body2D::setMass(const float& mass)
{
	m_mass = mass;
	if (mass == 0) m_invMass = 0;
	else m_invMass = 1.0f / mass;
}

float Body2D::invMass() const
{
	if (m_justCollider) return 0;
	return m_invMass;
}

const float& Body2D::elasticity() const
{
	return m_elasticity;
}

void Body2D::setElasticity(const float& elasticity)
{
	m_elasticity = elasticity;
}

const float& Body2D::friction() const
{
	return m_friction;
}

void Body2D::setFriction(const float& friction)
{
	m_friction = friction;
}

const bool& Body2D::justCollider() const
{
	return m_justCollider;
}

void Body2D::setJustCollider(const bool& enable)
{
	m_justCollider = enable;
}

size_t Body2D::colliderCount() const
{
	return m_colliders.size();
}

Collider2D* Body2D::collider2D(const size_t& index) const
{
	return m_colliders[index];
}

void Body2D::RegisterCollider(Collider2D* collider)
{
	if (!collider) return;
	m_colliders.push_back(collider);
	collider->m_body2D = this;
	collider->OnDestroyCallback += Function<void, Object*>(this, &Body2D::OnRegisteredColliderDestroy);
}

void Body2D::DeregisterCollider(Collider2D* collider)
{
	if (!collider) return;
	auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
	m_colliders.erase(it);
	collider->m_body2D = nullptr;
	collider->OnDestroyCallback -= Function<void, Object*>(this, &Body2D::OnRegisteredColliderDestroy);
}
bool Body2D::HasCollider(Collider2D* collider) const
{
	auto it = std::find(m_colliders.begin(), m_colliders.end(), collider);
	return (it != m_colliders.end());
}
void Body2D::AddImpulseToSpeed(const Vector2& direction, const float& speed)
{
	const float& dt = (*BaseGlobal::pDeltaTime);
	m_velcoity = m_velcoity + direction * speed * m_friction * dt;
}

void Body2D::AddImpulse(const Vector2& impulse)
{
	m_velcoity += impulse * m_invMass;
}

void Body2D::OnRegisteredColliderDestroy(Object* obj)
{
	DeregisterCollider(static_cast<Collider2D*>(obj));
}

std::vector<Body2D*> Body2D::g_bodies;