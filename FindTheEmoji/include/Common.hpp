#pragma once
#include <Siv3D.hpp>
#include "Commons/Ranking.hpp"

enum class State {
	Title,
	Game,
	GameOver
};

struct GameData {
	Ranking ranking = Ranking(U"score.txt");

	int32 lastScore = 0;


	Stopwatch spentTime = Stopwatch(0s);
};

using MyApp = SceneManager<State, GameData>;

const int32 SceneTrasisionTime = 200;