#pragma once
#ifndef __Animation_h__
#define __Animation_h__

class Sprite;

template <typename T>
struct AnimationNode
{
	float time;
	T value;
};

class Animation
{
	float m_totalTime;
	bool m_sorted;
	float m_speed;

	std::vector<AnimationNode<Vector2>> m_localPosition;
	std::vector<AnimationNode<float>> m_localAngle;
	std::vector<AnimationNode<Vector2>> m_localSize;
	std::vector<AnimationNode<Sprite*>> m_sprite;

	bool m_loop;

public:
	Animation();
	Animation(const bool& loop);

	// 각 타임라인을 시간순으로 정렬하고 애니메이션 총 시간을 계산합니다.
	void EndEdit();

	void AddLocalPosition(const float& time, const Vector2& localPosition);
	void AddLocalAngle(const float& time, const float& localAngle);
	void AddLocalSize(const float& time, const Vector2& localSize);
	void AddSprite(const float& time, Sprite* sprite);

	bool GetLocalPosition(float time, Vector2* localPosition);
	bool GetLocalAngle(float time, float* localAngle);
	bool GetLocalSize(float time, Vector2* localSize);
	bool GetSprite(float time, Sprite** sprite);

	bool IsOvered(float time) const;
	float GetPercent(float time) const;

	const float& totalTime() const;
	const bool& isLoop() const;
	void setLoop(const bool& enable);

	const float& speed() const;
	void setSpeed(const float& speed);

private:
	template <typename T>
	int NextIndexOf(const float& time, const std::vector<AnimationNode<T>>& vec);
	inline float Lerp(const float& start, const float& end, const float& t)
	{
		return start + (end - start) * t;
	}
};

template <typename T>
int Animation::NextIndexOf(const float& time, const std::vector<AnimationNode<T>>& vec)
{
	if (vec.size() == 0) return -1;
	if (vec.size() == 1) return 0;
	if (!m_sorted) EndEdit();
	size_t min = 0;
	size_t max = vec.size() - 1;
	while (max - min > 1)
	{
		size_t mid = (min + max) / 2;
		if (vec[mid].time < time)
		{
			min = mid;
		}
		else if(vec[mid].time > time)
		{
			max = mid;
		}
		else
		{
			return mid;
		}
	}
	return max;
}

#endif
