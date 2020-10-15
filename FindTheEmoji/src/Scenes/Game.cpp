#include "Scenes/Game.hpp"
#include "Commons/Random.hpp"
#include "Common.hpp"

Game::Game(const InitData& init) : IScene(init) {
	getData().spentTime.start();
	stage.nextStage();
}

void Game::update() {
	const Phase phase = stage.getCurrentPhase();

	if (phase == Phase::Started) {
		if (stage.isCleared()) {
			score += stage.getRemainingTime();
			stage.nextStage();
			return;
		}

		if (MouseL.down()) {
			score -= 1;
		}

		stage.update();
	}

	if (phase == Phase::Finished) {
		changeScene(State::GameOver, SceneTrasisionTime);
		getData().spentTime.pause();
		getData().ranking.addScore(score);
		getData().ranking.saveRanking();
		getData().lastScore = score;
	}
}

void Game::draw() const {
	drawUI();

	const Phase phase = stage.getCurrentPhase();
	switch (phase) {
	case Phase::Ready:
		FontAsset(U"Title")(U"’T‚¹!!!").drawAt(Scene::Center().movedBy(0, -150));
		stage.getTargetChara().texture.drawAt(Scene::Center());
		break;
	case Phase::Started:
		drawStage();
		break;
	case Phase::TimeOver:
		stage.getTargetChara().draw();
		break;
	}
}

void Game::drawUI() const {
	stage.getTargetChara().texture.drawAt(Scene::Width() - 100, 100);

	FontAsset(U"Score")(U"Time: {}"_fmt(stage.getRemainingTime())).drawAt(Scene::Width() - 100, 200);
	FontAsset(U"Score")(U"Level: {}"_fmt(stage.getCurrentLevel())).drawAt(Scene::Width() - 100, 250);
	FontAsset(U"Score")(U"Score:").drawAt(Scene::Width() - 100, 300);
	FontAsset(U"Score")(U"{}"_fmt(score)).drawAt(Scene::Width() - 90, 350);

	stageRect.drawFrame(0.5);
	stageRect.draw(Palette::Black);
}

void Game::drawStage() const {
	rt.clear(Palette::Black);
	{
		ScopedRenderTarget2D target(rt);
		stage.getTargetChara().draw();
		for (const auto& chara : stage.getOtherCharas()) {
			chara.draw();
		}
	}
	rt.drawAt(stageRect.center());
}