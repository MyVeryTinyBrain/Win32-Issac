#pragma once
#ifndef __Spinner_h__
#define __Spinner_h___

class Spinner : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

public:
	float speed = 10;
};

#endif
