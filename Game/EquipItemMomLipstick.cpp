#include "stdafx.h"
#include "EquipItemMomLipstick.h"
#include "Player.h"

void EquipItemMomLipstick::GiveAbilityToPlayer(Player* player)
{
	player->setRange(player->range() + 50);
	player->setProjectileSpeed(player->projectileSpeed() + 50);
}

EquipItemMomLipstick::EquipItemMomLipstick() : EquipItem(SpriteManager::Find(TEXT("collectibles_031_momslipstick")))
{
}
