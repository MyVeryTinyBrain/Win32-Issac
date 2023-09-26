#include "stdafx.h"
#include "ItemBlueHeart.h"
#include "Player.h"

void ItemBlueHeart::SetSprite(Sprite** pSprite)
{
	*pSprite = SpriteManager::Find(TEXT("blueheart_full"));
}

bool ItemBlueHeart::OnPlayerCollision(Player* player)
{
	player->SetSubHP(player->subHP() + 1);
	return true;
}

void ItemBlueHeart::OnUpdate()
{
}
