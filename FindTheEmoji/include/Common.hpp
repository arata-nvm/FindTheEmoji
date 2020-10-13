#pragma once
#include <Siv3D.hpp>
#include "Ranking.hpp"

enum class State {
	Title,
	Game,
	GameOver
};

struct GameData {
	Seconds timeOfStage = 10s;

	Stopwatch spentTime = Stopwatch(0s);

	int32 sceneTransisionTime = 200;
	
	Ranking ranking = Ranking(U"score.txt");

	int32 lastScore = 0;
};

using MyApp = SceneManager<State, GameData>;