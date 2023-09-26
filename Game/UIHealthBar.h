#pragma once
#ifndef __UIHealthBar_h__
#define __UIHealthBar_h__

class Character;

class UIHealthBar : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	SpriteRenderer* m_skull;
	GameObject* m_hpObj;
	float m_hpWidth;
	SpriteRenderer* m_hp;
	SpriteRenderer* m_bar;

	Character* m_target;

	float m_hideCounter;

public:
	void AddTarget(Character* character);
	void ClearTargets();

private:
	void OnTargetDead(Character* character);

private:
	static UIHealthBar* g_healthBar;

public:
	static UIHealthBar* instance();
};

#endif
