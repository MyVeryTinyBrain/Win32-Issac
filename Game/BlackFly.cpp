#include "stdafx.h"
#include "BlackFly.h"
#include "BlackFlyAnimator.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "Define.h"
#include "Pool.h"

void BlackFly::setSize(Size* pSize)
{
	*pSize = Size::Small;
}

void BlackFly::setInitHP(float* pHP)
{
	*pHP = 2;
}

void BlackFly::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
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

void BlackFly::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
	m_spriteObj = new GameObject(this->transform());
	m_spriteObj->transform()->setLocalPosition({});

	m_spriteObj->transform()->setLocalPosition({});
	SpriteRenderer* sr = m_spriteObj->AddComponent<SpriteRenderer>();
	sr->setRenderTag(RD_TAG_FLYING_OBJ);
	sr->setRenderOrder(RD_ORDER_FLYING_OBJ_FLY);
	sr->setYOrder(true);

	m_animator = m_spriteObj->AddComponent<BlackFlyAnimator>();
	m_animator->OnDeadAnimated += Function<void>(this, &BlackFly::OnDeadAnimated);

	pRenderers->push_back(sr);
}

void BlackFly::LateAwake()
{
	m_speed = 30.0f + (float)(rand() % 21);

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
}

void BlackFly::OnCollision(Collider2D* collider)
{
}

void BlackFly::OnTrigger(Collider2D* collider)
{
}

void BlackFly::OnDamaged()
{
}

void BlackFly::OnDead()
{
	GameObject* poolObj = new GameObject(center());
	Pool* pool = poolObj->AddComponent<Pool>();
	pool->InitGenerate(Pool::Type::Blood, Pool::Size::Small);

	m_shadowObj->setEnable(false);
	m_animator->PlayDead();
}

Vector2 BlackFly::center() const
{
	return transform()->position();
}

void BlackFly::Update()
{
	Monster::Update();

	if (isDead())
		return;

	Vector2 relVec = Player::instance()->headPosition() - transform()->position();
	Vector2 dir = relVec.normalized();
	m_body->AddImpulseToSpeed(dir, m_speed);
}

void BlackFly::OnDeadAnimated()
{
	this->gameObject()->Destroy();
}
