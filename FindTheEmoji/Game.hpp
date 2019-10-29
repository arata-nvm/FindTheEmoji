#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Common.hpp"
#include "Chara.hpp"
#include "Stage.hpp"

class Game: public MyApp::Scene
{
private:
	Rect stageRect = Rect(0, 0, Scene::Width() - 200, Scene::Height()).stretched(-5);

	Stage stage = Stage(stageRect);

	int level = 1;

	int score = 0;

	Timer timer = Timer(getData().timeOfStage + 2s);

	P2World world;


public:
	Game(const InitData& init);

	void update() override;

	void draw() const override;
};

