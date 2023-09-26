#include "stdafx.h"
#include "BlackBowl1.h"

void BlackBowl1::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BlackBowl1::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/bowl_black01"));
}

void BlackBowl1::OnDestroyObstacle()
{
}
