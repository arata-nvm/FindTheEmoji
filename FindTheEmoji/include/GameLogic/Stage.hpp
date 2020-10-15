#pragma once
#include <Siv3D.hpp>
#include "Chara.hpp"
#include "GameLogic/Phase.hpp"

class Stage
{
private:
	Array<char32> emojis = { U'😀', U'😎', U'🙄' };

	Rect stageRect;

	Chara targetChara;
	Array<Chara> otherCharas;

	Seconds timeOfStage = 10s;
	Timer timer = Timer(timeOfStage + 2s);

	int level = 0;

public:
	Stage(Rect&);

	void clear();

	void nextStage();

	void initStageSequence();

	void initStageRandom();

	void initStageSpecial(int = -1);

	void update();

	bool isCleared();

	Chara getTargetChara() const;

	Array<Chara> getOtherCharas() const;

	Phase getCurrentPhase() const;

	int32 getRemainingTime() const;

	int getCurrentLevel() const;
};

