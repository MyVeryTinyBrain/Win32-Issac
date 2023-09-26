#include "stdafx.h"
#include "Character.h"

void Character::Awake()
{
	setSize(&m_size);
	setInitHP(&m_hp);
	m_maxHP = m_hp;
	setCollider(&m_collider, &m_hitTrigger);
	setRenderers(&m_renderers);
	m_body = gameObject()->AddComponent<Body2D>();
	if (m_collider)
	{
		m_body->RegisterCollider(m_collider);
		m_collider->OnCollisionCallback += Function<void, Collider2D*>(this, &Character::OnCollision);
	}
	if (m_hitTrigger)
	{
		m_hitTrigger->setIsTrigger(true);
		m_body->RegisterCollider(m_hitTrigger);
		m_hitTrigger->OnTriggerCallback += Function<void, Collider2D*>(this, &Character::OnTrigger);
	}

	m_speed = 0;
	m_isDead = false;
	m_damagedEffectTime = 0;

	LateAwake();
}

void Character::Start()
{
}

void Character::Update()
{
	if (m_damagedEffectTime > 0)
	{
		m_damagedEffectTime -= Global::deltaTime;
		if (m_damagedEffectTime <= 0)
		{
			m_damagedEffectTime = 0;
			for (auto& sr : m_renderers)
			{
				sr->setFillMode(false);
			}
		}
		else
		{
			for (auto& sr : m_renderers)
			{
				sr->setFillMode(true);
				sr->setFillColor(RGB(255, 0, 0));
			}
		}
	}
}

void Character::LateUpdate()
{
}

void Character::OnEnable()
{
}

void Character::OnDisable()
{
}

void Character::OnDestroy()
{
}

Body2D* Character::body() const
{
	return m_body;
}

const float& Character::HP() const
{
	return m_hp;
}

const float& Character::maxHP() const
{
	return m_maxHP;
}

void Character::setMaxHP(const float& MaxHP)
{
	m_maxHP = MaxHP;
}

void Character::TakeDamage(float Damage)
{
	if (ApplyDamage(&Damage) == false) return;
	m_hp -= Damage;
	if (m_hp <= 0)
	{
		m_hp = 0;
		if (m_isDead == false)
		{
			m_isDead = true;

			m_body->setVelocity({});
			m_body->setEnable(false);
			if (m_collider) m_collider->setEnable(false);
			if (m_hitTrigger) m_hitTrigger->setEnable(false);

			OnDeadCallback(this);
			OnDead();
		}
	}
	else if (m_hp > 0)
	{
		m_damagedEffectTime = 0.1f;
		OnDamaged();
	}
}

void Character::setHP(const float& HP)
{
	float _hp = HP;
	if (_hp > m_maxHP)
		_hp = m_maxHP;
	if (_hp < 0)
		_hp = 0;
	m_hp = _hp;
}

const bool& Character::isDead() const
{
	return m_isDead;
}

const float& Character::speed() const
{
	return m_speed;
}

void Character::setSpeed(const float& value)
{
	m_speed = value;
}

const Character::Size& Character::size() const
{
	return m_size;
}

void Character::SetDamagedEffectTime(const float& time)
{
	m_damagedEffectTime = time;
}

bool Character::ApplyDamage(float* pDamage)
{
	return true;
}