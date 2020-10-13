#pragma once
#include "Common.hpp"
#include "GameLogic/Chara.hpp"

class Title : public MyApp::Scene {
private:
	const Rect m_startButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
	Transition m_startTransition = Transition(0.4s, 0.2s);

	const Rect m_exitButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
	Transition m_exitTransition = Transition(0.4s, 0.2s);

	const Rect screenRect = Rect(0, 0, Scene::Width(), Scene::Height());
	Array<Chara> charas;

public:
	Title(const InitData& init);

	void update() override;

	void draw() const override;
};