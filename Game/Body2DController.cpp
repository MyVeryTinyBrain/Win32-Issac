#include "stdafx.h"
#include "Body2DController.h"

void Body2DController::Awake()
{
	m_body2D = gameObject()->GetComponent<Body2D>();
}

void Body2DController::Start()
{
}

void Body2DController::Update()
{
	float speed = 500.0f;
	Vector2 dir = {};
	if (Input::GetKey(Key::Y))
		dir.y += 1;
	if (Input::GetKey(Key::H))
		dir.y -= 1;
	if (Input::GetKey(Key::G))
		dir.x -= 1;
	if (Input::GetKey(Key::J))
		dir.x += 1;
	dir.Normalize();
	m_body2D->AddImpulseToSpeed(dir, speed);
}

void Body2DController::LateUpdate()
{
}

void Body2DController::OnEnable()
{
}

void Body2DController::OnDisable()
{
}

void Body2DController::OnDestroy()
{
}
