#pragma once
#ifndef __Animator_h__
#define __Animator_h__

#include "Behavior.h"

class Animation;
class SpriteRenderer;

class Animator : public Behavior
{
	virtual void Awake() final override;
	virtual void Start() final override;
	virtual void Update() final override;
	virtual void LateUpdate() final override;
	virtual void OnEnable() final override;
	virtual void OnDisable() final override;
	virtual void OnDestroy() final override;

protected:
	virtual void OnAwake() = 0;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) = 0;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) = 0;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) = 0;
	virtual void OnPrevDestroy() = 0;

protected:
	float m_elapsed = 0;
	bool m_useUnscaledDeltaTime = false;
	Animation* m_defaultAnimation = nullptr;
	Animation* m_curAnimation = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;

public:
	void SetDefaultAnimation(Animation* animation);
	void PlayAnimation(Animation* animation, bool keepElapsedTime = false);
	void SetSpriteRenderer(SpriteRenderer* spriteRenderer);

private:
	void OnSpriteRendererDestroy(Object* obj);

protected:
	void setDefaultAnimation(Animation* animation);
};

#endif
