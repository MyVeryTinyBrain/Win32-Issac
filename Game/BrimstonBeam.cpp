#include "stdafx.h"
#include "BrimstonBeam.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "MyGameObjectLayer.h"
#include "Character.h"
#include "Monster.h"
#include "UIHealthBar.h"

void BrimstonBeam::Awake()
{
	m_sprites[0] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/1"));
	m_sprites[1] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/2"));
	m_sprites[2] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/3"));
	m_sprites[3] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/4"));
	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	m_renderer->setRenderTag(RD_TAG_EFFECT);
	m_renderer->setRenderOrder(RD_ORDER_EFFECT_BRIMSTON_BEAM);
	m_renderer->setFixedSize(false);
	m_renderer->setOriginSizeWhenDefixedSize(false);
	m_elasped = 0;

	gameObject()->setLayer(GO_LAYER_DAMAGABLE);
	m_hitTrigger = gameObject()->AddComponent<RectCollider2D>();
	m_hitTrigger->setIsTrigger(true);
	m_hitTrigger->rect()->setWidth(0.3f);
	m_hitTrigger->rect()->setHeight(0.5f);
	m_hitTrigger->OnTriggerCallback += Function<void, Collider2D*>(this, &BrimstonBeam::OnTrigger);
	m_body = gameObject()->AddComponent<Body2D>();
	m_body->RegisterCollider(m_hitTrigger);
	gameObject()->AddComponent<Collider2DRenderer>();

	SetWidth(10);

	m_targetLayer = GO_LAYER_ENEMY;
	m_damage = 0.5f;

	m_triggerToggleCounter = 0;
}

void BrimstonBeam::Start()
{
}

void BrimstonBeam::Update()
{
	float delay = 0.025f;
	float step = 4;
	float y = fmodf(m_elasped / delay, 2) * 0.5f;
	size_t pulse = (size_t)(y * step);
	m_renderer->setSprite(m_sprites[pulse]);
	m_elasped += Global::deltaTime;

	m_triggerToggleCounter -= Global::deltaTime;
	m_hitTrigger->setEnable(false);
	m_body->setEnable(false);
	if (m_triggerToggleCounter <= 0)
	{
		m_triggerToggleCounter = 0.2f;
		m_hitTrigger->setEnable(true);
		m_body->setEnable(true);
	}
}

void BrimstonBeam::LateUpdate()
{
}

void BrimstonBeam::OnEnable()
{
}

void BrimstonBeam::OnDisable()
{
}

void BrimstonBeam::OnDestroy()
{
}

void BrimstonBeam::SetTwoPoints(const Vector2& a, const Vector2& b)
{
	Vector2 relVec = b - a;
	float angle = Vector2::Radian(Vector2::right(), relVec.normalized()) + PI * 0.5f;
	transform()->setAngle(angle);
	transform()->setPosition((a + b) * 0.5f);
	transform()->setSize({ m_width * 2, relVec.magnitude() });
}

void BrimstonBeam::SetWidth(const float& Width)
{
	m_width = Width;
}

void BrimstonBeam::SetOrder(const int& order)
{
	m_renderer->setRenderOrder(RD_ORDER_EFFECT_BRIMSTON_BEAM + order);
}

void BrimstonBeam::setTargetLayer(const unsigned char& TargetLayer)
{
	m_targetLayer = TargetLayer;
}

void BrimstonBeam::setDamage(const float& damage)
{
	m_damage = damage;
}

void BrimstonBeam::OnTrigger(Collider2D* collider)
{
	Body2D* body = collider->body2D();
	if (collider->gameObject()->layer() == m_targetLayer)
	{
		Character* character = body->gameObject()->GetComponent<Character>();
		if (character)
		{
			if (dynamic_cast<Monster*>(character))
			{
				UIHealthBar* hpBar = UIHealthBar::instance();
				if (hpBar)
					hpBar->AddTarget(character);
			}
			character->TakeDamage(m_damage);
		}
	}
}
