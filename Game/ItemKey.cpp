#include "stdafx.h"
#include "ItemKey.h"
#include "Player.h"

void ItemKey::SetSprite(Sprite** pSprite)
{
	*pSprite = SpriteManager::Find(TEXT("pickup_003_charged_key"));
}

bool ItemKey::OnPlayerCollision(Player* player)
{
	player->setKey(player->key() + 1);
	return true;
}

void ItemKey::OnUpdate()
{
}
