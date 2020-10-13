#include "Scenes/Title.hpp"
#include "GameLogic/Chara.hpp"
#include "Commons/Random.hpp"
#include "Common.hpp"

Title::Title(const InitData& init) : IScene(init) {
	Title::getData().ranking.loadRanking();

	// 背景の絵文字キャラを初期化する
	const Array<char32> emojis = Range(U'😀', U'😛').asArray();
	const Vec2 baseVelocity = RandomVelocity(3);
	for (auto _ : step(10)) {
		charas.push_back(Chara(
			emojis.choice(),
			RandomScreenPos(screenRect),
			baseVelocity * Random(0.5, 1.5)
		));
	}
}

void Title::update() {
	m_startTransition.update(m_startButton.mouseOver());
	m_exitTransition.update(m_exitButton.mouseOver());
	if (m_startButton.mouseOver() || m_exitButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (m_startButton.leftClicked()) {
		changeScene(State::Game, SceneTrasisionTime);
	}

	if (m_exitButton.leftClicked()) {
		System::Exit();
	}
	
	for (auto& chara : charas) {
		chara.update(screenRect);
	}
}

void Title::draw() const {
	for (const auto& chara : charas) {
		chara.draw();
	}

	const int centerX = Scene::Center().x;

	// タイトル
	const String TitleName = U"You're an idiot";
	const Vec2 center(centerX, 120);
	FontAsset(U"Title")(TitleName).drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
	FontAsset(U"Title")(TitleName).drawAt(center);

	// スコア情報
	const int32 highScore = getData().ranking.getHighScore();
	const String spentTime = getData().spentTime.format(U"H時間m分s秒");
	FontAsset(U"Score")(U"High score: {}"_fmt(highScore)).drawAt(centerX, 300);
	FontAsset(U"Score")(U"無駄にされた時間: {}"_fmt(spentTime)).drawAt(centerX, 350);

	// ボタン
	m_startButton.draw(ColorF(1.0, m_startTransition.value())).drawFrame(2);
	m_exitButton.draw(ColorF(1.0, m_exitTransition.value())).drawFrame(2);
	FontAsset(U"Menu")(U"Start").drawAt(m_startButton.center(), ColorF(0.25));
	FontAsset(U"Menu")(U"Exit").drawAt(m_exitButton.center(), ColorF(0.25));

	// 背景
	Rect(0, 500, Scene::Width(), Scene::Height() - 500)
		.draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));
}