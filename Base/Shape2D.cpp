#include "BaseStdafx.h"
#include "Shape2D.h"

Shape2D::Shape2D(const size_t& vertexCount, const float& radius)
{
	m_position = Vector2::zero();
	m_angle = 0;
	m_size = Vector2::one();

	m_vertexCount = vertexCount;
	m_vertices = new Vector2[vertexCount];
	m_radius = radius;
}

Shape2D::~Shape2D()
{
	BASE_SAFE_DELETE_ARR(m_vertices);
}

const Vector2& Shape2D::worldPosition() const
{
	return m_position;
}

void Shape2D::setWorldPosition(const Vector2& worldPosition)
{
	if (m_position == worldPosition) return;
	m_position = worldPosition;
	UpdateShape();
}

const float& Shape2D::worldAngle() const
{
	return m_angle;
}

void Shape2D::setWorldAngle(const float& radian)
{
	if (m_angle == radian) return;
	m_angle = radian;
	UpdateShape();
}

const Vector2& Shape2D::worldSize() const
{
	return m_size;
}

void Shape2D::setWorldSize(const Vector2& size)
{
	if (m_size == size) return;
	m_size = size;
	UpdateShape();
}

const float& Shape2D::radius() const
{
	return m_radius;
}

void Shape2D::setRadius(const float& radius)
{
	if (m_radius == radius) return;
	m_radius = radius;
	UpdateShape();
}

void Shape2D::setWorldTransform(const Vector2& worldPosition, const float& radian, const Vector2& size)
{
	if (m_position == worldPosition && m_angle == radian && m_size == size) return;
	m_position = worldPosition;
	m_angle = radian;
	m_size = size;
	UpdateShape();
}

const size_t& Shape2D::vertexCount() const
{
	return m_vertexCount;
}

const Vector2& Shape2D::vertex(const size_t& index) const
{
	return m_vertices[index];
}

Vector2* Shape2D::vertices() const
{
	return m_vertices;
}
