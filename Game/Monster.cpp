#include "stdafx.h"
#include "Monster.h"
#include "MyGameObjectLayer.h"
#include "Room.h"

void Monster::Start()
{
	Character::Start();
}

void Monster::Update()
{
	if (isDead()) return;

	Character::Update();
}

void Monster::LateUpdate()
{
	Character::LateUpdate();
}

void Monster::OnEnable()
{
	Character::OnEnable();
}

void Monster::OnDisable()
{
	Character::OnDisable();
}

void Monster::OnDestroy()
{
	Character::OnDestroy();
}

void Monster::SetRoom(Room* room)
{
	m_room = room;
	transform()->setParent(m_room->transform());
}

Room* Monster::GetRoom() const
{
	return m_room;
}
