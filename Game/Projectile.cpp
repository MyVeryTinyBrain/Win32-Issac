#include "stdafx.h"
#include "Projectile.h"
#include "ProjectileAnimator.h"
#include "MyGameObjectLayer.h"
#include "MyRenderTag.h"
#include "Character.h"
#include "Monster.h"
#include "UIHealthBar.h"
#include "Player.h"
#include "Define.h"
#include "Pool.h"
#include "SoundMgr.h"

void Projectile::Awake()
{
	m_damage = 0;
	m_dir = {};
	m_speed = 0;
	m_range = 0;

	m_type = Type::Normal;

	m_shadowObj = new GameObject(this->transform());
	m_shadowObj->transform()->setLocalPosition({0, -FLYING_HEIGHT});
	SpriteRenderer* shadowRenderer = m_shadowObj->AddComponent<SpriteRenderer>();
	shadowRenderer->setSprite(SpriteManager::Find(TEXT("shadow")));
	shadowRenderer->setRenderTag(RD_TAG_SHADOW);
	shadowRenderer->setFixedSize(false);
	shadowRenderer->setOriginSizeWhenDefixedSize(false);
	shadowRenderer->setAlphaMode(true);
	shadowRenderer->setAlpha(SHADOW_ALPHA);

	m_projectileObj = new GameObject(this->transform());
	m_projectileObj->transform()->setLocalPosition({});
	m_projectileObj->setLayer(GO_LAYER_DAMAGABLE);

	SpriteRenderer* spriteRenderer = m_projectileObj->AddComponent<SpriteRenderer>();
	spriteRenderer->setFixedSize(false);
	spriteRenderer->setOriginSizeWhenDefixedSize(false);
	spriteRenderer->setRenderTag(RD_TAG_PROJECTILE);

	m_accumulatedDistance = 0;
	m_doStop = false;

	m_hitTrigger = m_projectileObj->AddComponent<CircleCollider2D>();
	m_hitTrigger->circle()->setRadius(0.1f);
	m_hitTrigger->setIsTrigger(true);
	m_hitTrigger->OnTriggerCallback += Function<void, Collider2D*>(this, &Projectile::OnTrigger);
	m_projectileObj->AddComponent<Collider2DRenderer>();
	Body2D* body = m_projectileObj->AddComponent<Body2D>();
	body->RegisterCollider(m_hitTrigger);
	//body->setJustCollider(true);
}

void Projectile::Start()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::TEAR_FIRE);
	CSoundMgr::Get_Instance()->PlaySound(L"tear fire 4.wav", CSoundMgr::CHANNELID::TEAR_FIRE);
}

void Projectile::Update()
{
	float size = (float)(m_damage + 1) * 20;
	m_projectileObj->transform()->setSize({ size,size });
	m_shadowObj->transform()->setSize({ size / 4.0f, size / 8.0f });

	if (m_doStop)
	{
		m_animator->PlayOnceDestroyAnimation();
		return;
	}
	
	float dist = m_speed * Global::deltaTime;
	m_accumulatedDistance += dist;

	if (m_accumulatedDistance > m_range)
	{
		dist = m_accumulatedDistance - m_range;
		m_accumulatedDistance = m_range;

		m_doStop = true;
		m_projectileObj->transform()->setLocalAngle((float)(rand() % 360));
		m_shadowObj->setEnable(false);
		m_hitTrigger->setEnable(false);
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::TEAR_HIT);
		CSoundMgr::Get_Instance()->PlaySound(L"tear block.wav", CSoundMgr::CHANNELID::TEAR_HIT);

		CreatePool();
	}

	float percent = m_accumulatedDistance / m_range;
	float projectileY = -powf(percent, 6) * FLYING_HEIGHT;
	m_projectileObj->transform()->setLocalPosition({ 0,projectileY });

	Vector2 delta = m_dir * dist;
	transform()->setPosition(transform()->position() + delta);
}

void Projectile::LateUpdate()
{
}

void Projectile::OnEnable()
{
}

