#include "Scenes/GameOver.hpp"

GameOver::GameOver(const InitData& init) : IScene(init) {

}

void GameOver::update() {
	m_retryTransition.update(m_retryButton.mouseOver());
	m_titleTransition.update(m_titleButton.mouseOver());

	if (m_retryButton.mouseOver() || m_titleButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (m_retryButton.leftClicked()) {
		changeScene(State::Game, getData().sceneTransisionTime);
	}

	if (m_titleButton.leftClicked()) {
		changeScene(State::Title, getData().sceneTransisionTime);
	}
}

void GameOver::draw() const {
	const String titleText = U"Game over";
	const Vec2 center(Scene::Center().x, 120);
	FontAsset(U"Title")(titleText).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
	FontAsset(U"Title")(titleText).drawAt(center);

	const int32 lastScore = getData().lastScore;
	const String score = U"Score: {} ({}/{}ˆÊ)"_fmt(lastScore, getData().ranking.getRank(lastScore), getData().ranking.size());
	FontAsset(U"Score")(score).drawAt(center.movedBy(0, 200));

	const int32 highScore = getData().ranking.getHighScore();
	FontAsset(U"Score")(U"High score: {}"_fmt(highScore)).drawAt(center.movedBy(0, 250));


	m_retryButton.draw(ColorF(1.0, m_retryTransition.value())).drawFrame(2);
	m_titleButton.draw(ColorF(1.0, m_titleTransition.value())).drawFrame(2);

	FontAsset(U"Menu")(U"Retry").drawAt(m_retryButton.center(), ColorF(0.25));
	FontAsset(U"Menu")(U"Title").drawAt(m_titleButton.center(), ColorF(0.25));

	Rect(0, 500, Scene::Width(), Scene::Height() - 500)
		.draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));

}