#include "stdafx.h"
#include "EquipItem.h"

EquipItem::EquipItem(Sprite* Sprite)
{
	m_sprite = Sprite;
}

Sprite* EquipItem::sprite() const
{
	return m_sprite;
}
