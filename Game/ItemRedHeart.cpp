#include "stdafx.h"
#include "ItemRedHeart.h"
#include "Player.h"

void ItemRedHeart::SetSprite(Sprite** pSprite)
{
	*pSprite = SpriteManager::Find(TEXT("redheart_full"));
}

bool ItemRedHeart::OnPlayerCollision(Player* player)
{
	if (player->HP() == player->maxHP())
		return false;
	player->setHP(player->HP() + 1);
	return true;
}

void ItemRedHeart::OnUpdate()
{
}
