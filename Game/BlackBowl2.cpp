#include "stdafx.h"
#include "BlackBowl2.h"

void BlackBowl2::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BlackBowl2::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/bowl_black02"));
}

void BlackBowl2::OnDestroyObstacle()
{
}
