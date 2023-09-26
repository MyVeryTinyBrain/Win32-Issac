#include "stdafx.h"
#include "BabyMonster.h"
#include "BabyMonsterAnimator.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "Projectile.h"
#include "RegularBloodPoofAnimator.h"
#include "SmallPoofAnimator.h"
#include "Room.h"
#include "TargetEffect.h"
#include "Define.h"
#include "Pool.h"
#include "SoundMgr.h"

void BabyMonster::setSize(Size* pSize)
{
    *pSize = Size::Regular;
}

void BabyMonster::setInitHP(float* pHP)
{
    *pHP = 5;
}

void BabyMonster::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
{
	GameObject* hitObj = new GameObject();
	hitObj->transform()->setLocalPosition({});
	hitObj->setLayer(GO_LAYER_ENEMY);
	CircleCollider2D* hit = hitObj->AddComponent<CircleCollider2D>();
	hit->circle()->setRadius(12);
	hit->setIsTrigger(true);
	hitObj->AddComponent<Collider2DRenderer>();

	*pHitTrigger = hit;
}

void BabyMonster::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
	m_spriteObj = new GameObject(this->transform());
	m_spriteObj->transform()->setLocalPosition({});

	m_spriteObj->transform()->setLocalPosition({});
	SpriteRenderer* sr = m_spriteObj->AddComponent<SpriteRenderer>();
	sr->setRenderTag(RD_TAG_FLYING_OBJ);
	sr->setRenderOrder(RD_ORDER_FLYING_OBJ_FLY);
	sr->setYOrder(true);
	sr->setFixedSize(false);
	sr->setOriginSizeWhenDefixedSize(true);

	m_animator = m_spriteObj->AddComponent<BabyMonsterAnimator>();
	m_animator->OnAttackAnimated += Function<void>(this, &BabyMonster::OnAttackAnimated);
	m_animator->OnTeleportAnimated += Function<void>(this, &BabyMonster::OnTeleportAnimated);

	pRenderers->push_back(sr);
}

void BabyMonster::LateAwake()
{
	m_speed = 50;

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
	m_shadowObj->transform()->setSize({ 15,10 });

	m_body->setFriction(2.0f);
	m_body->setMass(5);
	
	m_teleportTarget = {};
	m_teleportCounterInit = 2;
	m_attackDelay = 1.0f;
	m_teleportCounter = m_teleportCounterInit;
	m_attackCounter = m_attackDelay;
}

void BabyMonster::OnCollision(Collider2D* collider)
{
}

void BabyMonster::OnTrigger(Collider2D* collider)
{
}

void BabyMonster::OnDamaged()
{
}

void BabyMonster::OnDead()
{
	GameObject* bloodPoofObj = new GameObject(this->transform()->position());
	SpriteRenderer* bloodRenderer = bloodPoofObj->AddComponent<SpriteRenderer>();
	bloodRenderer->setRenderTag(RD_TAG_OBJ);
	bloodPoofObj->AddComponent<RegularBloodPoofAnimator>();

	gameObject()->Destroy();
}

Vector2 BabyMonster::center() const
{
	return transform()->position();
}

void BabyMonster::Update()
{
	Monster::Update();

	if (m_animator->isPlayingAttack() == false && m_animator->isPlayingTeleport() == false)
	{
		m_attackCounter -= Global::deltaTime;

		if (m_teleportCounter == 0)
		{
			m_teleportCounter = m_teleportCounterInit;
			m_body->setVelocity({});
			m_animator->PlayTeleport();
			m_teleportTarget = m_room->GetEmptyGridPosition();

			GameObject* targetEffectObj = new GameObject(m_teleportTarget);
			targetEffectObj->AddComponent<TargetEffect>()->InitSetRemainingTime(0.5f);

			GameObject* poofEffectObj = new GameObject(transform()->position());
			SpriteRenderer* effectRenderer = poofEffectObj->AddComponent<SpriteRenderer>();
			effectRenderer->setRenderTag(RD_TAG_EFFECT);
			effectRenderer->setFixedSize(false);
			effectRenderer->setOriginSizeWhenDefixedSize(true);
			poofEffectObj->AddComponent<SmallPoofAnimator>();
			poofEffectObj->transform()->setSize({ 2,2 });
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::TELEPORT);
			CSoundMgr::Get_Instance()->PlaySound(L"band aid pick up.wav", CSoundMgr::CHANNELID::TELEPORT);

			m_hitTrigger->setEnable(false);
			m_body->setEnable(false);
			return;
		}
		if (m_attackCounter <= 0)
		{
			m_attackCounter = m_attackDelay + (float)(rand() % 21) * 0.1f;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"child angry roar 1.wav", CSoundMgr::CHANNELID::MONSTER);
			m_body->setVelocity({});
			m_animator->PlayAttack();
			return;
		}

		Vector2 relVec = Player::instance()->headPosition() - transform()->position();
		Vector2 dir = relVec.normalized();
		m_body->AddImpulseToSpeed(dir, m_speed);
	}
}

void BabyMonster::OnTeleportAnimated()
{
	if (m_room == nullptr)
		return;

	transform()->setPosition(m_teleportTarget);
	
	GameObject* poofEffectObj = new GameObject(transform()->position());
	SpriteRenderer* effectRenderer = poofEffectObj->AddComponent<SpriteRenderer>();
	effectRenderer->setRenderTag(RD_TAG_EFFECT);
	effectRenderer->setFixedSize(false);
	effectRenderer->setOriginSizeWhenDefixedSize(true);
	poofEffectObj->AddComponent<SmallPoofAnimator>();
	poofEffectObj->transform()->setSize({ 2,2 });

	m_hitTrigger->setEnable(true);
	m_body->setEnable(true);
}

void BabyMonster::OnAttackAnimated()
{
	Player* player = Player::instance();
	Vector2 relVec = player->headPosition() - transform()->position();
	Vector2 dir = relVec.normalized();

	GameObject* projectilObj = new GameObject(transform()->position());
	Projectile* projectile = projectilObj->AddComponent<Projectile>();
	projectile->InitSetType(Projectile::Type::Blood);
	projectile->InitSetDamage(1);
	projectile->InitSetRange(200);
	projectile->InitSetSpeed(100);
	projectile->InitSetDirection(dir);
	projectile->InitSetTargetLayer(GO_LAYER_PLAYER);

	--m_teleportCounter;
}
