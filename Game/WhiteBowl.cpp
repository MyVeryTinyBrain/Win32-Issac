#include "stdafx.h"
#include "WhiteBowl.h"

void WhiteBowl::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void WhiteBowl::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/bowl_white01"));
}

void WhiteBowl::OnDestroyObstacle()
{
}
