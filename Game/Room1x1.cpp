#include "stdafx.h"
#include "Room1x1.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "Door.h"
#include "MyGameObjectLayer.h"

void Room1x1::Awake()
{
	Room::Awake();

	m_leftDoor = nullptr;
	m_topDoor = nullptr;
	m_rightDoor = nullptr;
	m_bottomDoor = nullptr;
}

void Room1x1::Start()
{
}

void Room1x1::Update()
{
	Room::Update();
}

void Room1x1::LateUpdate()
{
}

void Room1x1::OnEnable()
{
}

void Room1x1::OnDisable()
{
}

void Room1x1::SetCxCy(size_t* pCX, size_t* pCY)
{
	*pCX = 1;
	*pCY = 1;
}

void Room1x1::InitGenerateRoom(const TCHAR* bmpKey)
{
	auto makePath = [&](TCHAR* dest, const TCHAR* innerPath) -> void
	{
		_tcscpy_s(dest, 256, bmpKey);
		_tcscat_s(dest, 256, innerPath);
	};

	auto createFloor = [&]() -> GameObject*
	{
		TCHAR floorSpritePath[256];
		int floorType = rand() % 2;
		switch (floorType)
		{
			case 0: makePath(floorSpritePath, TEXT("/floor01")); break;
			case 1: makePath(floorSpritePath, TEXT("/floor02")); break;
		}

		GameObject* floor = new GameObject(this->transform());
		floor->transform()->setLocalPosition({});
		SpriteRenderer* floorLTRenderer = floor->AddComponent<SpriteRenderer>();
		floorLTRenderer->setSprite(SpriteManager::instance()->Find(floorSpritePath));
		floorLTRenderer->setRenderTag(RD_TAG_BACKGROUND_FLOOR);
		floorLTRenderer->setRenderOrder(RD_ORDER_BACKGROUND_FLOOR);
		return floor;
	};

	auto createWall = [&]() -> GameObject*
	{
		TCHAR wallSpritePath[256];
		int wallType = rand() % 3;
		switch (wallType)
		{
			case 0: makePath(wallSpritePath, TEXT("/wall01")); break;
			case 1: makePath(wallSpritePath, TEXT("/wall02")); break;
			case 2: makePath(wallSpritePath, TEXT("/wall03")); break;
			case 3: makePath(wallSpritePath, TEXT("/wall04")); break;
		}

		GameObject* wall = new GameObject(this->transform());
		SpriteRenderer* wallRenderer = wall->AddComponent<SpriteRenderer>();
		wallRenderer->setSprite(SpriteManager::instance()->Find(wallSpritePath));
		wallRenderer->setRenderTag(RD_TAG_BACKGROUND_WALL);
		wallRenderer->setRenderOrder(RD_ORDER_BACKGROUND_WALL);
		return wall;
	};

	GameObject* floorLT = createFloor();
	floorLT->transform()->setLocalPosition({ -FloorWidth * 0.5f,+FloorHeight * 0.5f });

	GameObject* floorRT = createFloor();
	floorRT->transform()->setLocalPosition({ +FloorWidth * 0.5f,+FloorHeight * 0.5f });
	floorRT->transform()->setLocalSize({ -1,1 });

	GameObject* floorRB = createFloor();
	floorRB->transform()->setLocalPosition({ +FloorWidth * 0.5f,-FloorHeight * 0.5f });
	floorRB->transform()->setLocalSize({ -1,-1 });

	GameObject* floorLB = createFloor();
	floorLB->transform()->setLocalPosition({ -FloorWidth * 0.5f,-FloorHeight * 0.5f });
	floorLB->transform()->setLocalSize({ 1,-1 });

	GameObject* wallLT = createWall();
	wallLT->transform()->setLocalPosition({ (FloorWidth + CornerLength) * -0.5f,(FloorHeight + CornerLength) * 0.5f });

	GameObject* wallRT = createWall();
	wallRT->transform()->setLocalPosition({ (FloorWidth + CornerLength) * 0.5f,(FloorHeight + CornerLength) * 0.5f });
	wallRT->transform()->setLocalSize({ -1,1 });

	GameObject* wallRB = createWall();
	wallRB->transform()->setLocalPosition({ (FloorWidth + CornerLength) * 0.5f,(FloorHeight + CornerLength) * -0.5f });
	wallRB->transform()->setLocalSize({ -1,-1 });

	GameObject* wallLB = createWall();
	wallLB->transform()->setLocalPosition({ (FloorWidth + CornerLength) * -0.5f,(FloorHeight + CornerLength) * -0.5f });
	wallLB->transform()->setLocalSize({ 1,-1 });
}

