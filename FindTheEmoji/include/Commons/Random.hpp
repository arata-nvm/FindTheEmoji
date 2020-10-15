#pragma once
#include <Siv3D.hpp>

class RandomVec {
public:
	static Vec2 RandomScreenPos(const Rect&);

	static Vec2 RandomVelocity(const float);
};
