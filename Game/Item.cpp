#include "stdafx.h"
#include "Item.h"
#include "MyGameObjectLayer.h"
#include "MyRenderTag.h"
#include "Player.h"
#include "SoundMgr.h"

void Item::Awake()
{
	gameObject()->setLayer(GO_LAYER_ITEM);
	m_collider = gameObject()->AddComponent<CircleCollider2D>();
	m_collider->circle()->setRadius(5);
	m_collider->OnCollisionCallback += Function<void, Collider2D*>(this, &Item::OnCollision);
	m_body = gameObject()->AddComponent<Body2D>();
	m_body->RegisterCollider(m_collider);
	gameObject()->AddComponent<Collider2DRenderer>();

	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	Sprite* sprite = nullptr;
	SetSprite(&sprite);
	m_renderer->setSprite(sprite);
	m_renderer->setRenderTag(RD_TAG_OBJ);
	m_renderer->setFixedSize(false);

	m_elapsed = 0;
	m_animated = false;
}

void Item::Start()
{
}

void Item::Update()
{
	if (m_elapsed <= 0.5f)
	{
		m_elapsed += Global::deltaTime;
		float x = -0.5f * sinf(2 * TAU * m_elapsed) + 1;
		float y = 0.5f * sinf(2 * TAU * m_elapsed) + 1;
		transform()->setSize({ x,y });
	}
	else if (!m_animated)
	{
		transform()->setSize({ 1,1 });
		m_animated = true;
	}

	OnUpdate();
}

void Item::LateUpdate()
{
}

void Item::OnEnable()
{
}

void Item::OnDisable()
{
}

void Item::OnDestroy()
{
}

Body2D* Item::body() const
{
	return m_body;
}

void Item::OnCollision(Collider2D* collider)
{
	Body2D* b = collider->body2D();
	if (collider->isTrigger() == false)
	{
		if (Player::instance()->gameObject() == b->gameObject())
		{
			if (OnPlayerCollision(Player::instance()) == false)
				return;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::GOTITEM);
			CSoundMgr::Get_Instance()->PlaySound(L"nickel pickup.wav", CSoundMgr::CHANNELID::GOTITEM);
			gameObject()->Destroy();
		}
	}
}
