#pragma once
#ifndef __TestRemover_h__
#define __TestRemover_h__

class TestRemover : public Behavior
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
