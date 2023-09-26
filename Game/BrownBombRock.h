#pragma once
#ifndef __BrownBombRock_h__
#define __BrownBombRock_h__

#include "RoomObstacle.h"

class BrownBombRock : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
