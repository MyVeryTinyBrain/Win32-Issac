#pragma once
#ifndef __Controller_h__
#define __Controller_h__

class Camera2D;

class Controller : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Camera2D* cam;
};

#endif
