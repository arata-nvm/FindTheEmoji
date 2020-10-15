#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Common.hpp"
#include "GameLogic/Chara.hpp"
#include "GameLogic/Stage.hpp"

class Game: public MyApp::Scene
{
private:
	Rect stageRect = Rect(0, 0, Scene::Width() - 200, Scene::Height()).stretched(-5);
	RenderTexture rt = RenderTexture(stageRect.size, Palette::Black);

	Stage stage = Stage(stageRect);

	int level = 1;

	int score = 0;

	Seconds timeOfStage = 10s;

	Timer timer = Timer(timeOfStage + 2s);

	P2World world;

	void drawUI() const;

	void drawStage() const;

public:
	Game(const InitData& init);

	void update() override;

	void draw() const override;
};

