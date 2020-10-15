#include <Siv3D.hpp>
#include "Commons/Random.hpp"

Vec2 RandomVec::RandomScreenPos(const Rect& stageRect) {
	return Vec2(
		Random(stageRect.x, stageRect.w),
		Random(stageRect.y, stageRect.h)
	);
}

Vec2 RandomVec::RandomVelocity(const float f) {
	return Vec2(
		Random(-f, f),
		Random(-f, f)
	);
}