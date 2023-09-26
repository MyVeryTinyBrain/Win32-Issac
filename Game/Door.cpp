#include "stdafx.h"
#include "Door.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"
#include "KeyAnimator.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "SideDoorAnimator.h"
#include "DoorPoppingAnimator.h"
#include "Camerawork.h"
#include "Room.h"
#include "ResourceLoader.h"

void Door::Awake()
{
}

void Door::Start()
{
}

void Door::Update()
{
}

void Door::LateUpdate()
{
}

void Door::OnEnable()
{
}

void Door::OnDisable()
{
}

void Door::OnDestroy()
{
}

const float& Door::height() const
{
	return m_height;
}

const float& Door::width() const
{
	return m_width;
}

void Door::Lock()
{
	if (m_locked) return;
	m_locked = true;
	m_rightDoorAnimator->setEnable(false);
	m_rightLockedDoorAnimator->setEnable(true);
	Close();

	if (m_exit) m_exit->Lock();
}

void Door::Unlock()
{
	if (!m_locked) return;
	m_locked = false;
	if (m_unlockAnimator->gameObject()->active() && m_unlockAnimator->enable()) m_unlockAnimator->Play();
	else Open();
	m_rightDoorAnimator->setEnable(false);
	m_rightLockedDoorAnimator->setEnable(true);

	if (m_exit) m_exit->Unlock();
}

const bool& Door::isLocked() const
{
	return m_locked;
}

void Door::Open()
{
	if (m_opened || m_locked || m_unlockAnimator->isPlayingUnlockAnimation()) return;
	m_opened = true;
	m_locked = false;
	if (m_poppingAnimator->gameObject()->active() && m_poppingAnimator->enable()) m_poppingAnimator->Play();
	else OnPoppingAnimated();

	if (m_exit) m_exit->Open();
}

void Door::Close()
{
	if (!m_opened || m_locked) return;
	m_opened = false;
	m_rightDoorAnimator->setEnable(true);
	m_rightLockedDoorAnimator->setEnable(false);
	m_leftDoorAnimator->PlayClose();
	m_rightDoorAnimator->PlayClose();
	m_rightLockedDoorAnimator->PlayClose();
	m_entranceCollider->gameObject()->setEnable(true);

	if (m_exit) m_exit->Close();
}

const bool& Door::isOpened() const
{
	return m_opened;
}

Door* Door::exitDoor() const
{
	return nullptr;
}

void Door::Connect(Door* exitDoor)
{
	m_exit = exitDoor;
	m_exitDirection = (transform()->position() - exitDoor->transform()->position()).normalized();

	exitDoor->m_exit = this;
	exitDoor->m_exitDirection = -1 * m_exitDirection;
}

void Door::SetCanUse(const bool& canUse)
{
	if (m_canUse == canUse) return;
	m_canUse = canUse;
	if (m_exit) m_exit->SetCanUse(canUse);
}

