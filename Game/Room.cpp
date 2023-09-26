#include "stdafx.h"
#include "Room.h"
#include "RoomObstacle.h"
#include "Monster.h"
#include "MyGameObjectLayer.h"
#include "Player.h"
#include "MyRenderTag.h"
#include "SmallPoofAnimator.h"
#include "Item.h"
#include "EquipItemPlacer.h"
#include "SoundMgr.h"

const float Room::FloorWidth = 182;
const float Room::FloorHeight = 104;
const float Room::CornerLength = 52;
const float Room::FloorGridLength = 26;

void Room::Awake()
{
	m_disableCounting = false;
	m_disableEndTime = 0;
	m_disableCountTime = 0;

	SetCxCy(&m_cx, &m_cy);
	m_arrRoomObstacles = new RoomObstacle * [(m_cx * 14) * (m_cy * 8)]{};

	m_enterTriggerObj = new GameObject(this->transform());
	m_enterTriggerObj->setLayer(GO_LAYER_PLAYER_TRIGGERZONE);
	m_enterTriggerObj->transform()->setLocalPosition({});
	m_EnterTrigger = m_enterTriggerObj->AddComponent<RectCollider2D>();
	m_EnterTrigger->setIsTrigger(true);
	m_EnterTrigger->rect()->setWidth(FloorWidth - 15);
	m_EnterTrigger->rect()->setHeight(FloorHeight - 15);
	m_EnterTrigger->OnTriggerCallback += Function<void, Collider2D*>(this, &Room::OnPlayerEnter);
	m_enterTriggerObj->AddComponent<Collider2DRenderer>();
	m_body = m_enterTriggerObj->AddComponent<Body2D>();
	m_body->RegisterCollider(m_EnterTrigger);
	m_body->setJustCollider(true);
}

void Room::Update()
{
	if (m_disableCounting)
	{
		m_disableCountTime += Global::deltaTime;
		if (m_disableCountTime >= m_disableEndTime)
		{
			m_disableCounting = false;
			m_disableEndTime = 0;
			m_disableCountTime = 0;
			gameObject()->setEnable(false);
		}
	}
}

void Room::OnDestroy()
{
	SAFE_DELETE_ARR(m_arrRoomObstacles);
}

void Room::RoomObjEnable()
{
	m_disableCounting = false;
	m_disableEndTime = 0;
	m_disableCountTime = 0;
	gameObject()->setEnable(true);
}

void Room::RoomObjDisableWithTime(const float& time)
{
	m_disableCounting = true;
	m_disableEndTime = time;
	m_disableCountTime = 0;
	if (time == 0)
		gameObject()->setEnable(false);
}

float Room::floorHorizontalLength() const
{
	return m_cx * 2 * FloorWidth;
}

float Room::floorVerticalLength() const
{
	return m_cy * 2 * FloorHeight;
}

float Room::roomHorizontalLength() const
{
	return floorHorizontalLength() + CornerLength * 2;
}

float Room::roomVerticalLength() const
{
	return floorVerticalLength() + CornerLength * 2;
}

float Room::floorLeft() const
{
	return transform()->position().x - floorHorizontalLength() * 0.5f;
}

float Room::floorTop() const
{
	return transform()->position().y + floorVerticalLength() * 0.5f;
}

float Room::floorRight() const
{
	return transform()->position().x + floorHorizontalLength() * 0.5f;
}

float Room::floorBottom() const
{
	return transform()->position().y - floorVerticalLength() * 0.5f;
}

float Room::roomLeft() const
{
	return transform()->position().x - roomHorizontalLength() * 0.5f;
}

float Room::roomTop() const
{
	return transform()->position().y + roomVerticalLength() * 0.5f;
}

float Room::roomRight() const
{
	return transform()->position().x + roomHorizontalLength() * 0.5f;
}

float Room::roomBottom() const
{
	return transform()->position().y - roomVerticalLength() * 0.5f;
}

size_t Room::floorGridCountX() const
{
	return m_cx * 14;
}

size_t Room::floorGridCountY() const
{
	return m_cy * 8;
}

Vector2 Room::floorLeftTop() const
{
	return { floorLeft(),floorTop() };
}

Vector2 Room::floorRightTop() const
{
	return { floorRight(),floorTop() };
}

Vector2 Room::floorRightBottom() const
{
	return { floorRight(),floorBottom() };
}

