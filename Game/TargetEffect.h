#pragma once
#ifndef __TargetEffect_h__
#define __TargetEffect_h__

class TargetEffect : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	float m_remainingTime;
	SpriteRenderer* m_renderer;

public:
	void InitSetRemainingTime(const float& time);
};

#endif