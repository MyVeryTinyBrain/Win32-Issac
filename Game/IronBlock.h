#pragma once
#ifndef __IronBlock_h__
#define __IronBlock_h__

#include "RoomObstacle.h"

class IronBlock : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
