#pragma once
#ifndef __LineRenderer_h__
#define __LineRenderer_h__

#include "Renderer2D.h"

class LineRenderer : public Renderer2D
{
protected:
	virtual void LateAwake() override;

private:
	virtual void Render(Camera2D* cam) final override;

protected:
	std::vector<Vector2> m_localVertices;
	std::vector<Vector2> m_worldVertices;

private:
	Vector2 m_min;
	Vector2 m_max;

public:
	void addLocalVertex(const Vector2& localPosition);
	void addWorldVertex(const Vector2& worldPosition);
	void ClearLocalVertex();
	void ClearWorldVertex();
};

#endif
