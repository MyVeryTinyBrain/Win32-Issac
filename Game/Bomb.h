#pragma once
#ifndef __Bomb_h__
#define __Bomb_h__

class Bomb : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	GameObject* m_rendererObj;
	SpriteRenderer* m_renderer;
	float m_delay;
	float m_accumulated;
};

#endif