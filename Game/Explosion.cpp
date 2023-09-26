#include "stdafx.h"
#include "Explosion.h"
#include "MyGameObjectLayer.h"
#include "MyRenderTag.h"
#include "Character.h"
#include "Monster.h"
#include "RoomObstacle.h"
#include "MyRenderOrder.h"
#include "SoundMgr.h"

void Explosion::Awake()
{
	gameObject()->transform()->setSize({ 2.05f,1.35f });
	gameObject()->setLayer(GO_LAYER_DAMAGABLE);
	PolygonCollider2D* hit = gameObject()->AddComponent<PolygonCollider2D>();
	hit->OnTriggerCallback += Function<void, Collider2D*>(this, &Explosion::OnHit);
	hit->shape2D()->setRadius(30);
	hit->setPolygonVertexCount(10);
	hit->setIsTrigger(true);
	Body2D* body = gameObject()->AddComponent<Body2D>();
	body->RegisterCollider(hit);
	gameObject()->AddComponent<Collider2DRenderer>();
	//body->setJustCollider(true);
	m_body = body;
	m_hit = hit;

	size_t idx = rand() % 8;
	switch (idx)
	{
		case 0: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/01")); break;
		case 1: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/02")); break;
		case 2: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/03")); break;
		case 3: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/04")); break;
		case 4: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/05")); break;
		case 5: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/06")); break;
		case 6: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/07")); break;
		case 7: m_bombRadSprite = SpriteManager::Find(TEXT("effect_017_bombradius/08")); break;
	}
	m_bombRadRenderer = gameObject()->AddComponent<SpriteRenderer>();
	m_bombRadRenderer->setSprite(m_bombRadSprite);
	m_bombRadRenderer->setRenderTag(RD_TAG_FLOOR_OVERLAY);
	m_bombRadRenderer->setRenderOrder(RD_TAG_FLOOR_OVERLAY_BOMBRAD);
	m_bombRadRenderer->setAlphaMode(true);
	m_bombRadRenderer->setAlpha(0.5f);

	m_anim[0] = SpriteManager::Find(TEXT("effect_029_explosion/01"));
	m_anim[1] = SpriteManager::Find(TEXT("effect_029_explosion/02"));
	m_anim[2] = SpriteManager::Find(TEXT("effect_029_explosion/03"));
	m_anim[3] = SpriteManager::Find(TEXT("effect_029_explosion/04"));
	m_anim[4] = SpriteManager::Find(TEXT("effect_029_explosion/05"));
	m_anim[5] = SpriteManager::Find(TEXT("effect_029_explosion/06"));
	m_anim[6] = SpriteManager::Find(TEXT("effect_029_explosion/07"));
	m_anim[7] = SpriteManager::Find(TEXT("effect_029_explosion/08"));
	m_anim[8] = SpriteManager::Find(TEXT("effect_029_explosion/09"));
	m_anim[9] = SpriteManager::Find(TEXT("effect_029_explosion/10"));
	m_anim[10] = SpriteManager::Find(TEXT("effect_029_explosion/11"));
	m_anim[11] = SpriteManager::Find(TEXT("effect_029_explosion/12"));
	GameObject* animObj = new GameObject(this->transform());
	animObj->transform()->setLocalPosition({ 0,35 });
	m_animRenderer = animObj->AddComponent<SpriteRenderer>();
	m_animRenderer->setSprite(m_bombRadSprite);
	m_animRenderer->setRenderTag(RD_TAG_EFFECT);
	m_animRenderer->setSprite(m_anim[0]);

	m_accumulated = 0;
	m_endTime = 0.3f;
	m_exploded = false;

	m_destroyDelay = 5.0f;
}

void Explosion::Start()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::EXPLOSION);
	CSoundMgr::Get_Instance()->PlaySound(L"boss explosions 0.wav", CSoundMgr::CHANNELID::EXPLOSION);
}

void Explosion::Update()
{
	if (m_exploded)
	{
		m_destroyCount -= Global::deltaTime;
		float per = m_destroyCount / m_destroyDelay;
		m_bombRadRenderer->setAlpha(per * 0.5f);
		if (m_destroyCount <= 0)
		{
			gameObject()->Destroy();
		}
		return;
	}

	size_t idx = (size_t)((m_accumulated / m_endTime) * 12);
	if (idx > 11)
	{
		idx = 11;
		m_exploded = true;
		m_animRenderer->setEnable(false);
		m_destroyCount = m_destroyDelay;
	}
	m_animRenderer->setSprite(m_anim[idx]);

	m_accumulated += Global::deltaTime;

	m_body->setEnable(false);
	m_hit->setEnable(false);
}

void Explosion::LateUpdate()
{
}

void Explosion::OnEnable()
{
}

void Explosion::OnDisable()
{
}

void Explosion::OnDestroy()
{
}

void Explosion::OnHit(Collider2D* collider)
{
	Character* character = collider->body2D()->gameObject()->GetComponent<Character>();
	RoomObstacle* obstacle = collider->body2D()->gameObject()->GetComponent<RoomObstacle>();
	if (collider->isTrigger())
	{
		if (character)
		{
			Monster* monster = dynamic_cast<Monster*>(character);
			if (monster)
			{
				monster->TakeDamage(10);
			}
			else // player
			{
				character->TakeDamage(1);
			}
			Vector2 relVec = character->transform()->position() - transform()->position();
			Vector2 dir = relVec.normalized();
			collider->body2D()->AddImpulse(dir * 200);
		}
	}
	else
	{
		if (obstacle)
		{
			obstacle->DestroyObstacle();
		}
	}
}
