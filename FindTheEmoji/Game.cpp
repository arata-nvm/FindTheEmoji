#include "Game.hpp"
#include "Random.hpp"

Game::Game(const InitData& init) : IScene(init) {
	getData().spentTime.start();
	stage.initStage(level);
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
		changeScene(State::GameOver, getData().sceneTransisionTime);
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
		stage.initStage(++level);
		timer.restart();
	}

	stage.update();
}

void Game::draw() const {
	stage.getTargetChara().texture.drawAt(Scene::Width() - 100, 100);
	FontAsset(U"Score")(U"Time: {}"_fmt(timer.s())).drawAt(Scene::Width() - 100, 200);
	FontAsset(U"Score")(U"Level: {}"_fmt(level)).drawAt(Scene::Width() - 100, 250);
	FontAsset(U"Score")(U"Score:").drawAt(Scene::Width() - 100, 300);
	FontAsset(U"Score")(U"{}"_fmt(score)).drawAt(Scene::Width() - 90, 350);

	stage.drawStage();

	if (isNotStarted(timer)) {
		stage.drawTargetAtCenter();
		return;
	}

	if (isFinished(timer)) {
		stage.getTargetChara().draw();
		return;
	}

	stage.draw();

}