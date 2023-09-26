#pragma once
#ifndef __RectRenderer_h__
#define __RectRenderer_h__

#include "LineRenderer.h"

class RectRenderer : public LineRenderer
{
	virtual void LateAwake() override;

private:
	float m_width;
	float m_height;

public:
	const float& width() const;
	void setWidth(const float& Width);
	const float& height() const;
	void setHeight(const float& Height);

private:
	void SetRectVertices();
};

#endif