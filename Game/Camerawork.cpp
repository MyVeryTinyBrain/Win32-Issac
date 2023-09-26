#include "stdafx.h"
#include "Camerawork.h"
#include "MyExecutionOrder.h"

void Camerawork::Awake()
{
	m_target = nullptr;

	m_useBorder = false;
	m_borderLeft = 0;
	m_borderTop = 0;
	m_borderRight = 0;
	m_borderBottom = 0;

	m_borderLerp = false;
	m_borderLerpLeft = 0;
	m_borderLerpTop = 0;
	m_borderLerpRight = 0;
	m_borderLerpBottom = 0;
	m_borderLerpAccumulated = 0;

	SetExecutionOrder(EX_ORDER_CAMERAWORK);
}

void Camerawork::Start()
{
}

void Camerawork::Update()
{
}

void Camerawork::LateUpdate()
{
	Camera2D* mainCamera = Camera2D::mainCamera();
	if (mainCamera)
	{
		const Vector2& camPos = mainCamera->transform()->position();
		Vector2 newCamPos = Vector2::Lerp(camPos, m_target->position(), 5.0f * Global::deltaTime);
		mainCamera->transform()->setPosition(newCamPos);
	}

	if (m_borderLerp)
	{
		m_borderLerpAccumulated += Global::deltaTime;
		float percent = m_borderLerpAccumulated / m_borderLerpEndTime;
		if (percent > 1)
		{
			percent = 1;
			m_borderLerp = false;
		}
		m_borderLeft = Lerp(m_borderLerpPrevLeft, m_borderLerpLeft, percent);
		m_borderTop = Lerp(m_borderLerpPrevTop, m_borderLerpTop, percent);
		m_borderRight = Lerp(m_borderLerpPrevRight, m_borderLerpRight, percent);
		m_borderBottom = Lerp(m_borderLerpPrevBottom, m_borderLerpBottom, percent);
	}

	if (m_useBorder && mainCamera)
	{
		const Vector2& camPos = mainCamera->transform()->position();
		Vector2 newCamPos = camPos;
		float width = m_borderRight - m_borderLeft;
		float height = m_borderTop - m_borderBottom;
		if (width <= mainCamera->horizontal())
		{
			newCamPos.x = (m_borderLeft + m_borderRight) * 0.5f;
		}
		else
		{
			float camLeft = camPos.x - mainCamera->halfWidth();
			float camRight = camPos.x + mainCamera->halfWidth();
			if (camLeft < m_borderLeft) newCamPos.x = m_borderLeft + mainCamera->halfWidth();
			else if (camRight > m_borderRight) newCamPos.x = m_borderRight - mainCamera->halfWidth();
		}
		if (height <= mainCamera->vertical())
		{
			newCamPos.y = (m_borderTop + m_borderBottom) * 0.5f;
		}
		else
		{
			float camBottom = camPos.y - mainCamera->halfHeight();
			float camTop = camPos.y + mainCamera->halfHeight();
			if (camBottom < m_borderBottom) newCamPos.y = m_borderBottom + mainCamera->halfHeight();
			else if (camTop > m_borderTop) newCamPos.y = m_borderTop - mainCamera->halfHeight();
		}
		mainCamera->transform()->setPosition(newCamPos);
	}
}

void Camerawork::OnEnable()
{
}

void Camerawork::OnDisable()
{
}

void Camerawork::OnDestroy()
{
}

void Camerawork::SetTarget(Transform* target)
{
	m_target = target;
}

void Camerawork::SetUseBorder(const bool& enable)
{
	m_useBorder = enable;
}

void Camerawork::SetBorder(const float& left, const float& top, const float& right, const float& bottom)
{
	m_borderLeft = left;
	m_borderTop = top;
	m_borderRight = right;
	m_borderBottom = bottom;
}

void Camerawork::LerpBorder(const float& left, const float& top, const float& right, const float& bottom, const float& t)
{
	m_borderLerp = true;
	m_borderLerpPrevLeft = m_borderLeft;
	m_borderLerpPrevTop = m_borderTop;
	m_borderLerpPrevRight = m_borderRight;
	m_borderLerpPrevBottom = m_borderBottom;
	m_borderLerpLeft = left;
	m_borderLerpTop = top;
	m_borderLerpRight = right;
	m_borderLerpBottom = bottom;
	m_borderLerpAccumulated = 0;
	m_borderLerpEndTime = t;
}

float Camerawork::Lerp(const float& start, const float& end, const float& t)
{
	return start + (end - start) * t;
}
