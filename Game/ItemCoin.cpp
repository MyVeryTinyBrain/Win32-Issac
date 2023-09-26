#include "stdafx.h"
#include "ItemCoin.h"
#include "Player.h"

void ItemCoin::SetSprite(Sprite** pSprite)
{
	*pSprite = SpriteManager::Find(TEXT("pickup_002_coin/01"));
}

bool ItemCoin::OnPlayerCollision(Player* player)
{
	player->setCoin(player->coin() + 1);
	return true;
}

void ItemCoin::OnUpdate()
{
}
