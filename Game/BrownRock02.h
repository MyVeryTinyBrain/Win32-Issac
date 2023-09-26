#pragma once
#ifndef __BrownRock02_h__
#define __BrownRock02_h__

#include "RoomObstacle.h"

class BrownRock02 : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