void Room1x1::InitGenerateBloodRoom()
{
	const TCHAR* bmpKey = TEXT("01_basement");

	auto makePath = [&](TCHAR* dest, const TCHAR* innerPath) -> void
	{
		_tcscpy_s(dest, 256, bmpKey);
		_tcscat_s(dest, 256, innerPath);
	};

	auto createFloor = [&]() -> GameObject*
	{
		TCHAR floorSpritePath[256];
		int floorType = rand() % 2;
		switch (floorType)
		{
			case 0: makePath(floorSpritePath, TEXT("/floor01")); break;
			case 1: makePath(floorSpritePath, TEXT("/floor02")); break;
		}

		GameObject* floor = new GameObject(this->transform());
		floor->transform()->setLocalPosition({});
		SpriteRenderer* floorLTRenderer = floor->AddComponent<SpriteRenderer>();
		floorLTRenderer->setSprite(SpriteManager::instance()->Find(floorSpritePath));
		floorLTRenderer->setRenderTag(RD_TAG_BACKGROUND_FLOOR);
		floorLTRenderer->setRenderOrder(RD_ORDER_BACKGROUND_FLOOR);
		return floor;
	};

	auto createWall = [&]() -> GameObject*
	{
		TCHAR wallSpritePath[256];
		int wallType = 3;
		switch (wallType)
		{
			case 0: makePath(wallSpritePath, TEXT("/wall01")); break;
			case 1: makePath(wallSpritePath, TEXT("/wall02")); break;
			case 2: makePath(wallSpritePath, TEXT("/wall03")); break;
			case 3: makePath(wallSpritePath, TEXT("/wall04")); break;
		}

		GameObject* wall = new GameObject(this->transform());
		SpriteRenderer* wallRenderer = wall->AddComponent<SpriteRenderer>();
		wallRenderer->setSprite(SpriteManager::instance()->Find(wallSpritePath));
		wallRenderer->setRenderTag(RD_TAG_BACKGROUND_WALL);
		wallRenderer->setRenderOrder(RD_ORDER_BACKGROUND_WALL);
		return wall;
	};

	GameObject* floorLT = createFloor();
	floorLT->transform()->setLocalPosition({ -FloorWidth * 0.5f,+FloorHeight * 0.5f });

	GameObject* floorRT = createFloor();
	floorRT->transform()->setLocalPosition({ +FloorWidth * 0.5f,+FloorHeight * 0.5f });
	floorRT->transform()->setLocalSize({ -1,1 });

	GameObject* floorRB = createFloor();
	floorRB->transform()->setLocalPosition({ +FloorWidth * 0.5f,-FloorHeight * 0.5f });
	floorRB->transform()->setLocalSize({ -1,-1 });

	GameObject* floorLB = createFloor();
	floorLB->transform()->setLocalPosition({ -FloorWidth * 0.5f,-FloorHeight * 0.5f });
	floorLB->transform()->setLocalSize({ 1,-1 });

	GameObject* wallLT = createWall();
	wallLT->transform()->setLocalPosition({ (FloorWidth + CornerLength) * -0.5f,(FloorHeight + CornerLength) * 0.5f });

	GameObject* wallRT = createWall();
	wallRT->transform()->setLocalPosition({ (FloorWidth + CornerLength) * 0.5f,(FloorHeight + CornerLength) * 0.5f });
	wallRT->transform()->setLocalSize({ -1,1 });

	GameObject* wallRB = createWall();
	wallRB->transform()->setLocalPosition({ (FloorWidth + CornerLength) * 0.5f,(FloorHeight + CornerLength) * -0.5f });
	wallRB->transform()->setLocalSize({ -1,-1 });

	GameObject* wallLB = createWall();
	wallLB->transform()->setLocalPosition({ (FloorWidth + CornerLength) * -0.5f,(FloorHeight + CornerLength) * -0.5f });
	wallLB->transform()->setLocalSize({ 1,-1 });
}

