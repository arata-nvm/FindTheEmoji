#include <Siv3D.hpp>
#include "Common.hpp"
#include "Title.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "Ranking.hpp"
#include <iostream>

using namespace std;

void Main()
{
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	Window::SetTitle(U"You're an idiot");
	Window::SetFullscreen(true);

	Scene::SetBackground(Palette::Deepskyblue);

	FontAsset::Register(U"Title", 120);
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	FontAsset::Register(U"Score", 36, Typeface::Bold);

	MyApp sceneManager;
	sceneManager
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.add<GameOver>(State::GameOver)
		.setFadeColor(Palette::White);

	// これがないと無駄にした時間が正常な値にならない？
	Stopwatch sw(true);

	while (System::Update())
	{
		if (!sceneManager.update()) {
			break;
		}
	}
}