void Door::InitGenerate(const TCHAR* bmpKey)
{
	auto createSpriteObject = [&](const TCHAR* spritePath, const unsigned char& order) -> GameObject*
	{
		GameObject* obj = new GameObject(this->transform());
		obj->transform()->setLocalPosition({});
		SpriteRenderer* renderer = obj->AddComponent<SpriteRenderer>();
		renderer->setSprite(SpriteManager::instance()->Find(spritePath));
		renderer->setRenderTag(RD_TAG_BACKGROUND_OBJ);
		renderer->setRenderOrder(order);
		renderer->setFixedSize(false);
		return obj;
	};

	auto createSpriteObject2 = [&](const unsigned char& order) -> GameObject*
	{
		GameObject* obj = new GameObject(this->transform());
		obj->transform()->setLocalPosition({});
		SpriteRenderer* renderer = obj->AddComponent<SpriteRenderer>();
		renderer->setRenderTag(RD_TAG_BACKGROUND_OBJ);
		renderer->setRenderOrder(order);
		renderer->setFixedSize(false);
		return obj;
	};

	GameObject* inside = createSpriteObject(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("inside")), RD_ORDER_BACKGROUND_OBJ_DOOR_INSIDE);
	inside->transform()->setLocalPosition(Vector2(0, +1));

	Sprite* left1 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("left1")));
	Sprite* left2 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("left2")));
	Sprite* left3 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("left3")));
	Sprite* left4 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("left4")));
	GameObject* leftDoor = createSpriteObject2(RD_ORDER_BACKGROUND_OBJ_DOOR_LEFT);
	leftDoor->transform()->setLocalPosition(Vector2(0, -2));
	m_leftDoorAnimator = leftDoor->AddComponent<DoorSideAnimator>();
	m_leftDoorAnimator->InitSetDoorSprite(left1, left2, left3, left4);

	Sprite* right1 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right1")));
	Sprite* right2 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right2")));
	Sprite* right3 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right3")));
	Sprite* right4 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right4")));
	Sprite* rightlocked1 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right_locked1")));
	Sprite* rightlocked2 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right_locked2")));
	Sprite* rightlocked3 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right_locked3")));
	Sprite* rightlocked4 = SpriteManager::Find(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("right_locked4")));
	GameObject* rightDoor = createSpriteObject2(RD_ORDER_BACKGROUND_OBJ_DOOR_RIGHT);
	rightDoor->transform()->setLocalPosition(Vector2(0, -2));
	m_rightDoorAnimator = rightDoor->AddComponent<DoorSideAnimator>();
	m_rightDoorAnimator->InitSetDoorSprite(right1, right2, right3, right4);
	m_rightLockedDoorAnimator = rightDoor->AddComponent<DoorSideAnimator>();
	m_rightLockedDoorAnimator->InitSetDoorSprite(rightlocked1, rightlocked2, rightlocked3, rightlocked4);
	m_rightLockedDoorAnimator->setEnable(false);

	m_poppingAnimator = gameObject()->AddComponent<DoorPoppingAnimator>();
	m_poppingAnimator->OnAnimated += Function<void>(this, &Door::OnPoppingAnimated);

	GameObject* doorFrame = createSpriteObject(ResourceLoader::MakeSpriteKey(bmpKey, TEXT("frame")), RD_ORDER_BACKGROUND_OBJ_DOOR_FRAME);
	doorFrame->transform()->setLocalPosition(Vector2(0, +1));

	m_height = doorFrame->GetComponent<SpriteRenderer>()->sprite()->height();
	m_width = doorFrame->GetComponent<SpriteRenderer>()->sprite()->width();

	GameObject* triggerObj = new GameObject(this->transform());
	triggerObj->transform()->setLocalPosition({ 0,15 });
	m_trigger = triggerObj->AddComponent<RectCollider2D>();
	m_trigger->setIsTrigger(true);
	triggerObj->setLayer(GO_LAYER_DOOR);
	m_trigger->rect()->setHeight(5);
	m_trigger->rect()->setWidth(10);
	m_trigger->OnTriggerCallback += Function<void, Collider2D*>(this, &Door::OnTrigged);
	triggerObj->AddComponent<Collider2DRenderer>();

	GameObject* entranceColliderObj = new GameObject(this->transform());
	entranceColliderObj->setLayer(GO_LAYER_GROUNDWALL);
	m_entranceCollider = entranceColliderObj->AddComponent<LineCollider2D>();
	m_entranceCollider->line()->setLength(20);
	m_entranceCollider->transform()->setLocalPosition({ 0,-13 });
	m_entranceCollider->OnCollisionCallback += Function<void, Collider2D*>(this, &Door::OnCollision);
	entranceColliderObj->AddComponent<Collider2DRenderer>();

	GameObject* entranceHoleColliderObj1 = new GameObject(this->transform());
	entranceHoleColliderObj1->setLayer(GO_LAYER_GROUNDWALL);
	entranceHoleColliderObj1->transform()->setLocalPosition({ 10,-2 });
	entranceHoleColliderObj1->transform()->setLocalAngle(90 * DEG2RAD);
	LineCollider2D* line1 = entranceHoleColliderObj1->AddComponent<LineCollider2D>();
	line1->line()->setLength(21);
	entranceHoleColliderObj1->AddComponent<Collider2DRenderer>();

	GameObject* entranceHoleColliderObj2 = new GameObject(this->transform());
	entranceHoleColliderObj2->setLayer(GO_LAYER_GROUNDWALL);
	entranceHoleColliderObj2->transform()->setLocalPosition({ -10,-2 });
	entranceHoleColliderObj2->transform()->setLocalAngle(90 * DEG2RAD);
	LineCollider2D* line2 = entranceHoleColliderObj2->AddComponent<LineCollider2D>();
	line2->line()->setLength(21);
	entranceHoleColliderObj2->AddComponent<Collider2DRenderer>();

	m_body = gameObject()->AddComponent<Body2D>();
	m_body->setJustCollider(true);
	m_body->RegisterCollider(m_trigger);
	m_body->RegisterCollider(m_entranceCollider);
	m_body->RegisterCollider(line1);
	m_body->RegisterCollider(line2);

	GameObject* unlockAnimatorObj = new GameObject(this->transform());
	SpriteRenderer* unlockRenderer = unlockAnimatorObj->AddComponent<SpriteRenderer>();
	unlockRenderer->setRenderOrder(RD_ORDER_EFFECT_UNLOCK);
	unlockRenderer->setRenderTag(RD_TAG_EFFECT);
	unlockAnimatorObj->transform()->setLocalPosition({});
	m_unlockAnimator = unlockAnimatorObj->AddComponent<KeyAnimator>();
	m_unlockAnimator->OnAnimated += Function<void>(this, &Door::OnUnlockAnimated);

	m_opened = true;
	m_locked = false;

	Close();
	//Lock();
}