void Room1x1::InitGenerateDoor(const TCHAR* leftBmpKey, const TCHAR* topBmpKey, const TCHAR* rightBmpKey, const TCHAR* bottomBmpKey)
{
	auto createWallCollider = [&](const Vector2& dir, const float& len, const unsigned char& layer) -> GameObject*
	{
		GameObject* collider = new GameObject(this->transform());
		collider->setLayer(layer);
		LineCollider2D* line = collider->AddComponent<LineCollider2D>();
		line->line()->setDirection(dir);
		line->line()->setLength(len);
		collider->AddComponent<Collider2DRenderer>();
		Body2D* body = collider->AddComponent<Body2D>();
		body->setJustCollider(true);
		body->RegisterCollider(line);
		return collider;
	};

	auto createDoor = [&](const TCHAR* bmpKey) -> Door*
	{
		GameObject* doorObj = new GameObject(this->transform());
		Door* door = doorObj->AddComponent<Door>();
		door->InitGenerate(bmpKey);
		door->InitSetRoom(this);
		return door;
	};

	if (leftBmpKey)
	{
		GameObject* colliderL1 = createWallCollider({ 0,1 }, FloorHeight - 10, GO_LAYER_GROUNDWALL);
		colliderL1->transform()->setLocalPosition({ -FloorWidth, FloorHeight * 0.5f + 5 });
		GameObject* colliderL2 = createWallCollider({ 0,1 }, FloorHeight - 10, GO_LAYER_GROUNDWALL);
		colliderL2->transform()->setLocalPosition({ -FloorWidth, -FloorHeight * 0.5f - 5 });

		m_leftDoor = createDoor(leftBmpKey);
		m_leftDoor->transform()->setLocalPosition({ -FloorWidth - m_leftDoor->height() * 0.25f, 0 });
		m_leftDoor->transform()->setLocalAngle(90 * DEG2RAD);
	}
	else
	{
		GameObject* colliderL = createWallCollider({ 0,1 }, FloorHeight * 2, GO_LAYER_GROUNDWALL);
		colliderL->transform()->setLocalPosition({ -FloorWidth,0 });
	}
	GameObject* projColliderL = createWallCollider({ 0,1 }, FloorHeight * 2 + CornerLength, GO_LAYER_PROJ_WALL);
	projColliderL->transform()->setLocalPosition({ -FloorWidth - CornerLength * 0.5f,0 });
	if (topBmpKey)
	{
		GameObject* colliderT1 = createWallCollider({ 1,0 }, FloorWidth - 10, GO_LAYER_GROUNDWALL);
		colliderT1->transform()->setLocalPosition({ FloorWidth * 0.5f + 5 ,FloorHeight });
		GameObject* colliderT2 = createWallCollider({ 1,0 }, FloorWidth - 10, GO_LAYER_GROUNDWALL);
		colliderT2->transform()->setLocalPosition({ -FloorWidth * 0.5f - 5 ,FloorHeight });

		m_topDoor = createDoor(topBmpKey);
		m_topDoor->transform()->setLocalPosition({ 0, FloorHeight + m_topDoor->height() * 0.25f });
	}
	else
	{
		GameObject* colliderT = createWallCollider({ 1,0 }, FloorWidth * 2, GO_LAYER_GROUNDWALL);
		colliderT->transform()->setLocalPosition({ 0,FloorHeight });
	}
	GameObject* projColliderT = createWallCollider({ 1,0 }, FloorWidth * 2 + CornerLength, GO_LAYER_PROJ_WALL);
	projColliderT->transform()->setLocalPosition({ 0, +FloorHeight + CornerLength * 0.5f });
	if (rightBmpKey)
	{
		GameObject* colliderR1 = createWallCollider({ 0,1 }, FloorHeight - 10, GO_LAYER_GROUNDWALL);
		colliderR1->transform()->setLocalPosition({ FloorWidth, FloorHeight * 0.5f + 5 });
		GameObject* colliderR2 = createWallCollider({ 0,1 }, FloorHeight - 10, GO_LAYER_GROUNDWALL);
		colliderR2->transform()->setLocalPosition({ FloorWidth, -FloorHeight * 0.5f - 5 });

		m_rightDoor = createDoor(rightBmpKey);
		m_rightDoor->transform()->setLocalPosition({ +FloorWidth + m_rightDoor->height() * 0.25f, 0 });
		m_rightDoor->transform()->setLocalAngle(-90 * DEG2RAD);
	}
	else
	{
		GameObject* colliderR = createWallCollider({ 0,1 }, FloorHeight * 2, GO_LAYER_GROUNDWALL);
		colliderR->transform()->setLocalPosition({ FloorWidth,0 });
	}
	GameObject* projColliderR = createWallCollider({ 0,1 }, FloorHeight * 2 + CornerLength, GO_LAYER_PROJ_WALL);
	projColliderR->transform()->setLocalPosition({ +FloorWidth + CornerLength * 0.5f,0 });
	if (bottomBmpKey)
	{
		GameObject* colliderB1 = createWallCollider({ 1,0 }, FloorWidth - 10, GO_LAYER_GROUNDWALL);
		colliderB1->transform()->setLocalPosition({ FloorWidth * 0.5f + 5, -FloorHeight });
		GameObject* colliderB2 = createWallCollider({ 1,0 }, FloorWidth - 10, GO_LAYER_GROUNDWALL);
		colliderB2->transform()->setLocalPosition({ -FloorWidth * 0.5f - 5, -FloorHeight });

		m_bottomDoor = createDoor(bottomBmpKey);
		m_bottomDoor->transform()->setLocalPosition({ 0, -FloorHeight - m_bottomDoor->height() * 0.25f });
		GameObject* bottomDoorParent = new GameObject(m_bottomDoor->transform()->position(), this->transform());
		m_bottomDoor->transform()->setParent(bottomDoorParent->transform());
		bottomDoorParent->transform()->setSize({ 1,-1 });
	}
	else
	{
		GameObject* colliderB = createWallCollider({ 1,0 }, FloorWidth * 2, GO_LAYER_GROUNDWALL);
		colliderB->transform()->setLocalPosition({ 0,-FloorHeight });
	}
	GameObject* projColliderB = createWallCollider({ 1,0 }, FloorWidth * 2 + CornerLength, GO_LAYER_PROJ_WALL);
	projColliderB->transform()->setLocalPosition({ 0, -FloorHeight - CornerLength * 0.5f });

	SetDoorsUseState(false);
	SetDoorsOpen(false);
}

