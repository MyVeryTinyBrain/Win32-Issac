#include "stdafx.h"
#include "GoldBox.h"
#include "Player.h"
#include "EquipItem.h"

void GoldBox::SetCanGetItem(bool* pCanGetItem)
{
	*pCanGetItem = false;
}

void GoldBox::SetSprites(Sprite** pDefault, Sprite** pChanged)
{
	*pDefault = SpriteManager::Find(TEXT("pickup_005_chests/gold_closed"));
	*pChanged = SpriteManager::Find(TEXT("pickup_005_chests/gold_open"));
}

void GoldBox::SetCollider(Collider2D** pCollider)
{
	RectCollider2D* collider = gameObject()->AddComponent<RectCollider2D>();
	collider->rect()->setWidth(10);
	collider->rect()->setHeight(10);
	gameObject()->AddComponent<Collider2DRenderer>();
	*pCollider = collider;
}

void GoldBox::SetBody2DProperty(Body2D* body)
{
	m_elapsed = 0;
}

void GoldBox::LateAwake()
{
	m_canGetItem = false;
}

void GoldBox::Update()
{
	if (m_canGetItem == false && isShowingItem())
	{
		m_elapsed += Global::deltaTime;
		if (m_elapsed >= 0.5f)
			m_canGetItem = true;
	}
}

void GoldBox::OnPlayerCollision(Player* player)
{
	if (isShowingItem())
		return;

	if (player->key() > 0)
	{
		player->setKey(player->key() - 1);
		ToShowItem();
	}
}

void GoldBox::GiveAbilityToPlayer(Player* player)
{
	if (equipItem())
		equipItem()->GiveAbilityToPlayer(player);
}
