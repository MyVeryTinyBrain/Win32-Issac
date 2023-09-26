#include "stdafx.h"
#include "ItemBomb.h"
#include "Player.h"

void ItemBomb::SetSprite(Sprite** pSprite)
{
	*pSprite = SpriteManager::Find(TEXT("pickup_016_bomb/default"));
}

bool ItemBomb::OnPlayerCollision(Player* player)
{
	player->setBomb(player->bomb() + 1);
	return true;
}

void ItemBomb::OnUpdate()
{
}
