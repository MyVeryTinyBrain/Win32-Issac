#include "stdafx.h"
#include "IronBlock.h"

void IronBlock::SetDestructible(bool* pDestructible)
{
	*pDestructible = false;
}

void IronBlock::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/iron"));
	*pDestroyed = nullptr;
}

void IronBlock::OnDestroyObstacle()
{
}
