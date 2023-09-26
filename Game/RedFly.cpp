#include "stdafx.h"
#include "RedFly.h"
#include "RedFlyAnimator.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "Projectile.h"
#include "Define.h"
#include "Pool.h"

void RedFly::setSize(Size* pSize)
{
	*pSize = Size::Small;
}

void RedFly::setInitHP(float* pHP)
{
	*pHP = 3;
}

void RedFly::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
{
	//GameObject* colObj = new GameObject();
	//colObj->setLayer(GO_LAYER_ENEMY);
	//CircleCollider2D* col = colObj->AddComponent<CircleCollider2D>();
	//col->circle()->setRadius(5);
	//colObj->AddComponent<Collider2DRenderer>();

	GameObject* hitObj = new GameObject();
	hitObj->transform()->setLocalPosition({});
	hitObj->setLayer(GO_LAYER_ENEMY);
	CircleCollider2D* hit = hitObj->AddComponent<CircleCollider2D>();
	hit->circle()->setRadius(5);
	hit->setIsTrigger(true);
	hitObj->AddComponent<Collider2DRenderer>();

	//*pCollider = col;
	*pHitTrigger = hit;
}

void RedFly::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
	m_spriteObj = new GameObject(this->transform());
	m_spriteObj->transform()->setLocalPosition({});

	m_spriteObj->transform()->setLocalPosition({});
	SpriteRenderer* sr = m_spriteObj->AddComponent<SpriteRenderer>();
	sr->setRenderTag(RD_TAG_FLYING_OBJ);
	sr->setRenderOrder(RD_ORDER_FLYING_OBJ_FLY);
	sr->setYOrder(true);

	m_animator = m_spriteObj->AddComponent<RedFlyAnimator>();
	m_animator->OnDeadAnimated += Function<void>(this, &RedFly::OnDeadAnimated);

	pRenderers->push_back(sr);
}

void RedFly::LateAwake()
{
	m_speed = 38.0f + (float)(rand() % 21);

	m_hitTrigger->transform()->setParent(this->transform());
	m_hitTrigger->transform()->setLocalPosition({});

	m_shadowObj = new GameObject(this->transform());
	m_shadowObj->transform()->setLocalPosition({ 0,-FLYING_HEIGHT });
	SpriteRenderer* shadowRenderer = m_shadowObj->AddComponent<SpriteRenderer>();
	shadowRenderer->setSprite(SpriteManager::Find(TEXT("shadow")));
	shadowRenderer->setRenderTag(RD_TAG_SHADOW);
	shadowRenderer->setFixedSize(false);
	shadowRenderer->setOriginSizeWhenDefixedSize(false);
	shadowRenderer->setAlphaMode(true);
	shadowRenderer->setAlpha(SHADOW_ALPHA);
	m_shadowObj->transform()->setSize({ 10,5 });

	m_body->setFriction(1.0f);

	m_shotTime = fmodf((float)rand() * 0.1f, 1.0f);
}

void RedFly::OnCollision(Collider2D* collider)
{
}

void RedFly::OnTrigger(Collider2D* collider)
{
}

void RedFly::OnDamaged()
{
}

void RedFly::OnDead()
{
	GameObject* poolObj = new GameObject(center());
	Pool* pool = poolObj->AddComponent<Pool>();
	pool->InitGenerate(Pool::Type::Blood, Pool::Size::Small);

	m_shadowObj->setEnable(false);
	m_animator->PlayDead();
}

Vector2 RedFly::center() const
{
	return transform()->position();
}

void RedFly::Update()
{
	Monster::Update();

	if (isDead())
		return;

	Vector2 relVec = Player::instance()->headPosition() - transform()->position();
	Vector2 dir = relVec.normalized();
	m_body->AddImpulseToSpeed(dir, m_speed);

	m_shotTime += Global::deltaTime;
	if (m_shotTime > 2.0f)
	{
		m_shotTime = fmodf((float)rand() * 0.1f, 1.0f);

		Vector2 relVec = Player::instance()->headPosition() - transform()->position();
		Vector2 dir = relVec.normalized();

		GameObject* projectilObj = new GameObject(transform()->position());
		Projectile* projectile = projectilObj->AddComponent<Projectile>();
		projectile->InitSetType(Projectile::Type::Blood);
		projectile->InitSetDamage(1);
		projectile->InitSetRange(100);
		projectile->InitSetSpeed(100);
		projectile->InitSetDirection(dir);
		projectile->InitSetTargetLayer(GO_LAYER_PLAYER);
	}
}

void RedFly::OnDeadAnimated()
{
	this->gameObject()->Destroy();
}
