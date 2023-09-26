#include "BaseStdafx.h"
#include "Renderer2D.h"
#include "Camera2D.h"
#include "Transform.h"
#include "HDCEx.h"
#include "Renderer2DTag.h"
#include "Renderer2DOrder.h"
#include "ExecutionOrder.h"

void Renderer2D::Awake()
{
	m_isRenderer = true;
	m_renderTag = RD_TAG_DEFAULT;
	m_renderOrder = RD_ORDER_DEFAULT;

	m_yOrder = false;
	m_yOrderAdjustment = 0;

	SetExecutionOrder(EX_ORDER_RENDERER);

	LateAwake();
}

void Renderer2D::Start()
{
}

void Renderer2D::Update()
{
}

void Renderer2D::LateUpdate()
{
	if (m_yOrder)
	{
		m_renderOrder = (int)(transform()->position().y) + (int)m_yOrderAdjustment;
	}
}

const unsigned char& Renderer2D::renderTag() const
{
	return m_renderTag;
}

void Renderer2D::setRenderTag(unsigned char tag)
{
	m_renderTag = tag;
}

const int& Renderer2D::renderOrder() const
{
	return m_renderOrder;
}

void Renderer2D::setRenderOrder(int renderOrder)
{
	m_renderOrder = renderOrder;
}

void Renderer2D::OnEnable()
{
}

void Renderer2D::OnDisable()
{
}

void Renderer2D::OnDestroy()
{
}

const bool& Renderer2D::yOrder() const
{
	return m_yOrder;
}

void Renderer2D::setYOrder(const bool& enable)
{
	m_yOrder = enable;
}

const float& Renderer2D::yOrderAdjustment() const
{
	return m_yOrderAdjustment;
}

void Renderer2D::setYOrderAdjustment(const float& yAdjustment)
{
	m_yOrderAdjustment = yAdjustment;
}