void Projectile::OnDisable()
{
}

void Projectile::OnDestroy()
{
}

void Projectile::InitSetType(const Type& type)
{
	if (m_animator)
		return;
	m_animator = m_projectileObj->AddComponent<ProjectileAnimator>();
	switch (type)
	{
		case Type::Normal:
			m_animator->InitSetSprites(
				SpriteManager::Find(TEXT("effect_015_tearpoofa/01")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/02")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/03")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/04")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/05")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/06")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/07")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/08")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/09")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/10")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/11")),
				SpriteManager::Find(TEXT("effect_015_tearpoofa/12"))
			);
			break;
		case Type::Blood:
			m_animator->InitSetSprites(
				SpriteManager::Find(TEXT("effect_003_bloodtear/01")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/02")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/03")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/04")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/05")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/06")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/07")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/08")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/09")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/10")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/11")),
				SpriteManager::Find(TEXT("effect_003_bloodtear/12"))
			);
			break;
	}
	m_animator->OnDestroyAnimated += Function<void>(this, &Projectile::OnDestroyAnimated);
	m_animator->PlayIdleAnimation();
	m_type = type;
}

void Projectile::InitSetDamage(const int& damage)
{
	m_damage = damage;
}

void Projectile::InitSetSpeed(const float& speed)
{
	m_speed = speed;
}

void Projectile::InitSetDirection(const Vector2& direction)
{
	m_dir = direction;
}

void Projectile::InitSetRange(const float& range)
{
	m_range = range;
}

void Projectile::InitSetTargetLayer(const unsigned char& targetLayer)
{
	m_targetLayer = targetLayer;
}

void Projectile::OnDestroyAnimated()
{
	gameObject()->Destroy();
}

void Projectile::OnTrigger(Collider2D* collider)
{
	if (m_doStop)
		return;
	const unsigned char& layer = collider->gameObject()->layer();
	if (layer == GO_LAYER_PROJ_WALL || layer == GO_LAYER_OBJECT || layer == GO_LAYER_DOOR || layer == m_targetLayer)
	{
		Pool* pool = CreatePool();

		if (layer == m_targetLayer)
		{
			if (collider->isTrigger())
			{
				GameObject* obj = collider->body2D()->gameObject();
				Character* character = obj->GetComponent<Character>();
				if (character)
				{
					character->TakeDamage((float)m_damage);
					character->body()->AddImpulse(m_dir * m_speed * 0.35f);
					if (dynamic_cast<Monster*>(character))
					{
						UIHealthBar* hpBar = UIHealthBar::instance();
						if (hpBar)
							hpBar->AddTarget(character);
					}
				}
			}
			else
			{
				return;
			}
		}
		else if(layer == GO_LAYER_PROJ_WALL)
		{
			if (pool)
				pool->transform()->setPosition(pool->transform()->position() - m_dir * 20);
		}
		m_doStop = true;
		m_projectileObj->transform()->setLocalAngle((float)(rand() % 360));
		m_shadowObj->setEnable(false);
		m_hitTrigger->setEnable(false);
		m_animator->PlayOnceDestroyAnimation();
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::TEAR_HIT);
		CSoundMgr::Get_Instance()->PlaySound(L"tear block.wav", CSoundMgr::CHANNELID::TEAR_HIT);
	}
}

Pool* Projectile::CreatePool()
{
	size_t spawn = rand() % 100 + 1;
	if (spawn <= 71)
		return nullptr;

	GameObject* poolObj = new GameObject(m_projectileObj->transform()->position());
	Pool* pool = poolObj->AddComponent<Pool>();
	Pool::Type poolType = m_type == Type::Normal ? Pool::Type::Water : Pool::Type::Blood;
	Pool::Size poolSize = Pool::Size::Small;
	if (m_damage >= 2) poolSize = Pool::Size::Regular;
	if (m_damage >= 5) poolSize = Pool::Size::Large;
	pool->InitGenerate(poolType, poolSize);
	return pool;
}
