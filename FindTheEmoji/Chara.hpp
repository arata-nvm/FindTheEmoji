#pragma once
#include <Siv3D.hpp>

class Chara {
private:
	void Loop(Vec2* vec, const Rect& stageRect);
public:
	Texture texture;
	Vec2 pos;
	Vec2 velocity;

	Chara();

	Chara(char32 _word, Vec2 _pos, Vec2 _velocity);

	Chara(Texture _texture, Vec2 _pos, Vec2 _velocity);

	void update(const Rect& stage);

	void draw() const;
};