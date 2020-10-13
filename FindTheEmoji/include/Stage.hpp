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


public:
	Stage(Rect&);

	void clear();

	void initStage(int);

	void initStageSequence(int);

	void initStageRandom(int);

	void initStageSpecial(int, int = -1);

	void shuffleEmoji();

	void update();

	void draw() const;

	void drawStage() const;

	void drawTargetAtCenter() const;

	bool isCleared();

	Chara getTargetChara() const;
};

