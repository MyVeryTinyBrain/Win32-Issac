#include "stdafx.h"
#include "TestReferencingComponent.h"

void TestReferencingComponent::Awake()
{
	m_refGameObject = nullptr;
	m_refComponent = nullptr;
}

void TestReferencingComponent::Start()
{
}

void TestReferencingComponent::Update()
{
}

void TestReferencingComponent::LateUpdate()
{
}
void TestReferencingComponent::OnEnable()
{
}

void TestReferencingComponent::OnDisable()
{
	if (m_refGameObject)
		m_refGameObject->OnDestroyCallback -= Function<void, Object*>(this, &TestReferencingComponent::OnObjectDestroy);
	if (m_refComponent)
		m_refComponent->OnDestroyCallback -= Function<void, Object*>(this, &TestReferencingComponent::OnObjectDestroy);
}

void TestReferencingComponent::OnDestroy()
{
}

void TestReferencingComponent::OnObjectDestroy(Object* object)
{
	if (object == m_refComponent)
		m_refComponent = nullptr;
	else if (object == m_refGameObject)
		m_refGameObject = nullptr;
}

void TestReferencingComponent::setGameObject(GameObject* go)
{
	if (m_refGameObject)
		m_refGameObject->OnDestroyCallback -= Function<void, Object*>(this, &TestReferencingComponent::OnObjectDestroy);
	go->OnDestroyCallback += Function<void, Object*>(this, &TestReferencingComponent::OnObjectDestroy);
	m_refGameObject = go;
}

void TestReferencingComponent::setComponent(Component* comp)
{
	if (m_refComponent)
		m_refComponent->OnDestroyCallback -= Function<void, Object*>(this, &TestReferencingComponent::OnObjectDestroy);
	comp->OnDestroyCallback += Function<void, Object*>(this, &TestReferencingComponent::OnObjectDestroy);
	m_refComponent = comp;
}
