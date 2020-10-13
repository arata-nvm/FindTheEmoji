#include "Chara.hpp"
#include "Emojis.hpp"

Chara::Chara() {}

Chara::Chara(char32 _word, Vec2 _pos, Vec2 _velocity) {
	this->texture = Emojis::getEmojiTexture(_word);
	this->pos = _pos;
	this->velocity = _velocity;
}

Chara::Chara(Texture _texture, Vec2 _pos, Vec2 _velocity) {
	this->texture = _texture;
	this->pos = _pos;
	this->velocity = _velocity;
}

void Chara::update(const Rect& stage) {
	pos += velocity;
	Loop(&pos, stage);
}

void Chara::Loop(Vec2* vec, const Rect& stageRect) {
	int tw = texture.width() / 2;
	int th = texture.height() / 2;
	if (vec->x + tw < stageRect.x) vec->x = stageRect.w + tw;
	if (vec->y + th < stageRect.y) vec->y = stageRect.h + th;
	if (vec->x - tw > stageRect.w) vec->x = stageRect.x - tw;
	if (vec->y - th > stageRect.h) vec->y = stageRect.y - th;
}

void Chara::draw() const {
	texture.drawAt(pos);
}