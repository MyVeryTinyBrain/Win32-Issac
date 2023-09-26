#pragma once
#ifndef __EquipItemPlacer_h__
#define __EquipItemPlacer_h__

class Player;
class EquipItem;

class EquipItemPlacer : public Behavior
{
	virtual void SetCanGetItem(bool* pCanGetItem) = 0;
	virtual void SetSprites(Sprite** pDefault, Sprite** pChanged) = 0;
	virtual void SetCollider(Collider2D** pCollider) = 0;
	virtual void SetBody2DProperty(Body2D* body) = 0;
	virtual void Awake() override;
	virtual void LateAwake() = 0;
	virtual void Start() override;
	virtual void Update() override = 0;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Body2D* m_body;
	Collider2D* m_collider;
	SpriteRenderer* m_placerRenderer;

	GameObject* m_itemObj;
	SpriteRenderer* m_itemRenderer;
	EquipItem* m_equipItem;

	bool m_showItem;
	Sprite* m_defaultPlacerSprite;
	Sprite* m_changedPlcaerSprite;

	float m_elapsed;
	bool m_used;

protected:
	bool m_canGetItem;

private:
	void OnCollision(Collider2D* collider);

protected:
	virtual void OnPlayerCollision(Player* player) = 0;
	virtual void GiveAbilityToPlayer(Player* player) = 0;
	void ToShowItem();

public:
	const bool& isShowingItem() const;

	template <typename T>
	void SetEquipItem()
	{
		m_equipItem = new T();
	}
	EquipItem* equipItem() const;
};

#endif
