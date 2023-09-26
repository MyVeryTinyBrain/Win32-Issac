#pragma once
#ifndef __Body2DController_h__
#define __Body2DController_h__

class Body2D;

class Body2DController : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Body2D* m_body2D;
};

#endif
