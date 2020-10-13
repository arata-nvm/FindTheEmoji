#pragma once
#include "Common.hpp"

class GameOver : public MyApp::Scene {
private:
	Rect m_retryButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
	Transition m_retryTransition = Transition(0.4s, 0.2s);

	Rect m_titleButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
	Transition m_titleTransition = Transition(0.4s, 0.2s);

public:
	GameOver(const InitData& init);

	void update() override;

	void draw() const override;
};