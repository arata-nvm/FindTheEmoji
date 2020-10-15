#pragma once
#include <Siv3D.hpp>
#include "Chara.hpp"

class Stage
{
private:
	Array<char32> emojis = { U'😀', U'😎', U'🙄' };

	Rect stageRect;

	RenderTexture rt;

	Chara targetChara;

	Array<Chara> otherCharas;

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

	int getCurrentLevel() const;
};

