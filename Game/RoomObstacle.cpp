#include "stdafx.h"
#include "RoomObstacle.h"
#include "MyRenderTag.h"
#include "Room.h"
#include "MyGameObjectLayer.h"

void RoomObstacle::Awake()
{
	gameObject()->setLayer(GO_LAYER_OBJECT);
	m_collider = gameObject()->AddComponent<RectCollider2D>();
	m_collider->rect()->setWidth(Room::FloorGridLength * 0.5f - 1);
	m_collider->rect()->setHeight(Room::FloorGridLength * 0.5f - 1);
	gameObject()->AddComponent<Collider2DRenderer>();
	m_body = gameObject()->AddComponent<Body2D>();
	m_body->setJustCollider(true);
	m_body->RegisterCollider(m_collider);

	SetDestructible(&m_isDestructible);
	SetSprites(&m_defaultSprite, &m_destroyedSprite);

	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	m_renderer->setRenderTag(RD_TAG_OBJ);
	m_renderer->setSprite(m_defaultSprite);

	m_ix = 0;
	m_iy = 0;
}

void RoomObstacle::Start()
{
}

void RoomObstacle::Update()
{
}

void RoomObstacle::LateUpdate()
{
}

void RoomObstacle::OnEnable()
{
}

void RoomObstacle::OnDisable()
{
}

void RoomObstacle::OnDestroy()
{
}

void RoomObstacle::DestroyObstacle()
{
	if (m_destroyed == true || m_isDestructible == false) return;
	m_destroyed = true;
	m_renderer->setSprite(m_destroyedSprite);
	m_body->setEnable(false);
	m_collider->setEnable(false);
	m_renderer->setRenderTag(RD_TAG_FLOOR_OVERLAY);
	OnDestroyObstacle();
	OnObstacleDestroyedCallback(this);
}

Vector2 RoomObstacle::GetIndex() const
{
	return { (float)m_ix, (float)m_iy };
}

void RoomObstacle::InitSetIndex(const size_t& ix, const size_t& iy)
{
	m_ix = ix;
	m_iy = iy;
}