Door* Room1x1::leftDoor() const
{
	return m_leftDoor;
}

Door* Room1x1::topDoor() const
{
	return m_topDoor;
}

Door* Room1x1::rightDoor() const
{
	return m_rightDoor;
}

Door* Room1x1::bottomDoor() const
{
	return m_bottomDoor;
}

void Room1x1::SetDoorsUseState(const bool& canUse)
{
	if (m_leftDoor) m_leftDoor->SetCanUse(canUse);
	if (m_topDoor) m_topDoor->SetCanUse(canUse);
	if (m_rightDoor) m_rightDoor->SetCanUse(canUse);
	if (m_bottomDoor) m_bottomDoor->SetCanUse(canUse);
}

void Room1x1::SetDoorsOpen(const bool& open)
{
	if (open)
	{
		if (m_leftDoor) m_leftDoor->Open();
		if (m_topDoor) m_topDoor->Open();
		if (m_rightDoor) m_rightDoor->Open();
		if (m_bottomDoor) m_bottomDoor->Open();
	}
	else
	{
		if (m_leftDoor) m_leftDoor->Close();
		if (m_topDoor) m_topDoor->Close();
		if (m_rightDoor) m_rightDoor->Close();
		if (m_bottomDoor) m_bottomDoor->Close();
	}
}