Vector2 Room::floorLeftBottom() const
{
	return { floorLeft(),floorBottom() };
}

Vector2 Room::roomLeftTop() const
{
	return { roomLeft(),roomTop() };
}

Vector2 Room::roomRightTop() const
{
	return { roomRight(),roomTop() };
}

Vector2 Room::roomRightBottom() const
{
	return { roomRight(),roomBottom() };
}

Vector2 Room::roomLeftBottom() const
{
	return { roomLeft(),roomBottom() };
}

const Vector2& Room::center() const
{
	return transform()->position();
}

Vector2 Room::IndexToCoordOnFloor(const size_t& x, const size_t& y) const
{
	float localPX = (float)x * FloorGridLength + FloorGridLength * 0.5f - floorHorizontalLength() * 0.5f;
	float localPY = -(float)y * FloorGridLength - FloorGridLength* 0.5f + floorVerticalLength() * 0.5f;
	return { localPX + transform()->position().x ,localPY + transform()->position().y };
}

Vector2 Room::CoordToIndexOnFloor(const Vector2& coord) const
{
	float ox = coord.x + floorHorizontalLength() * 0.5f - transform()->position().x;
	float oy = -coord.y + floorVerticalLength() * 0.5f + transform()->position().y;
	int ix = (int)(ox / FloorGridLength);
	int iy = (int)(oy / FloorGridLength);
	return { (float)ix, (float)iy };
}

Vector2 Room::IndexToRoomLeftTopCoord(const int& x, const int& y)
{
	static float OneRoomHorizontalLength = (2 * FloorWidth) + CornerLength * 2;
	static float OneRoomVerticalLength = (2 * FloorHeight) + CornerLength * 2;
	float PX = (float)x * OneRoomHorizontalLength;
	float PY = -(float)y * OneRoomVerticalLength;
	return { PX,PY };
}

Vector2 Room::RoomLeftTopCoordToIndex(const Vector2& roomLeftTopCoord)
{
	static float OneRoomHorizontalLength = (2 * FloorWidth) + CornerLength * 2;
	static float OneRoomVerticalLength = (2 * FloorHeight) + CornerLength * 2;
	return { roomLeftTopCoord.x / OneRoomHorizontalLength , roomLeftTopCoord.y / OneRoomVerticalLength };
}

void Room::SetRoomLeftTop(const Vector2& roomLeftTop)
{
	float centerX = roomLeftTop.x + roomHorizontalLength() * 0.5f;
	float centerY = roomLeftTop.y - roomVerticalLength() * 0.5f;
	transform()->setPosition({ centerX, centerY });
}

void Room::AddObstacle(const size_t& x, const size_t& y, RoomObstacle* obstacle)
{
	if (x >= m_cx * 14 || y >= m_cy * 8)
		return;
	size_t idx = (m_cx * 14) * y + x;
	if (m_arrRoomObstacles[idx] != nullptr)
		return;
	m_arrRoomObstacles[idx] = obstacle;
	obstacle->transform()->setPosition(IndexToCoordOnFloor(x, y));
	obstacle->transform()->setParent(this->transform());
	obstacle->InitSetIndex(x, y);
	obstacle->OnObstacleDestroyedCallback += Function<void, RoomObstacle*>(this, &Room::OnObstacleDestroyed);
}

void Room::AddMonster(const size_t& x, const size_t& y, Monster* monster)
{
	m_monsters.push_back(monster);
	//monster->transform()->setParent(this->transform());
	monster->transform()->setPosition(IndexToCoordOnFloor(x, y));
	monster->gameObject()->setEnable(false);
	monster->SetRoom(this);
	monster->OnDeadCallback += Function<void, Character*>(this, &Room::OnMonsterDead);
}

void Room::AddMonsterAtCenter(Monster* monster)
{
	m_monsters.push_back(monster);
	//monster->transform()->setParent(this->transform());
	monster->transform()->setPosition(center());
	monster->gameObject()->setEnable(false);
	monster->SetRoom(this);
	monster->OnDeadCallback += Function<void, Character*>(this, &Room::OnMonsterDead);
}

void Room::AddItem(const size_t& x, const size_t& y, Item* item)
{
	m_items.push_back(item);
	item->transform()->setParent(this->transform());
	item->transform()->setPosition(IndexToCoordOnFloor(x, y));
	item->gameObject()->setEnable(false);
	item->transform()->setParent(this->transform());
}

