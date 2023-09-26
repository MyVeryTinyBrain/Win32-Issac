#pragma once
#ifndef __BrownRock01_h__
#define __BrownRock01_h__

#include "RoomObstacle.h"

class BrownRock01 : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
