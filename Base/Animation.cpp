#include "BaseStdafx.h"
#include "Animation.h"
#include "SpriteManager.h"

Animation::Animation() : Animation(false)
{
}

Animation::Animation(const bool& loop)
{
	m_totalTime = 0;
	m_sorted = true;
	m_speed = 1;

	m_loop = loop;
}

void Animation::EndEdit()
{
	if (!m_sorted)
	{
		std::sort(m_localPosition.begin(), m_localPosition.end(),
			[](const AnimationNode<Vector2>& a, const AnimationNode<Vector2>& b) -> bool
			{
				return a.time < b.time;
			});
		std::sort(m_localAngle.begin(), m_localAngle.end(),
			[](const AnimationNode<float>& a, const AnimationNode<float>& b) -> bool
			{
				return a.time < b.time;
			});
		std::sort(m_localSize.begin(), m_localSize.end(),
			[](const AnimationNode<Vector2>& a, const AnimationNode<Vector2>& b) -> bool
			{
				return a.time < b.time;
			});
		std::sort(m_sprite.begin(), m_sprite.end(),
			[](const AnimationNode<Sprite*>& a, const AnimationNode<Sprite*>& b) -> bool
			{
				return a.time < b.time;
			});
	}
	m_sorted = true;
	m_totalTime = 0;
	if (m_localPosition.size() > 0 && m_totalTime < m_localPosition.back().time) m_totalTime = m_localPosition.back().time;
	if (m_localAngle.size() > 0 && m_totalTime < m_localAngle.back().time) m_totalTime = m_localAngle.back().time;
	if (m_localSize.size() > 0 && m_totalTime < m_localSize.back().time) m_totalTime = m_localSize.back().time;
	if (m_sprite.size() > 0 && m_totalTime < m_sprite.back().time) m_totalTime = m_sprite.back().time;
}

void Animation::AddLocalPosition(const float& time, const Vector2& localPosition)
{
	m_localPosition.push_back({ time, localPosition });
	if (m_localPosition.size() > 0 && m_localPosition.back().time > time)
		m_sorted = false;
}

void Animation::AddLocalAngle(const float& time, const float& localAngle)
{
	m_localAngle.push_back({ time, localAngle });
	if (m_localAngle.size() > 0 && m_localAngle.back().time > time)
		m_sorted = false;
}

void Animation::AddLocalSize(const float& time, const Vector2& localSize)
{
	m_localSize.push_back({ time, localSize });
	if (m_localSize.size() > 0 && m_localSize.back().time > time)
		m_sorted = false;
}

void Animation::AddSprite(const float& time, Sprite* sprite)
{
	m_sprite.push_back({ time, sprite });
	if (m_sprite.size() > 0 && m_sprite.back().time > time)
		m_sorted = false;
}

bool Animation::GetLocalPosition(float time, Vector2* localPosition)
{
	time *= m_speed;

	if (m_localPosition.size() == 1)
	{
		*localPosition = m_localPosition.front().value;
		return true;
	}
	else if (m_loop == false && time > m_totalTime)
	{
		return false;
	}

	float newTime = time;
	if (m_loop && time > m_totalTime)
		newTime = fmodf(newTime, m_totalTime);

	int index = NextIndexOf(newTime, m_localPosition);
	if (index == -1) return false;

	float delta = m_localPosition[index].time - m_localPosition[index - 1].time;
	float percent = (newTime - m_localPosition[index - 1].time) / delta;
	if (percent < 0) percent = 0;
	else if (percent > 1.0f) percent = 1.0f;
	*localPosition = Vector2::Lerp(m_localPosition[index - 1].value, m_localPosition[index].value, percent);
	return true;
}

bool Animation::GetLocalAngle(float time, float* localAngle)
{
	time *= m_speed;

	if (m_localAngle.size() == 1)
	{
		*localAngle = m_localAngle.front().value;
		return true;
	}
	else if (m_loop == false && time > m_totalTime)
	{
		return false;
	}

	float newTime = time;
	if (m_loop && time > m_totalTime)
		newTime = fmodf(newTime, m_totalTime);

	int index = NextIndexOf(newTime, m_localAngle);
	if (index == -1) return false;

	float delta = m_localAngle[index].time - m_localAngle[index - 1].time;
	float percent = (newTime - m_localAngle[index - 1].time) / delta;
	if (percent < 0) percent = 0;
	else if (percent > 1.0f) percent = 1.0f;
	*localAngle = Lerp(m_localAngle[index - 1].value, m_localAngle[index].value, percent);
	return true;
}

bool Animation::GetLocalSize(float time, Vector2* localSize)
{
	time *= m_speed;

	if (m_localSize.size() == 1)
	{
		*localSize = m_localSize.front().value;
		return true;
	}
	else if (m_loop == false && time > m_totalTime)
	{
		return false;
	}

	float newTime = time;
	if (m_loop && time > m_totalTime)
		newTime = fmodf(newTime, m_totalTime);

	int index = NextIndexOf(newTime, m_localSize);
	if (index == -1) return false;

	float delta = m_localSize[index].time - m_localSize[index - 1].time;
	float percent = (newTime - m_localSize[index - 1].time) / delta;
	if (percent < 0) percent = 0;
	else if (percent > 1.0f) percent = 1.0f;
	*localSize = Vector2::Lerp(m_localSize[index - 1].value, m_localSize[index].value, percent);
	return true;
}

bool Animation::GetSprite(float time, Sprite** sprite)
{
	time *= m_speed;

	if (m_sprite.size() == 1)
	{
		*sprite = m_sprite.front().value;
		return true;
	}
	else if (m_loop == false && time > m_totalTime)
	{
		return false;
	}

	float newTime = time;
	if (m_loop && time > m_totalTime)
		newTime = fmodf(newTime, m_totalTime);

	int index = NextIndexOf(newTime, m_sprite);
	if (index == -1) return false;

	*sprite = m_sprite[index - 1].value;
	return true;
}

bool Animation::IsOvered(float time) const
{
	time *= m_speed;

	return time > m_totalTime;
}

float Animation::GetPercent(float time) const
{
	time *= m_speed;

	float newTime = time;
	return newTime / m_totalTime;
}

const float& Animation::totalTime() const
{
	return m_totalTime;
}

const bool& Animation::isLoop() const
{
	return m_loop;
}

void Animation::setLoop(const bool& enable)
{
	m_loop = enable;
}

const float& Animation::speed() const
{
	return m_speed;
}

void Animation::setSpeed(const float& speed)
{
	m_speed = speed;
}
