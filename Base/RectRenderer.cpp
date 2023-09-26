#include "BaseStdafx.h"
#include "RectRenderer.h"

void RectRenderer::LateAwake()
{
	LineRenderer::LateAwake();
	m_width = 1;
	m_height = 1;
	addLocalVertex({ 0,0 });
	addLocalVertex({ 0,0 });
	addLocalVertex({ 0,0 });
	addLocalVertex({ 0,0 });
	addLocalVertex({ 0,0 });
	SetRectVertices();
}

const float& RectRenderer::width() const
{
	return m_width;
}

void RectRenderer::setWidth(const float& Width)
{
	m_width = Width;
	SetRectVertices();
}

const float& RectRenderer::height() const
{
	return m_height;
}

void RectRenderer::setHeight(const float& Height)
{
	m_height = Height;
	SetRectVertices();
}

void RectRenderer::SetRectVertices()
{
	m_localVertices[0] = { -m_width,+m_height };
	m_localVertices[1] = { +m_width,+m_height };
	m_localVertices[2] = { +m_width,-m_height };
	m_localVertices[3] = { -m_width,-m_height };
	m_localVertices[4] = { -m_width,+m_height };
}
