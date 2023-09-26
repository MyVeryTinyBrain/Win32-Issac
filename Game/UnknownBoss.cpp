#include "stdafx.h"
#include "UnknownBoss.h"
#include "UnknownBossAnimator.h"
#include "MyGameObjectLayer.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "Room.h"
#include "Projectile.h"
#include "Player.h"

void UnknownBoss::setSize(Size* pSize)
{
	*pSize = Size::Regular;
}

void UnknownBoss::setInitHP(float* pHP)
{
	*pHP = 100;
}

void UnknownBoss::setCollider(Collider2D** pCollider, Collider2D** pHitTrigger)
{
	m_hitObj = new GameObject(this->transform());
	m_hitObj->setLayer(GO_LAYER_ENEMY);
	m_hit = m_hitObj->AddComponent<RectCollider2D>();
	m_hit->setIsTrigger(true);
	m_hitObj->AddComponent<Collider2DRenderer>();

	*pHitTrigger = m_hit;
}

void UnknownBoss::setRenderers(std::vector<SpriteRenderer*>* pRenderers)
{
    m_rendererObj = new GameObject(this->transform());
    m_rendererObj->transform()->setLocalPosition({});
    m_renderer = m_rendererObj->AddComponent<SpriteRenderer>();
    m_renderer->setRenderTag(RD_TAG_FLYING_OBJ);
    m_renderer->setRenderOrder(RD_ORDER_FLYING_OBJ_FLY);
    m_renderer->setFixedSize(false);
    m_renderer->setOriginSizeWhenDefixedSize(true);

    m_animator = m_rendererObj->AddComponent<UnknownBossAnimator>();
	m_animator->OnUpAnimated += Function<void>(this, &UnknownBoss::OnUpAnimated);
	m_animator->OnPopAnimated += Function<void>(this, &UnknownBoss::OnPopAnimated);

	m_state = -1;
	SetState(0);

    pRenderers->push_back(m_renderer);
}

void UnknownBoss::LateAwake()
{
	m_speed = 35;
	m_body->setFriction(5.0f);
	m_body->setMass(0);

	m_skillDelay = 2.0f;
	m_skillCounter = m_skillDelay;

	m_shootToPlayerCounter = 0;
	m_shootToPlayerNextCounter = 0;
}

void UnknownBoss::OnCollision(Collider2D* collider)
{
}

void UnknownBoss::OnTrigger(Collider2D* collider)
{
}

void UnknownBoss::OnDamaged()
{
}

void UnknownBoss::OnDead()
{
}

void UnknownBoss::Start()
{
	Monster::Start();
}

Vector2 UnknownBoss::center() const
{
	return this->transform()->position();
}

void UnknownBoss::Update()
{
	Monster::Update();

	float hpPer = HP() / maxHP();
	if (hpPer >= 0.7f)
	{
		SetState(0);
	}
	else if (hpPer >= 0.4f)
	{
		SetState(1);
	}
	else
	{
		SetState(2);
	}

	ShootToPlayer();

	bool doingSomething =
		m_shootToPlayerCounter >= 0;
	cout << doingSomething << endl;

	if (doingSomething == false && m_skillCounter > 0)
	{
		m_skillCounter -= Global::deltaTime;
	}
	if (m_skillCounter <= 0)
	{
		m_skillCounter = m_skillDelay;
		
		if (m_state == 0 || m_state == 1)
			m_animator->SetPop();
		else
		{
			size_t r = rand() % 3;
			if (r == 2)
				m_animator->SetUpOnWing();
			else 
				m_animator->SetPop();
		}
	}
}

void UnknownBoss::SetState(const int& state)
{
	if (m_state == state)
		return;
	m_state = state;
	switch (state)
	{
		case 0:
			m_hit->rect()->setWidth(16);
			m_hit->rect()->setHeight(12);
			m_animator->SetState(UnknownBossAnimator::State::LIE);
			break;
		case 1:
			m_hit->rect()->setWidth(10);
			m_hit->rect()->setHeight(16);
			m_animator->SetState(UnknownBossAnimator::State::STAND);
			break;
		case 2:
			m_hit->rect()->setWidth(10);
			m_hit->rect()->setHeight(16);
			m_animator->SetState(UnknownBossAnimator::State::WING);
			break;
	}
	OnStateChange();
}

void UnknownBoss::OnUpAnimated()
{
	Vector2 pos = m_room->GetEmptyGridPosition();
	transform()->setPosition(pos);
}

void UnknownBoss::OnPopAnimated()
{
	switch (m_state)
	{
		case 0:
			{
				size_t r = rand() % 1;
				switch (r)
				{
					case 0:
						m_shootToPlayerCounter = 2.5f;
						break;
				}
			}
			break;
		case 1:

			break;
		case 2:

			break;
	}
}

void UnknownBoss::OnStateChange()
{
}

void UnknownBoss::ShootToPlayer()
{
	if (m_shootToPlayerCounter > 0)
	{
		m_shootToPlayerNextCounter -= Global::deltaTime;
		if (m_shootToPlayerNextCounter <= 0)
		{
			m_shootToPlayerNextCounter = 0.2f;
			MakeProjectilToPlayer();
		}
	}
	m_shootToPlayerCounter -= Global::deltaTime;
}

void UnknownBoss::MakeProjectilToPlayer()
{
	Vector2 relVec = Player::instance()->headPosition() - transform()->position();
	Vector2 dir = relVec.normalized();

	GameObject* projectilObj = new GameObject(transform()->position());
	Projectile* projectile = projectilObj->AddComponent<Projectile>();
	projectile->InitSetType(Projectile::Type::Normal);
	projectile->InitSetDamage(1);
	projectile->InitSetRange(100);
	projectile->InitSetSpeed(100);
	projectile->InitSetDirection(dir);
	projectile->InitSetTargetLayer(GO_LAYER_PLAYER);
}
