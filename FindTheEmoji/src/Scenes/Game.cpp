#include "Scenes/Game.hpp"
#include "Commons/Random.hpp"
#include "Common.hpp"

Game::Game(const InitData& init) : IScene(init) {
	getData().spentTime.start();
	stage.nextStage();
	timer.start();
}

bool isNotStarted(Timer timer) {
	return timer.progress0_1() <= 0.05;
}

bool isFinished(Timer timer) {
	return timer.remaining() <= 1s;
}

void Game::update() {
	if (isNotStarted(timer)) return;

	if (timer.remaining() <= 0s) {
		changeScene(State::GameOver, SceneTrasisionTime);
		getData().spentTime.pause();
		getData().ranking.addScore(score);
		getData().ranking.saveRanking();
		getData().lastScore = score;
	}

	if (MouseL.down() && !stage.isCleared()) {
		score -= 1;
	}

	if (!isFinished(timer) && stage.isCleared()) {
		score += timer.s();
		stage.nextStage();
		timer.restart();
	}

	stage.update();
}

void Game::draw() const {
	drawUI();

	if (isNotStarted(timer)) {
		FontAsset(U"Title")(U"’T‚¹!!!").drawAt(Scene::Center().movedBy(0, -150));
		stage.getTargetChara().texture.drawAt(Scene::Center());
		return;
	}

	if (isFinished(timer)) {
		stage.getTargetChara().draw();
		return;
	}

	drawStage();
}

void Game::drawUI() const {
	stage.getTargetChara().texture.drawAt(Scene::Width() - 100, 100);

	FontAsset(U"Score")(U"Time: {}"_fmt(timer.s())).drawAt(Scene::Width() - 100, 200);
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