void Room::AddItemAtCenter(Item* item)
{
	m_items.push_back(item);
	item->transform()->setParent(this->transform());
	item->transform()->setPosition(center());
	item->gameObject()->setEnable(false);
	item->transform()->setParent(this->transform());
}

void Room::AddEquipItemPlacer(const size_t& x, const size_t& y, EquipItemPlacer* placer)
{
	m_equipItems.push_back(placer);
	placer->transform()->setParent(this->transform());
	placer->transform()->setPosition(IndexToCoordOnFloor(x, y));
	placer->gameObject()->setEnable(false);
	placer->transform()->setParent(this->transform());
}

void Room::AddEquipItemPlacerAtCenter(EquipItemPlacer* placer)
{
	m_equipItems.push_back(placer);
	placer->transform()->setParent(this->transform());
	placer->transform()->setPosition(center());
	placer->gameObject()->setEnable(false);
	placer->transform()->setParent(this->transform());
}

Vector2 Room::GetEmptyGridPosition() const
{
	std::vector<size_t> emptyIdx;
	for (size_t i = 0; i < floorGridCountX() * floorGridCountY(); ++i)
	{
		if (m_arrRoomObstacles[i] == nullptr)
			emptyIdx.push_back(i);
	}
	size_t pickIdx = emptyIdx[rand() % emptyIdx.size()];
	size_t x = pickIdx % floorGridCountX();
	size_t y = pickIdx / floorGridCountX();
	return IndexToCoordOnFloor(x, y);
}

void Room::OnPlayerEnter(Collider2D* collider)
{
	if (collider->isTrigger() == true)
		return;
	Body2D* body = collider->body2D();
	if (body && body == Player::instance()->body())
	{
		m_enterTriggerObj->setEnable(false);
		if (m_monsters.size() > 0)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"summonsound.wav", CSoundMgr::CHANNELID::SUMMON);
			SetDoorsOpen(false);
			SetDoorsUseState(false);
			for (auto& m : m_monsters)
			{
				GameObject* poofEffectObj = new GameObject(m->center());
				SpriteRenderer* effectRenderer = poofEffectObj->AddComponent<SpriteRenderer>();
				effectRenderer->setRenderTag(RD_TAG_EFFECT);
				effectRenderer->setFixedSize(false);
				effectRenderer->setOriginSizeWhenDefixedSize(true);
				poofEffectObj->AddComponent<SmallPoofAnimator>();
				switch (m->size())
				{
					case Character::Size::Small:
						poofEffectObj->transform()->setSize({ 1.25f,1.25f });
						break;
					case Character::Size::Regular:
						poofEffectObj->transform()->setSize({ 2,2 });
						break;
					case Character::Size::Large:
						poofEffectObj->transform()->setSize({ 3,3 });
						break;
				}
				m->gameObject()->setEnable(true);
			}
		}
		else
		{
			SetDoorsOpen(true);
			SetDoorsUseState(true);

			for (auto& i : m_items)
			{
				i->gameObject()->setEnable(true);
			}
			m_items.clear();

			for (auto& i : m_equipItems)
			{
				i->gameObject()->setEnable(true);
			}
			m_equipItems.clear();
		}
	}
}

void Room::OnMonsterDead(Character* monster)
{
	for (auto it = m_monsters.begin(); it != m_monsters.end(); ++it)
	{
		if (monster == *it)
		{
			m_monsters.erase(it);
			if (m_monsters.size() == 0)
			{
				SetDoorsOpen(true);
				SetDoorsUseState(true);

				for (auto& i : m_items)
				{
					i->gameObject()->setEnable(true);
				}
				m_items.clear();

				for (auto& i : m_equipItems)
				{
					i->gameObject()->setEnable(true);
				}
				m_equipItems.clear();
			}
			return;
		}
	}
}

void Room::OnObstacleDestroyed(RoomObstacle* obstacle)
{
	for (size_t i = 0; i < (m_cx * 14) * (m_cy * 8); ++i)
	{
		if (m_arrRoomObstacles[i] == obstacle)
		{
			m_arrRoomObstacles[i] = nullptr;
			obstacle->OnObstacleDestroyedCallback -= Function<void, RoomObstacle*>(this, &Room::OnObstacleDestroyed);
		}
	}
}
