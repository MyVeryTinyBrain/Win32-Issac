#pragma once
#ifndef __BrownRock03_h__
#define __BrownRock03_h__

#include "RoomObstacle.h"

class BrownRock03 : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
