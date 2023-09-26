#pragma once
#ifndef __MouseTracker_h__
#define __MouseTracker_h__

class MouseTracker :public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;
};

#endif