void Door::InitSetRoom(Room* room)
{
	m_room = room;
}

Room* Door::GetRoom() const
{
	return m_room;
}

void Door::OnPoppingAnimated()
{
	m_leftDoorAnimator->PlayOpen();
	m_rightDoorAnimator->PlayOpen();
	m_rightLockedDoorAnimator->PlayOpen();
	m_entranceCollider->gameObject()->setEnable(false);
}

void Door::OnUnlockAnimated()
{
	Open();
}

void Door::OnTrigged(Collider2D* collider)
{
	if (!m_canUse) return;
	if (m_exit && collider->gameObject()->layer() == GO_LAYER_PLAYER)
	{
		Transform* playerTrs = collider->transform()->parent();
		if (playerTrs)
		{
			if(!m_locked)
			{
				Player* player = Player::instance();
				const Vector2& vel = player->body()->velocity();
				float dot = Vector2::Dot(m_exit->m_exitDirection, vel);
				if (dot > 0)
				{
					playerTrs->setPosition(m_exit->transform()->position() + m_exit->m_exitDirection * 1);

					Camera2D* mainCam = Camera2D::mainCamera();
					Camerawork* camwork = mainCam->gameObject()->GetComponent<Camerawork>();
					Room* exitRoom = m_exit->m_room;
					camwork->LerpBorder(exitRoom->roomLeft(), exitRoom->roomTop(), exitRoom->roomRight(), exitRoom->roomBottom(), 0.2f);

					m_room->RoomObjDisableWithTime(0.2f);
					m_exit->m_room->RoomObjEnable();
				}
			}
		}
	}
}

void Door::OnCollision(Collider2D* collider)
{
	if (!m_canUse) return;
	if (m_exit && collider->gameObject()->layer() == GO_LAYER_PLAYER)
	{
		GameObject* obj = collider->body2D()->gameObject();
		Player* player = Player::instance();
		if (obj == player->gameObject())
		{
			size_t keyCount = player->key();
			if (m_locked && keyCount > 0)
			{
				player->setKey(keyCount - 1);
				Unlock();
			}
		}
	}
}
