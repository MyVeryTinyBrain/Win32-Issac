#pragma once
#ifndef __Resizer_h__
#define __Resizer_h__

class Resizer : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

public:
	float speed_x = 5;
	float speed_y = 2.5f;
};

#endif
