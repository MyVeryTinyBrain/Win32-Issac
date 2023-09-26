#pragma once
#ifndef __TestReferencingComponent
#define __TestReferencingComponent

class TestReferencingComponent : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

	void OnObjectDestroy(Object* object);

private:
	GameObject* m_refGameObject;
	Component* m_refComponent;

public:
	void setGameObject(GameObject* go);
	void setComponent(Component* comp);
};

#endif
