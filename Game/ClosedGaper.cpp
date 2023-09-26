#include "stdafx.h"
#include "ClosedGaper.h"
#include "MyGameObjectLayer.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "PlayerBodyAnimator.h"
#include "Player.h"
#include "RegularBloodPoofAnimator.h"
#include "Define.h"
#include "Pool.h"

void ClosedGaper::setSize(Size* pSize)
{
	*pSize = Size::Regular;
}

void ClosedGaper::setInitHP(float* pHP)
{
	*pHP = 7;
}

void ClosedGaper::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
{
	m_colObj = new GameObject(this->transform());
	m_colObj->transform()->setLocalPosition({});
	m_colObj->setLayer(GO_LAYER_ENEMY);
	CircleCollider2D* col = m_colObj->AddComponent<CircleCollider2D>();
	col->circle()->setRadius(10);
	m_colObj->AddComponent<Collider2DRenderer>();

	m_hitObj = new GameObject(this->transform());
	m_hitObj->transform()->setLocalPosition({ 0,10 });
	m_hitObj->setLayer(GO_LAYER_ENEMY);
	RectCollider2D* hit = m_hitObj->AddComponent<RectCollider2D>();
	hit->rect()->setWidth(15);
	hit->rect()->setHeight(15);
	m_hitObj->AddComponent<Collider2DRenderer>();

	*pCollider = col;
	*pHitTrigger = hit;
}

void ClosedGaper::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
	m_spriteParent = new GameObject(this->transform());
	m_spriteParent->transform()->setLocalPosition({});

	m_headObj = new GameObject(m_spriteParent->transform());
	m_headObj->transform()->setLocalPosition({ 0,16 });
	SpriteRenderer* headRenderer = m_headObj->AddComponent<SpriteRenderer>();
	headRenderer->setRenderTag(RD_TAG_OBJ);
	headRenderer->setRenderOrder(RD_ORDER_OBJ_HEAD);
	headRenderer->setSprite(SpriteManager::Find(TEXT("monster_017_gaper/close_01")));

	m_bodyObj = new GameObject(m_spriteParent->transform());
	m_bodyObj->transform()->setLocalPosition({});
	SpriteRenderer* bodyRenderer = m_bodyObj->AddComponent<SpriteRenderer>();
	bodyRenderer->setRenderTag(RD_TAG_OBJ);
	bodyRenderer->setRenderOrder(RD_ORDER_OBJ_BODY);
	m_bodyAnimator = m_bodyObj->AddComponent<PlayerBodyAnimator>();

	pRenderers->push_back(headRenderer);
	pRenderers->push_back(bodyRenderer);
}

void ClosedGaper::LateAwake()
{
	m_speed = 100;

	m_shadowObj = new GameObject(this->transform());
	m_shadowObj->transform()->setLocalPosition({ 0,-5 });
	SpriteRenderer* shadowRenderer = m_shadowObj->AddComponent<SpriteRenderer>();
	shadowRenderer->setSprite(SpriteManager::Find(TEXT("shadow")));
	shadowRenderer->setRenderTag(RD_TAG_SHADOW);
	shadowRenderer->setFixedSize(false);
	shadowRenderer->setOriginSizeWhenDefixedSize(false);
	shadowRenderer->setAlphaMode(true);
	shadowRenderer->setAlpha(SHADOW_ALPHA);
	m_shadowObj->transform()->setSize({ 20,10 });

	m_body->setFriction(2.0f);

}

void ClosedGaper::OnCollision(Collider2D* collider)
{
}

void ClosedGaper::OnTrigger(Collider2D* collider)
{
}

void ClosedGaper::OnDamaged()
{
}

void ClosedGaper::OnDead()
{
	GameObject* poolObj = new GameObject(center());
	Pool* pool = poolObj->AddComponent<Pool>();
	pool->InitGenerate(Pool::Type::Blood, Pool::Size::Regular);

	GameObject* bloodPoofObj = new GameObject(this->transform()->position());
	SpriteRenderer* bloodRenderer = bloodPoofObj->AddComponent<SpriteRenderer>();
	bloodRenderer->setRenderTag(RD_TAG_OBJ);
	bloodPoofObj->AddComponent<RegularBloodPoofAnimator>();

	gameObject()->Destroy();
}

Vector2 ClosedGaper::center() const
{
	return transform()->position() + Vector2(0, 10);
}

void ClosedGaper::Update()
{
	Monster::Update();

	Vector2 moveDir = m_body->velocity().normalized();
	float dotR = Vector2::Dot(moveDir, { 1,0 });
	float dotT = Vector2::Dot(moveDir, { 0,1 });
	float dotL = Vector2::Dot(moveDir, { -1,0 });
	float dotB = Vector2::Dot(moveDir, { 0,-1 });
	enum class DIR
	{
		LEFT, TOP, RIGHT, BOTTOM
	};
	DIR dir;
	float maxDot = 0;
	if (dotR >= maxDot)
	{
		dir = DIR::RIGHT;
		maxDot = dotR;
	}
	if (dotT >= maxDot)
	{
		dir = DIR::TOP;
		maxDot = dotT;
	}
	if (dotL >= maxDot)
	{
		dir = DIR::LEFT;
		maxDot = dotL;
	}
	if (dotB >= maxDot)
	{
		dir = DIR::BOTTOM;
		maxDot = dotB;
	}
	if (maxDot == 0)
	{
		dir = DIR::BOTTOM;
	}

	m_bodyAnimator->SetState(PlayerBodyAnimator::BodyState::IDLE);
	if (maxDot > 0)
	{
		if (dir == DIR::BOTTOM)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::FORWARD);
		}
		else if (dir == DIR::TOP)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::BACKWARD);
		}
		else if (dir == DIR::LEFT)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::LEFT);
		}
		else if (dir == DIR::RIGHT)
		{
			m_bodyAnimator->SetDirection(PlayerBodyAnimator::BodyDirection::RIGHT);
		}
		m_bodyAnimator->SetState(PlayerBodyAnimator::BodyState::WALK);
	}
}

void ClosedGaper::LateUpdate()
{
	Player* player = Player::instance();
	Vector2 relVec = player->headPosition() - transform()->position();
	Vector2 dir = relVec.normalized();

	m_body->AddImpulseToSpeed(dir, m_speed);
}
