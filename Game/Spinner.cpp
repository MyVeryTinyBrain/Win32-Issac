#include "stdafx.h"
#include "Spinner.h"

void Spinner::Awake()
{
}

void Spinner::Start()
{
}

void Spinner::Update()
{
	float a = transform()->localAngle();
	a += speed * Global::deltaTime;
	transform()->setLocalAngle(a);
}

void Spinner::LateUpdate()
{
}

void Spinner::OnEnable()
{
}

void Spinner::OnDisable()
{
}

void Spinner::OnDestroy()
{
}
