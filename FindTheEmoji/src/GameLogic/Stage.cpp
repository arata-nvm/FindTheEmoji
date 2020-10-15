﻿#include "GameLogic/Stage.hpp"
#include "Commons/Random.hpp"
#include "Commons/Emojis.hpp"

bool isNear(Point p1, Point p2, int e = 50) {
	return abs(p1.x - p2.x) < e && abs(p1.y - p2.y) < e;
}

Vec2 LerpVec(Rect& stageRect, float fx, float fy) {
	return Vec2(
		stageRect.x + stageRect.w * fx,
		stageRect.y + stageRect.h * fy
	);
}

Stage::Stage(Rect& stageRect) {
	this->stageRect = stageRect;
	this->rt = RenderTexture(stageRect.size, Palette::Black);
}

void Stage::clear() {
	targetChara = Chara();
	otherCharas.clear();
}

void Stage::nextStage() {
	++level;
	this->clear();
	if (level % 10 == 0) {
		emojis = Emojis::RandomEmojis(3);
		Logger.writeln(U"New emoji: {}"_fmt(emojis.join()));
	}

	if (level >= 10 && RandomBool(0.15)) {
		initStageSpecial(level);
		return;
	}

	if (level <= 5 || RandomBool(0.7)) {
		initStageRandom();
	} else  {
		initStageSequence();
	}
}

void Stage::initStageSequence() {
	char32 targetEmoji = emojis.choice();
	Array<char32> otherEmojis = emojis.removed(targetEmoji);

	Vec2 v = Vec2(0, 0);// Random(-1, 1), Random(-1, 1));

	int interval = 10;
	Vec2 add = Vec2(76, 54);

	int numOfChara = interval * interval;
	int numToPlaceTarget = Random(0, numOfChara);
	for (auto i : step(numOfChara)) {
		float x = (i % (interval)) / (float)interval;
		float y = (i / interval) / (float)interval;
		Vec2 location = LerpVec(stageRect, x, y);
		if (i != numToPlaceTarget) {
			otherCharas << Chara(otherEmojis.choice(), location + add, v);
		} else {
			targetChara = Chara(targetEmoji, location + add, v);
		}
	}
}

void Stage::initStageRandom() {
	char32 targetEmoji = emojis.choice();
	Array<char32> otherEmojis = emojis.removed(targetEmoji);

	Vec2 v = RandomVec::RandomVelocity(Min(level / 2 + 1, 3));
	bool changeVelocity = RandomBool();

	targetChara = Chara(targetEmoji, RandomVec::RandomScreenPos(stageRect), v);

	for (auto i : step(Min(level * 3, 50))) {
		if (changeVelocity) {
			v = RandomVec::RandomVelocity(3);
		}
		otherCharas << Chara(otherEmojis.choice(), RandomVec::RandomScreenPos(stageRect), v * (Random() + 0.5));
	}
}

void Stage::initStageSpecial(int mode) {
	if (mode < 0 || mode > 2) mode = Random(0, 2);

	char32 emoji = emojis.choice();
	Vec2 pos, vel;
	switch (mode) {
	case 0:
		pos = RandomVec::RandomScreenPos(stageRect);
		vel = RandomVec::RandomVelocity(1) * 20;
		targetChara = Chara(emoji, pos, vel);
		break;
	case 1:
		pos = Scene::Center().moveBy(-5, -5);
		vel = Vec2(0, 0);
		targetChara = Chara(emoji, pos, vel);
		break;
	case 2:
		pos = Vec2(-35, -35);
		vel = Vec2(0, 0);
		targetChara = Chara(emoji, pos, vel);
		break;
	}

}

void Stage::update() {
	targetChara.update(stageRect);

	for (auto& chara : otherCharas) {
		chara.update(stageRect);
	}

	rt.clear(Palette::Black);
}

bool Stage::isCleared() {
	return MouseL.down() && isNear(Cursor::Pos(), targetChara.pos.asPoint());
}

Chara Stage::getTargetChara() const {
	return targetChara;
}

Array<Chara> Stage::getOtherCharas() const {
	return otherCharas;
}

int Stage::getCurrentLevel() const {
	return level;
}