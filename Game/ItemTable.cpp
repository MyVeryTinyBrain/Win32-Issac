#include "stdafx.h"
#include "ItemTable.h"
#include "EquipItem.h"

void ItemTable::SetCanGetItem(bool* pCanGetItem)
{
	*pCanGetItem = true;
}

void ItemTable::SetSprites(Sprite** pDefault, Sprite** pChanged)
{
	*pDefault = SpriteManager::Find(TEXT("itemtable"));
	*pChanged = SpriteManager::Find(TEXT("itemtable"));
}

void ItemTable::SetCollider(Collider2D** pCollider)
{
	RectCollider2D* collider = gameObject()->AddComponent<RectCollider2D>();
	collider->rect()->setWidth(10);
	collider->rect()->setHeight(10);
	gameObject()->AddComponent<Collider2DRenderer>();
	*pCollider = collider;
}

void ItemTable::SetBody2DProperty(Body2D* body)
{
	body->setJustCollider(true);
}

void ItemTable::LateAwake()
{
}

void ItemTable::Update()
{
}

void ItemTable::OnPlayerCollision(Player* player)
{
}

void ItemTable::GiveAbilityToPlayer(Player* player)
{
	if (equipItem())
	equipItem()->GiveAbilityToPlayer(player);
}
