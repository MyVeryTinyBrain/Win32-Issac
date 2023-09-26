#pragma once
#ifndef __Collider2D_h__
#define __Collider2D_h__

#include "Behavior.h"
#include "Delegate.h"

class Shape2D;
class Body2D;

class Collider2D : public Behavior
{
	friend class Body2D;

private:
	virtual void Awake() final override;
	virtual void Start() final override;
	virtual void Update() final override;
	virtual void LateUpdate() final override;
	virtual void OnEnable() final override;
	virtual void OnDisable() final override;
	virtual void OnDestroy() final override;

protected:
	virtual void SetShape2DOnAwake(Shape2D** pColliderShape2D) = 0;

private:
	Shape2D* m_shape2D = nullptr;
	bool m_isTrigger = false;

	Body2D* m_body2D = nullptr;

public:
	void UpdateShapeVertices();

	Shape2D* shape2D() const;
	const bool& isTrigger() const;
	void setIsTrigger(const bool& IsTrigger);

	Body2D* body2D() const;

	Delegate<void, Collider2D*> OnCollisionCallback;
	Delegate<void, Collider2D*> OnTriggerCallback;
};

#endif
