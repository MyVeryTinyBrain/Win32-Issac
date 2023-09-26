#include "stdafx.h"
#include "EquipItemPlacer.h"
#include "SmallPoofAnimator.h"
#include "MyRenderTag.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "EquipItem.h"

void EquipItemPlacer::Awake()
{
	SetCanGetItem(&m_showItem);
	SetSprites(&m_defaultPlacerSprite, &m_changedPlcaerSprite);
	m_placerRenderer = gameObject()->AddComponent<SpriteRenderer>();
	m_placerRenderer->setRenderTag(RD_TAG_OBJ);
	if (!m_showItem)
		m_placerRenderer->setSprite(m_defaultPlacerSprite);
	else
		m_placerRenderer->setSprite(m_changedPlcaerSprite);

	SetCollider(&m_collider);
	gameObject()->setLayer(GO_LAYER_ITEM);
	m_body = gameObject()->AddComponent<Body2D>();
	SetBody2DProperty(m_body);
	if (m_collider)
	{
		m_body->RegisterCollider(m_collider);
		m_collider->OnCollisionCallback += Function<void, Collider2D*>(this, &EquipItemPlacer::OnCollision);
	}

	m_itemObj = new GameObject(this->transform()->position(), this->transform());
	m_itemRenderer = m_itemObj->AddComponent<SpriteRenderer>();
	m_itemRenderer->setRenderTag(RD_TAG_OBJ);

	m_equipItem = nullptr;

	m_elapsed = 0;
	m_used = false;
	m_canGetItem = true;

	LateAwake();
}

void EquipItemPlacer::Start()
{
	GameObject* poofEffectObj = new GameObject(this->transform()->position(), this->transform());
	poofEffectObj->transform()->setSize({ 3,3 });
	SpriteRenderer* effectRenderer = poofEffectObj->AddComponent<SpriteRenderer>();
	effectRenderer->setRenderTag(RD_TAG_EFFECT);
	effectRenderer->setFixedSize(false);
	effectRenderer->setOriginSizeWhenDefixedSize(true);
	poofEffectObj->AddComponent<SmallPoofAnimator>();

	if (m_showItem)
		ToShowItem();
}

void EquipItemPlacer::Update()
{
}

void EquipItemPlacer::LateUpdate()
{
	if (m_showItem && !m_used)
	{
		m_elapsed += Global::deltaTime;
		float y = sinf(m_elapsed * 2) * 5 + 15;
		m_itemObj->transform()->setPosition(this->transform()->position() + Vector2(0, y));
	}
}

void EquipItemPlacer::OnEnable()
{
}

void EquipItemPlacer::OnDisable()
{
}

void EquipItemPlacer::OnDestroy()
{
	SAFE_DELETE(m_equipItem);
}

void EquipItemPlacer::OnCollision(Collider2D* collider)
{
	if (m_used)
		return;

	Body2D* body = collider->body2D();
	if (Player::instance()->gameObject() == body->gameObject())
	{
		OnPlayerCollision(Player::instance());
		if (m_canGetItem && m_showItem && !m_used)
		{
			m_used = true;
			m_itemObj->setEnable(false);
			GiveAbilityToPlayer(Player::instance());
			if (m_equipItem)
			{
				Player::instance()->GotItem(m_equipItem->sprite());
			}
		}
	}
}

void EquipItemPlacer::ToShowItem()
{
	m_showItem = true;
	m_placerRenderer->setSprite(m_changedPlcaerSprite);
	if (m_equipItem)
		m_itemRenderer->setSprite(m_equipItem->sprite());
}

const bool& EquipItemPlacer::isShowingItem() const
{
	return m_showItem;
}

EquipItem* EquipItemPlacer::equipItem() const
{
	return m_equipItem;
}
