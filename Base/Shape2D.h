#pragma once
#ifndef __Shape2D_h__
#define __Shape2D_h__

class Shape2D
{
	// World position
	Vector2 m_position;
	// World angle
	float m_angle; // Radian
	// World Size
	Vector2 m_size;

protected:
	size_t m_vertexCount;
	// Local vertices
	Vector2* m_vertices;

private:
	// Local radius
	float m_radius;

public:
	Shape2D(const size_t& vertexCount, const float& radius);
	virtual ~Shape2D();

	virtual void UpdateShape() = 0;

	const Vector2& worldPosition() const;
	void setWorldPosition(const Vector2& worldPosition);
	const float& worldAngle() const;
	void setWorldAngle(const float& radian);
	const Vector2& worldSize() const;
	void setWorldSize(const Vector2& size);
	const float& radius() const;
	void setRadius(const float& radius);
	void setWorldTransform(const Vector2& worldPosition, const float& radian, const Vector2& size);
	const size_t& vertexCount() const;
	const Vector2& vertex(const size_t& index) const;

protected:
	Vector2* vertices() const;
};

#endif
